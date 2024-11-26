/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12GraphicsPipeline;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <stdexcept>;
import <type_traits>;
import <vector>;

import PonyBase.COMUtility;
import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Utility;

import :Direct3D12Material;
import :Direct3D12Mesh;
import :Direct3D12RootSignature;
import :Direct3D12RenderObject;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12RenderObjectManagerPrivate;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12RenderViewPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 graphics pipeline.
	class Direct3D12GraphicsPipeline final
	{
	public:
		/// @brief Creates a @p Direct3D12GraphicsPipeline.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueuePriority Command queue priority.
		[[nodiscard("Pure constructor")]]
		Direct3D12GraphicsPipeline(IDirect3D12SystemContext& d3d12System, INT commandQueuePriority);
		Direct3D12GraphicsPipeline(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline(Direct3D12GraphicsPipeline&&) = delete;

		~Direct3D12GraphicsPipeline() noexcept;

		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		/// @brief Gets the main command queue.
		/// @return Command queue.
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		/// @brief Populates commands. All the system components must be ready.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();

		Direct3D12GraphicsPipeline& operator =(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline& operator =(Direct3D12GraphicsPipeline&&) = delete;

	private:
		/// @brief Direct3D12 render object entry. It's used in the cache.
		struct Direct3D12RenderObjectEntry final
		{
			Direct3D12RenderObject* renderObject; ///< Render object.
			PonyMath::Core::Matrix4x4<FLOAT> mvpMatrix; ///< Model-view-projection matrix.
		};

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Populates resource barriers to make resources ready for rendering.
		void PopulateResourceBarriersIn();
		/// @brief Populates render target commands.
		void PopulateRenderTarget();
		/// @brief Gets render objects to render and sorts them. The result is in the @p renderObjects.
		void GetRenderObjects();
		/// @brief Populates render objects that were gotten in the @p GetRenderObjects().
		void PopulateRenderObjects();
		/// @brief Populates resource barriers back.
		void PopulateResourceBarriersOut();
		/// @brief Closes command lists.
		void CloseLists();

		GUID guid; ///< Graphics pipeline guid.

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Graphics command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Graphics command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Graphics command list.

		std::vector<Direct3D12RenderObjectEntry> renderObjects; ///< Render objects cache.
	};
}

namespace PonyEngine::Render
{
	Direct3D12GraphicsPipeline::Direct3D12GraphicsPipeline(IDirect3D12SystemContext& d3d12System, const INT commandQueuePriority) :
		guid{PonyBase::Utility::AcquireGuid()},
		d3d12System{&d3d12System}
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Graphics pipeline guid: '{}'.", PonyBase::Utility::ToString(guid));

		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command queue. Priority: '{}'.", commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = commandQueuePriority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		ID3D12Device10& device = this->d3d12System->Device();
		if (const HRESULT result = device.CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command queue with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command queue acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandQueue.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command allocator.");
		if (const HRESULT result = device.CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command allocator acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandAllocator.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire direct command list.");
		if (const HRESULT result = device.CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire direct command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command list acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandList.Get()));
	}

	Direct3D12GraphicsPipeline::~Direct3D12GraphicsPipeline() noexcept
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command list.");
		commandList.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command list released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command allocator.");
		commandAllocator.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command allocator released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release direct command queue.");
		commandQueue.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Direct command queue released.");
	}

	ID3D12CommandQueue& Direct3D12GraphicsPipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& Direct3D12GraphicsPipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void Direct3D12GraphicsPipeline::PopulateCommands()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command lists.");
		ResetLists();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate resource barriers in.");
		PopulateResourceBarriersIn();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate render target.");
		PopulateRenderTarget();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Get render objects.");
		GetRenderObjects();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate render objects.");
		PopulateRenderObjects();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Populate resource barriers out.");
		PopulateResourceBarriersOut();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Close command lists.");
		CloseLists();
	}

	void Direct3D12GraphicsPipeline::Execute()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command lists.");
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void Direct3D12GraphicsPipeline::ResetLists()
	{
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersIn()
	{
		const auto renderTargetBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = &d3d12System->RenderTargetPrivate().CurrentBackBuffer(),
				.Subresource = 0u,
				.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
				.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
			}
		};
		commandList->ResourceBarrier(1u, &renderTargetBarrier);
	}

	void Direct3D12GraphicsPipeline::PopulateRenderTarget()
	{
		const IDirect3D12RenderTargetPrivate& renderTarget = d3d12System->RenderTargetPrivate();
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.CurrentRtvHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = d3d12System->DepthStencilPrivate().DsvHandle();
		commandList->OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
		commandList->ClearRenderTargetView(rtvHandle, renderTarget.ClearColorD3D12().Span().data(), 0u, nullptr);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 0u, nullptr);

		const PonyMath::Utility::Resolution<UINT>& resolution = renderTarget.ResolutionD3D12();
		const auto viewport = D3D12_VIEWPORT{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH};
		commandList->RSSetViewports(1u, &viewport);
		const auto rect = D3D12_RECT{.left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height())};
		commandList->RSSetScissorRects(1u, &rect);
	}

	void Direct3D12GraphicsPipeline::GetRenderObjects()
	{
		const IDirect3D12RenderViewPrivate& renderView = d3d12System->RenderViewPrivate();
		const PonyMath::Core::Matrix4x4<FLOAT> vp = renderView.ProjectionMatrixD3D12() * renderView.ViewMatrixD3D12();

		IDirect3D12RenderObjectManagerPrivate& renderObjectManager = d3d12System->RenderObjectManagerPrivate();
		const std::size_t renderObjectCount = renderObjectManager.RenderObjectCount();
		renderObjects.clear();
		renderObjects.reserve(renderObjectCount);
		for (std::size_t i = 0; i < renderObjectCount; ++i)
		{
			Direct3D12RenderObject& renderObject = renderObjectManager.RenderObject(i);
			renderObjects.push_back(Direct3D12RenderObjectEntry{.renderObject = &renderObject, .mvpMatrix = vp * renderObject.ModelMatrix()});
		}

		std::ranges::sort(renderObjects, [](const Direct3D12RenderObjectEntry& left, const Direct3D12RenderObjectEntry& right)
		{
			const Direct3D12Material* const leftMaterial = &left.renderObject->Material();
			const Direct3D12Material* const rightMaterial = &right.renderObject->Material();
			const Direct3D12RootSignature* const leftRootSignature = &leftMaterial->RootSignature();
			const Direct3D12RootSignature* const rightRootSignature = &rightMaterial->RootSignature();
			if (leftRootSignature != rightRootSignature)
			{
				return reinterpret_cast<std::uintptr_t>(leftRootSignature) < reinterpret_cast<std::uintptr_t>(rightRootSignature);
			}
			if (leftMaterial != rightMaterial)
			{
				return reinterpret_cast<std::uintptr_t>(leftMaterial) < reinterpret_cast<std::uintptr_t>(rightMaterial);
			}

			const Direct3D12Mesh* const leftMesh = &left.renderObject->Mesh();
			const Direct3D12Mesh* const rightMesh = &right.renderObject->Mesh();
			if (leftMesh != rightMesh)
			{
				return reinterpret_cast<std::uintptr_t>(leftMesh) < reinterpret_cast<std::uintptr_t>(rightMesh);
			}

			return PonyMath::Core::ExtractTranslation(left.mvpMatrix).Z() < PonyMath::Core::ExtractTranslation(right.mvpMatrix).Z();
		});
	}

	void Direct3D12GraphicsPipeline::PopulateRenderObjects()
	{
		const Direct3D12RootSignature* prevRootSignature = nullptr;
		const Direct3D12Material* prevMaterial = nullptr;
		const Direct3D12Mesh* prevMesh = nullptr;

		for (const Direct3D12RenderObjectEntry& renderObjectEntry : renderObjects)
		{
			Direct3D12RenderObject* const renderObject = renderObjectEntry.renderObject;

			Direct3D12Material* const material = &renderObject->Material();
			Direct3D12RootSignature* const rootSignature = &material->RootSignature();
			if (rootSignature != prevRootSignature)
			{
				commandList->SetGraphicsRootSignature(&rootSignature->RootSignature());
			}
			if (material != prevMaterial)
			{
				commandList->SetPipelineState(&material->GetPipelineState());
				commandList->IASetPrimitiveTopology(material->PrimitiveTopology());
			}

			const Direct3D12Mesh* const mesh = &renderObject->Mesh();
			if (mesh != prevMesh || material != prevMaterial)
			{
				commandList->IASetVertexBuffers(material->VertexSlot(), 1, &mesh->VertexBufferView());
				if (material->VertexColorSlot() && mesh->VertexColorBufferView())
				{
					commandList->IASetVertexBuffers(material->VertexColorSlot().value(), 1, &mesh->VertexColorBufferView().value());
				}
			}
			if (mesh != prevMesh)
			{
				commandList->IASetIndexBuffer(&mesh->VertexIndexBufferView());
			}

			const PonyMath::Core::Matrix4x4<FLOAT>& mvp = renderObjectEntry.mvpMatrix;
			commandList->SetGraphicsRoot32BitConstants(rootSignature->MvpIndex(), mvp.ComponentCount, mvp.Span().data(), 0);

			commandList->DrawIndexedInstanced(mesh->IndexCount(), 1, 0, 0, 0);

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersOut()
	{
		const auto presentBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = &d3d12System->RenderTargetPrivate().CurrentBackBuffer(),
				.Subresource = 0u,
				.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
				.StateAfter = D3D12_RESOURCE_STATE_PRESENT
			}
		};
		commandList->ResourceBarrier(1u, &presentBarrier);
	}

	void Direct3D12GraphicsPipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
