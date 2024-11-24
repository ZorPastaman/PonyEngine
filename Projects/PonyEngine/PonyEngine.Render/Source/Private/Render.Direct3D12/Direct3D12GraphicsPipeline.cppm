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

import :Direct3D12DepthStencil;
import :Direct3D12Mesh;
import :Direct3D12MeshManager;
import :Direct3D12Material;
import :Direct3D12MaterialManager;
import :Direct3D12RenderTarget;
import :Direct3D12RenderObjectManager;
import :Direct3D12RootSignatureManager;
import :Direct3D12RenderView;
import :Direct3D12Waiter;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	class Direct3D12GraphicsPipeline final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12GraphicsPipeline(IDirect3D12SystemContext& d3d12System, INT commandQueuePriority);
		Direct3D12GraphicsPipeline(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline(Direct3D12GraphicsPipeline&&) = delete;

		~Direct3D12GraphicsPipeline() noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue& CommandQueue() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12CommandQueue& CommandQueue() const noexcept;

		void PopulateCommands(UINT bufferIndex);
		void Execute();

		Direct3D12GraphicsPipeline& operator =(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline& operator =(Direct3D12GraphicsPipeline&&) = delete;

	private:
		void ResetQueue();
		void PopulateResourceBarriersIn(UINT bufferIndex);
		void PopulateRenderTarget(UINT bufferIndex);
		void PopulateRenderObjects();
		void PopulateResourceBarriersOut(UINT bufferIndex);
		void CloseQueue();

		GUID guid;

		IDirect3D12SystemContext* d3d12System;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;
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

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire command allocator.");
		if (const HRESULT result = device.CreateCommandAllocator(commandListType, IID_PPV_ARGS(commandAllocator.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command allocator acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandAllocator.Get()));

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire command list.");
		if (const HRESULT result = device.CreateCommandList1(0, commandListType, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(commandList.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command list acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandList.Get()));
	}

	Direct3D12GraphicsPipeline::~Direct3D12GraphicsPipeline() noexcept
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command list.");
		commandList.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command list released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command allocator.");
		commandAllocator.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command allocator released.");

		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command queue.");
		commandQueue.Reset();
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command queue released.");
	}

	ID3D12CommandQueue& Direct3D12GraphicsPipeline::CommandQueue() noexcept
	{
		return *commandQueue.Get();
	}

	const ID3D12CommandQueue& Direct3D12GraphicsPipeline::CommandQueue() const noexcept
	{
		return *commandQueue.Get();
	}

	void Direct3D12GraphicsPipeline::PopulateCommands(const UINT bufferIndex)
	{
		ResetQueue();
		PopulateResourceBarriersIn(bufferIndex);
		PopulateRenderTarget(bufferIndex);
		PopulateRenderObjects();
		PopulateResourceBarriersOut(bufferIndex);
		CloseQueue();
	}

	void Direct3D12GraphicsPipeline::Execute()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command list.");
		ID3D12CommandList* const commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(1, commandLists);
	}

	void Direct3D12GraphicsPipeline::ResetQueue()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command allocator.");
		if (const HRESULT result = commandAllocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command allocator with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Reset command list.");
		if (const HRESULT result = commandList->Reset(commandAllocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to reset command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersIn(const UINT bufferIndex)
	{
		ID3D12Resource2& backBuffer = d3d12System->RenderTarget().GetBackBuffer(bufferIndex);

		const auto renderTargetBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = &backBuffer,
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
				.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
			}
		};
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' as render target.", reinterpret_cast<std::uintptr_t>(&backBuffer));
		commandList->ResourceBarrier(1, &renderTargetBarrier);
	}

	void Direct3D12GraphicsPipeline::PopulateRenderTarget(const UINT bufferIndex)
	{
		const IDirect3D12RenderTargetPrivate& renderTarget = d3d12System->RenderTarget();
		const IDirect3D12DepthStencilPrivate& depthStencil = d3d12System->DepthStencil();

		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget.GetRtvHandle(bufferIndex);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set '0x{:X}' render target view.", rtvHandle.ptr);
		const D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = depthStencil.DsvHandle();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set '0x{:X}' depth stencil view.", dsvHandle.ptr);
		commandList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set clear color to {}.", renderTarget.ClearColorD3D12().ToString());
		commandList->ClearRenderTargetView(rtvHandle, renderTarget.ClearColorD3D12().Span().data(), 0, nullptr);
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Clear depth stencil view.");
		commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, D3D12_MAX_DEPTH, 0u, 0u, nullptr);

		const PonyMath::Utility::Resolution<UINT>& resolution = renderTarget.ResolutionD3D12();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set render resolution to '{}'.", resolution.ToString());
		const auto viewport = D3D12_VIEWPORT{.TopLeftX = 0.f, .TopLeftY = 0.f, .Width = static_cast<FLOAT>(resolution.Width()), .Height = static_cast<FLOAT>(resolution.Height()), .MinDepth = D3D12_MIN_DEPTH, .MaxDepth = D3D12_MAX_DEPTH};
		commandList->RSSetViewports(1u, &viewport);
		const auto rect = D3D12_RECT{ .left = 0L, .top = 0L, .right = static_cast<LONG>(resolution.Width()), .bottom = static_cast<LONG>(resolution.Height()) };
		commandList->RSSetScissorRects(1u, &rect);
	}

	void Direct3D12GraphicsPipeline::PopulateRenderObjects()
	{
		const IDirect3D12RenderView& renderView = d3d12System->RenderView();
		const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix = renderView.ViewMatrixD3D12();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set view matrix to '{}'.", viewMatrix.ToString());
		const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix = renderView.ProjectionMatrixD3D12();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set projection matrix to '{}'.", projectionMatrix.ToString());
		const PonyMath::Core::Matrix4x4<FLOAT> vp = projectionMatrix * viewMatrix;

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set render objects.");
		for (auto renderObjectWeak : d3d12System->RenderObjectManager().RenderObjects())
		{
			std::shared_ptr<Direct3D12RenderObject> renderObject = renderObjectWeak.lock(); // TODO: Sort before rendering in the order RootSignature, PipelineState, Mesh.
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set render object at '0x{:X}.'", reinterpret_cast<std::uintptr_t>(renderObject.get()));

			Direct3D12Material& material = renderObject->Material();
			Direct3D12RootSignature& rootSignature = material.RootSignature();
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set root signature at '0x{:X}.'", reinterpret_cast<std::uintptr_t>(&rootSignature.RootSignature()));
			commandList->SetGraphicsRootSignature(&rootSignature.RootSignature());
			ID3D12PipelineState& pipelineState = material.GetPipelineState();
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set pipeline state at '0x{:X}.'", reinterpret_cast<std::uintptr_t>(&pipelineState));
			commandList->SetPipelineState(&pipelineState);
			commandList->IASetPrimitiveTopology(material.PrimitiveTopology());

			Direct3D12Mesh& renderMesh = renderObject->Mesh();
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set render mesh at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(&renderMesh));
			commandList->IASetVertexBuffers(0, 1, &renderMesh.VertexBufferView()); // TODO: Material has to tell slots for buffers.
			commandList->IASetVertexBuffers(1, 1, &renderMesh.VertexColorBufferView());
			commandList->IASetIndexBuffer(&renderMesh.VertexIndexBufferView());

			const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix = renderObject->ModelMatrixD3D12();
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set model matrix to '{}'.", modelMatrix.ToString());
			const PonyMath::Core::Matrix4x4<FLOAT> mvp = vp * modelMatrix;
			commandList->SetGraphicsRoot32BitConstants(rootSignature.MvpIndex(), mvp.ComponentCount, mvp.Span().data(), 0);
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Draw.");
			commandList->DrawIndexedInstanced(renderMesh.IndexCount(), 1, 0, 0, 0);
		}
	}

	void Direct3D12GraphicsPipeline::PopulateResourceBarriersOut(const UINT bufferIndex)
	{
		ID3D12Resource2& backBuffer = d3d12System->RenderTarget().GetBackBuffer(bufferIndex);

		const auto presentBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = &backBuffer,
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
				.StateAfter = D3D12_RESOURCE_STATE_PRESENT
			}
		};
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as present.", reinterpret_cast<std::uintptr_t>(&backBuffer), bufferIndex);
		commandList->ResourceBarrier(1, &presentBarrier);
	}

	void Direct3D12GraphicsPipeline::CloseQueue()
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Close command list.");
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
