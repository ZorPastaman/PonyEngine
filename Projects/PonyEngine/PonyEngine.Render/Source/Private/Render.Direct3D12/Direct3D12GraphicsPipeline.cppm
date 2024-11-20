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

import <cstdint>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.COMUtility;
import PonyBase.StringUtility;

import PonyMath.Color;
import PonyMath.Core;
import PonyMath.Geometry;
import PonyMath.Utility;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;

import :Direct3D12Mesh;
import :Direct3D12MeshManager;
import :Direct3D12Material;
import :Direct3D12MaterialManager;
import :Direct3D12RenderTarget;
import :Direct3D12RenderObjectManager;
import :Direct3D12RenderView;
import :Direct3D12Waiter;

export namespace PonyEngine::Render
{
	class Direct3D12GraphicsPipeline final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12GraphicsPipeline(IRenderContext& renderer, ID3D12Device10* device, const Direct3D12RenderSystemParams& params, Direct3D12RenderTarget* renderTarget, Direct3D12RenderView* renderView, 
			Direct3D12MaterialManager* materialManager, Direct3D12MeshManager* meshManager, Direct3D12RenderObjectManager* renderObjectManager);
		Direct3D12GraphicsPipeline(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline(Direct3D12GraphicsPipeline&&) = delete;

		~Direct3D12GraphicsPipeline() noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue* GetCommandQueue() const noexcept;

		void PopulateCommands(UINT bufferIndex);
		void Execute();

		Direct3D12GraphicsPipeline& operator =(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline& operator =(Direct3D12GraphicsPipeline&&) = delete;

	private:
		void ResetQueue();
		void PopulateResourceBarriersBegin(UINT bufferIndex);
		void PopulateTarget(UINT bufferIndex);
		void PopulateView();
		void PopulateRenderObjects();
		void PopulateResourceBarriersEnd(UINT bufferIndex);
		void CloseQueue();

		GUID guid;
		IRenderContext* renderer;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;

		Direct3D12RenderTarget* renderTarget;
		Direct3D12RenderView* renderView;
		Direct3D12MaterialManager* materialManager;
		Direct3D12MeshManager* meshManager;
		Direct3D12RenderObjectManager* renderObjectManager;
	};
}

namespace PonyEngine::Render
{
	Direct3D12GraphicsPipeline::Direct3D12GraphicsPipeline(IRenderContext& renderer, ID3D12Device10* const device, const Direct3D12RenderSystemParams& params, Direct3D12RenderTarget* const renderTarget, 
		Direct3D12RenderView* const renderView, Direct3D12MaterialManager* const materialManager, Direct3D12MeshManager* const meshManager, Direct3D12RenderObjectManager* const renderObjectManager) :
		guid{PonyBase::Utility::AcquireGuid()},
		renderer{&renderer},
		renderTarget{renderTarget},
		renderView{renderView},
		materialManager{materialManager},
		meshManager{meshManager},
		renderObjectManager{renderObjectManager}
	{
		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline guid: '{}'.", PonyBase::Utility::ToString(guid));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 command queue. Priority: '{}'.", params.commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = params.commandQueuePriority,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device->CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 command queue with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandQueue.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 command allocator.");
		if (const HRESULT result = device->CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command allocator acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandAllocator.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 command list.");
		if (const HRESULT result = device->CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command list acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandList.Get()));
	}

	Direct3D12GraphicsPipeline::~Direct3D12GraphicsPipeline() noexcept
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command list.");
		commandList.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command list released.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command allocator.");
		commandAllocator.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command allocator released.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command queue.");
		commandQueue.Reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue released.");
	}

	ID3D12CommandQueue* Direct3D12GraphicsPipeline::GetCommandQueue() noexcept
	{
		return commandQueue.Get();
	}

	const ID3D12CommandQueue* Direct3D12GraphicsPipeline::GetCommandQueue() const noexcept
	{
		return commandQueue.Get();
	}

	void Direct3D12GraphicsPipeline::PopulateCommands(const UINT bufferIndex)
	{
		ResetQueue();
		PopulateResourceBarriersBegin(bufferIndex);
		PopulateTarget(bufferIndex);
		PopulateView();
		PopulateRenderObjects();
		PopulateResourceBarriersEnd(bufferIndex);
		CloseQueue();
	}

	void Direct3D12GraphicsPipeline::Execute()
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command list.");
		ID3D12CommandList* const commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(1, commandLists);
	}

	void Direct3D12GraphicsPipeline::ResetQueue()
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command allocator.");
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command list.");
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersBegin(const UINT bufferIndex)
	{
		ID3D12Resource2* const backBuffer = renderTarget->GetBackBuffer(bufferIndex);

		const auto renderTargetBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = backBuffer,
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
				.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as render target.", reinterpret_cast<std::uintptr_t>(backBuffer), bufferIndex);
		commandList->ResourceBarrier(1, &renderTargetBarrier);
	}

	void Direct3D12GraphicsPipeline::PopulateTarget(const UINT bufferIndex)
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render target.");
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetRtvHandle(bufferIndex);
		commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set clear color to {}.", renderTarget->ClearColor().ToString());
		commandList->ClearRenderTargetView(rtvHandle, renderTarget->ClearColorD3D12().Span().data(), 0, nullptr);
	}

	void Direct3D12GraphicsPipeline::PopulateView()
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render view.");
		commandList->RSSetViewports(1, &renderView->Viewport().Viewport());
		commandList->RSSetScissorRects(1, &renderView->Viewport().Rect());
	}

	void Direct3D12GraphicsPipeline::PopulateRenderObjects()
	{
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		const PonyMath::Core::Matrix4x4<FLOAT>& vp = renderView->VpMatrix();

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render objects.");
		for (auto renderObject = renderObjectManager->RenderObjectBegin(); renderObject != renderObjectManager->RenderObjectEnd(); ++renderObject)
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set pipeline state.");
			Direct3D12Material* const material = materialManager->FindMaterial(renderObject->second.Material());
			commandList->SetGraphicsRootSignature(material->GetRootSignature());
			commandList->SetPipelineState(material->GetPipelineState());

			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render object with '{}' id.", renderObject->first.id);
			Direct3D12Mesh* const renderMesh = meshManager->FindDirect3D12Mesh(renderObject->second.RenderMesh());
			commandList->IASetVertexBuffers(0, 1, &renderMesh->VerticesView());
			commandList->IASetVertexBuffers(1, 1, &renderMesh->VertexColorsView());
			commandList->IASetIndexBuffer(&renderMesh->VertexIndicesView());

			const PonyMath::Core::Matrix4x4<FLOAT> mvp = vp * renderObject->second.ModelMatrixD3D12();
			commandList->SetGraphicsRoot32BitConstants(0u, mvp.ComponentCount, mvp.Span().data(), 0); // TODO: Data must come from root signature. So, it seems that I need a root signature class.
			commandList->DrawIndexedInstanced(renderMesh->IndexCount(), 1, 0, 0, 0);
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersEnd(const UINT bufferIndex)
	{
		ID3D12Resource2* const backBuffer = renderTarget->GetBackBuffer(bufferIndex);

		const auto presentBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = backBuffer,
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
				.StateAfter = D3D12_RESOURCE_STATE_PRESENT
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as present.", reinterpret_cast<std::uintptr_t>(backBuffer), bufferIndex);
		commandList->ResourceBarrier(1, &presentBarrier);
	}

	void Direct3D12GraphicsPipeline::CloseQueue()
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Close command list.");
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
