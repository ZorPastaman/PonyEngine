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
import <memory>;
import <stdexcept>;
import <string>;
import <string_view>;
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
import :Direct3D12Utility;
import :IDirect3D12DepthStencilPrivate;
import :IDirect3D12GraphicsPipeline;
import :IDirect3D12RenderTargetPrivate;
import :IDirect3D12RenderViewPrivate;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 graphics pipeline.
	class Direct3D12GraphicsPipeline final : public IDirect3D12GraphicsPipeline
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

		virtual void AddVertexInitializationTask(ID3D12Resource2& vertexBuffer) override;
		virtual void AddIndexInitializationTask(ID3D12Resource2& indexBuffer) override;
		virtual void AddRenderTask(const std::shared_ptr<Direct3D12RenderObject>& renderObject) override;

		/// @brief Sets the name to the graphics pipeline components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Populates commands. All the system components must be ready.
		void PopulateCommands();
		/// @brief Executes populated commands.
		void Execute();
		/// @brief Clears the tasks. Must be called only after finishing execution.
		void Clear() noexcept;

		Direct3D12GraphicsPipeline& operator =(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline& operator =(Direct3D12GraphicsPipeline&&) = delete;

	private:
		/// @brief Direct3D12 render object entry. It's used in the cache.
		struct Direct3D12RenderObjectEntry final
		{
			std::shared_ptr<Direct3D12RenderObject> renderObject; ///< Render object.
			PonyMath::Core::Matrix4x4<FLOAT> mvpMatrix; ///< Model-view-projection matrix.
		};

		/// @brief Resets command lists.
		void ResetLists();
		/// @brief Populates begin to render barriers.
		void PopulateBeginToRenderBarriers();
		/// @brief Populates render target commands.
		void PopulateRenderTarget();
		/// @brief Populates render objects.
		void PopulateRenderObjects();
		/// @brief Populates render to resolve barriers.
		void PopulateRenderToResolveBarriers();
		/// @brief Populates resolve commands.
		void PopulateResolveCommands();
		/// @brief Populates resolve to end barriers.
		void PopulateResolveToEndBarriers();
		/// @brief Closes command lists.
		void CloseLists();

		/// @brief Populates barrier groups.
		void PopulateBarrierGroups();

		GUID guid; ///< Graphics pipeline guid.

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Graphics command queue.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator; ///< Graphics command allocator.
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList; ///< Graphics command list.

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> uninitializedVertices; ///< Uninitialized vertex buffers.
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> uninitializedIndices; ///< Uninitialized index buffers.
		std::vector<Direct3D12RenderObjectEntry> renderObjects; ///< Render objects.

		std::vector<D3D12_BUFFER_BARRIER> bufferBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_TEXTURE_BARRIER> textureBarriers; ///< Buffer barriers cache.
		std::vector<D3D12_BARRIER_GROUP> barrierGroups; ///< Barrier groups cache.
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

	void Direct3D12GraphicsPipeline::AddVertexInitializationTask(ID3D12Resource2& vertexBuffer)
	{
		uninitializedVertices.emplace_back(&vertexBuffer);
	}

	void Direct3D12GraphicsPipeline::AddIndexInitializationTask(ID3D12Resource2& indexBuffer)
	{
		uninitializedIndices.emplace_back(&indexBuffer);
	}

	void Direct3D12GraphicsPipeline::AddRenderTask(const std::shared_ptr<Direct3D12RenderObject>& renderObject)
	{
		renderObjects.push_back(Direct3D12RenderObjectEntry{.renderObject = renderObject});
	}

	void Direct3D12GraphicsPipeline::Name(const std::string_view name)
	{
		constexpr std::string_view commandQueueName = " - CommandQueue";
		constexpr std::string_view commandAllocatorName = " - CommandAllocator";
		constexpr std::string_view commandListName = " - CommandList";

		auto componentName = std::string();
		componentName.reserve(name.size() + commandAllocatorName.size());

		componentName.append(name).append(commandQueueName);
		SetName(*commandQueue.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandAllocatorName);
		SetName(*commandAllocator.Get(), componentName);

		componentName.clear();
		componentName.append(name).append(commandListName);
		SetName(*commandList.Get(), componentName);
	}

	void Direct3D12GraphicsPipeline::PopulateCommands()
	{
		ResetLists();
		PopulateBeginToRenderBarriers();
		PopulateRenderTarget();
		PopulateRenderObjects();
		PopulateRenderToResolveBarriers();
		PopulateResolveCommands();
		PopulateResolveToEndBarriers();
		CloseLists();
	}

	void Direct3D12GraphicsPipeline::Execute()
	{
		const auto commandLists = std::array<ID3D12CommandList*, 1> { commandList.Get() };
		commandQueue->ExecuteCommandLists(static_cast<UINT>(commandLists.size()), commandLists.data());
	}

	void Direct3D12GraphicsPipeline::Clear() noexcept
	{
		uninitializedVertices.clear();
		uninitializedIndices.clear();
		renderObjects.clear();
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

	void Direct3D12GraphicsPipeline::PopulateBeginToRenderBarriers()
	{
		bufferBarriers.clear();
		bufferBarriers.reserve(uninitializedVertices.size() + uninitializedIndices.size());
		for (Microsoft::WRL::ComPtr<ID3D12Resource2>& vertexBuffer : uninitializedVertices)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_VERTEX_BUFFER,
				.pResource = vertexBuffer.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(barrier);
		}
		for (Microsoft::WRL::ComPtr<ID3D12Resource2>& indexBuffer : uninitializedIndices)
		{
			const auto barrier = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_DRAW,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_INDEX_BUFFER,
				.pResource = indexBuffer.Get(),
				.Offset = 0UL,
				.Size = UINT64_MAX
			};
			bufferBarriers.push_back(barrier);
		}

		textureBarriers.clear();
		textureBarriers.reserve(2);
		const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_NONE,
			.SyncAfter = D3D12_BARRIER_SYNC_RENDER_TARGET,
			.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
			.AccessAfter = D3D12_BARRIER_ACCESS_RENDER_TARGET,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_COMMON,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
			.pResource = &d3d12System->RenderTargetPrivate().RenderTargetBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(renderTargetBarrier);
		const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.SyncAfter = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.AccessBefore = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_READ,
			.AccessAfter = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
			.pResource = &d3d12System->DepthStencilPrivate().DepthStencilBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void Direct3D12GraphicsPipeline::PopulateRenderTarget()
	{
		const IDirect3D12RenderTargetPrivate& renderTarget = d3d12System->RenderTargetPrivate();

		const PonyMath::Utility::Resolution<UINT>& resolution = renderTarget.ResolutionD3D12();
		const auto viewport = D3D12_VIEWPORT{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH};
		commandList->RSSetViewports(1u, &viewport);
		const auto rect = D3D12_RECT{.left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height())};
		commandList->RSSetScissorRects(1u, &rect);

		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.RtvHandle();
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = d3d12System->DepthStencilPrivate().DsvHandle();
		commandList->OMSetRenderTargets(1u, &rtvHandle, false, &dsvHandle);
		commandList->ClearRenderTargetView(rtvHandle, renderTarget.ClearColorD3D12().Span().data(), 0u, nullptr);
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 0u, nullptr);
	}

	void Direct3D12GraphicsPipeline::PopulateRenderObjects()
	{
		const IDirect3D12RenderViewPrivate& renderView = d3d12System->RenderViewPrivate();
		const PonyMath::Core::Matrix4x4<FLOAT> vp = renderView.ProjectionMatrixD3D12() * renderView.ViewMatrixD3D12();
		for (Direct3D12RenderObjectEntry& renderObject : renderObjects)
		{
			renderObject.mvpMatrix = vp * renderObject.renderObject->ModelMatrixD3D12();
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

		const Direct3D12RootSignature* prevRootSignature = nullptr;
		const Direct3D12Material* prevMaterial = nullptr;
		const Direct3D12Mesh* prevMesh = nullptr;
		for (const Direct3D12RenderObjectEntry& renderObject : renderObjects)
		{
			Direct3D12Material* const material = &renderObject.renderObject->Material();
			Direct3D12RootSignature* const rootSignature = &material->RootSignature();
			if (rootSignature != prevRootSignature)
			{
				commandList->SetGraphicsRootSignature(&rootSignature->RootSignature());
			}
			if (material != prevMaterial)
			{
				commandList->SetPipelineState(&material->PipelineState());
				commandList->IASetPrimitiveTopology(material->PrimitiveTopology());
			}

			const Direct3D12Mesh* const mesh = &renderObject.renderObject->Mesh();
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

			const PonyMath::Core::Matrix4x4<FLOAT>& mvp = renderObject.mvpMatrix;
			commandList->SetGraphicsRoot32BitConstants(rootSignature->MvpIndex(), mvp.ComponentCount, mvp.Span().data(), 0);

			commandList->DrawIndexedInstanced(mesh->IndexCount(), 1, 0, 0, 0); // TODO: Draw via mesh shaders

			prevRootSignature = rootSignature;
			prevMaterial = material;
			prevMesh = mesh;
		}
	}

	void Direct3D12GraphicsPipeline::PopulateRenderToResolveBarriers()
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		textureBarriers.reserve(3);
		if (d3d12System->RenderTargetPrivate().SampleDesc().Count > 1u)
		{
			const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
				.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
				.pResource = &d3d12System->RenderTargetPrivate().RenderTargetBuffer(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(renderTargetBarrier);
			const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_RESOLVE,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_RESOLVE_DEST,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_RESOLVE_DEST,
				.pResource = &d3d12System->BackBufferPrivate().CurrentBackBuffer()
			};
			textureBarriers.push_back(backBufferBarrier);
		}
		else
		{
			const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RENDER_TARGET,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_RENDER_TARGET,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RENDER_TARGET,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.pResource = &d3d12System->RenderTargetPrivate().RenderTargetBuffer(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(renderTargetBarrier);
			const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_NONE,
				.SyncAfter = D3D12_BARRIER_SYNC_COPY,
				.AccessBefore = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.AccessAfter = D3D12_BARRIER_ACCESS_COPY_DEST,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_PRESENT,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COPY_DEST,
				.pResource = &d3d12System->BackBufferPrivate().CurrentBackBuffer()
			};
			textureBarriers.push_back(backBufferBarrier);
		}
		const auto depthStencilBarrier = D3D12_TEXTURE_BARRIER
		{
			.SyncBefore = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.SyncAfter = D3D12_BARRIER_SYNC_DEPTH_STENCIL,
			.AccessBefore = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_WRITE,
			.AccessAfter = D3D12_BARRIER_ACCESS_DEPTH_STENCIL_READ,
			.LayoutBefore = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE,
			.LayoutAfter = D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ,
			.pResource = &d3d12System->DepthStencilPrivate().DepthStencilBuffer(),
			.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
		};
		textureBarriers.push_back(depthStencilBarrier);

		PopulateBarrierGroups();
	}

	void Direct3D12GraphicsPipeline::PopulateResolveCommands()
	{
		if (d3d12System->RenderTargetPrivate().SampleDesc().Count > 1u)
		{
			commandList->ResolveSubresource(&d3d12System->BackBufferPrivate().CurrentBackBuffer(), 0u, 
				&d3d12System->RenderTargetPrivate().RenderTargetBuffer(), 0u, 
				d3d12System->RenderTargetPrivate().Format());
		}
		else
		{
			commandList->CopyResource(&d3d12System->BackBufferPrivate().CurrentBackBuffer(), &d3d12System->RenderTargetPrivate().RenderTargetBuffer());
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResolveToEndBarriers()
	{
		bufferBarriers.clear();

		textureBarriers.clear();
		textureBarriers.reserve(2);
		if (d3d12System->RenderTargetPrivate().SampleDesc().Count > 1u)
		{
			const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = &d3d12System->RenderTargetPrivate().RenderTargetBuffer(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(renderTargetBarrier);
			const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_RESOLVE,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_RESOLVE_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_RESOLVE_DEST,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_PRESENT,
				.pResource = &d3d12System->BackBufferPrivate().CurrentBackBuffer()
			};
			textureBarriers.push_back(backBufferBarrier);
		}
		else
		{
			const auto renderTargetBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_SOURCE,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_SOURCE,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_COMMON,
				.pResource = &d3d12System->RenderTargetPrivate().RenderTargetBuffer(),
				.Subresources = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
				.Flags = D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
			textureBarriers.push_back(renderTargetBarrier);
			const auto backBufferBarrier = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = D3D12_BARRIER_SYNC_COPY,
				.SyncAfter = D3D12_BARRIER_SYNC_NONE,
				.AccessBefore = D3D12_BARRIER_ACCESS_COPY_DEST,
				.AccessAfter = D3D12_BARRIER_ACCESS_NO_ACCESS,
				.LayoutBefore = D3D12_BARRIER_LAYOUT_COPY_DEST,
				.LayoutAfter = D3D12_BARRIER_LAYOUT_PRESENT,
				.pResource = &d3d12System->BackBufferPrivate().CurrentBackBuffer()
			};
			textureBarriers.push_back(backBufferBarrier);
		}

		PopulateBarrierGroups();
	}

	void Direct3D12GraphicsPipeline::CloseLists()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12GraphicsPipeline::PopulateBarrierGroups()
	{
		barrierGroups.clear();
		barrierGroups.reserve((bufferBarriers.size() > 0) + (textureBarriers.size() > 0));

		if (bufferBarriers.size() > 0)
		{
			const auto bufferBarrierGroup = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(bufferBarriers.size()),
				.pBufferBarriers = bufferBarriers.data()
			};
			barrierGroups.push_back(bufferBarrierGroup);
		}
		if (textureBarriers.size() > 0)
		{
			const auto textureBarrierGroup = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(textureBarriers.size()),
				.pTextureBarriers = textureBarriers.data()
			};
			barrierGroups.push_back(textureBarrierGroup);
		}

		if (barrierGroups.size() > 0)
		{
			commandList->Barrier(static_cast<UINT32>(barrierGroups.size()), barrierGroups.data());
		}
	}
}
