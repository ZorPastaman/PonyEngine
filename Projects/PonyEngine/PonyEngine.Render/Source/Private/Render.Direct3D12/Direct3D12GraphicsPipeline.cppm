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

export module PonyEngine.Render.Direct3D12:Direct3D12GraphicsPipeline;

import <cstdint>;
import <memory>;
import <span>;
import <stdexcept>;
import <type_traits>;

import PonyBase.GuidUtility;
import PonyBase.StringUtility;

import PonyMath.Core;
import PonyMath.Geometry;

import PonyDebug.Log;

import PonyEngine.Screen;

import :Direct3D12Camera;
import :Direct3D12Fence;
import :Direct3D12Mesh;
import :Direct3D12MeshManager;
import :Direct3D12Material;
import :Direct3D12RenderTarget;
import :Direct3D12RenderObjectManager;

export namespace PonyEngine::Render
{
	class Direct3D12GraphicsPipeline final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12GraphicsPipeline(IRenderer& renderer, ID3D12Device10* device, INT commandQueuePriority, DWORD fenceTimeout);
		Direct3D12GraphicsPipeline(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline(Direct3D12GraphicsPipeline&&) = delete;

		~Direct3D12GraphicsPipeline() noexcept;

		[[nodiscard("Pure function")]]
		PonyMath::Core::RGBA<FLOAT>& ClearColor() noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::RGBA<FLOAT>& ClearColor() const noexcept;

		[[nodiscard("Pure function")]]
		PonyMath::Core::Matrix4x4<FLOAT>& CameraTrsMatrix() noexcept;
		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& CameraTrsMatrix() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		void Initialize(const Screen::Resolution<UINT>& resolution, FLOAT fov, FLOAT nearPlane, FLOAT farPlane, std::span<ID3D12Resource2*> buffers, DXGI_FORMAT rtvFormat);

		void PopulateCommands(UINT bufferIndex) const;
		void Execute() const;
		void WaitForEndOfFrame() const;

		RenderObjectHandle CreateRenderObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& trs) const;
		void DestroyRenderObject(RenderObjectHandle renderObjectHandle) const noexcept;

		void UpdateRenderObjectTrs(RenderObjectHandle handle, const PonyMath::Core::Matrix4x4<FLOAT>& trs) const noexcept;

		Direct3D12GraphicsPipeline& operator =(const Direct3D12GraphicsPipeline&) = delete;
		Direct3D12GraphicsPipeline& operator =(Direct3D12GraphicsPipeline&&) = delete;

	private:
		GUID guid;
		IRenderer* renderer;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;
		std::unique_ptr<Direct3DFence> fence;

		std::unique_ptr<Direct3D12RenderTarget> renderTarget;
		std::unique_ptr<Direct3D12Camera> camera;
		std::unique_ptr<Direct3D12Material> material;
		std::unique_ptr<Direct3D12MeshManager> meshManager;
		std::unique_ptr<Direct3D12RenderObjectManager> renderObjectManager;
	};
}

namespace PonyEngine::Render
{
	Direct3D12GraphicsPipeline::Direct3D12GraphicsPipeline(IRenderer& renderer, ID3D12Device10* const device, const INT commandQueuePriority, const DWORD fenceTimeout) :
		guid{PonyBase::Utility::AcquireGuid()},
		renderer{&renderer}
	{
		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 graphics pipeline guid: '{}'.", PonyBase::Utility::ToString(guid));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 command queue. Priority: '{}'.", commandQueuePriority);
		const auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = commandListType,
			.Priority = commandQueuePriority,
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

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 fence. Fence timeout: {}.", fenceTimeout);
		fence.reset(new Direct3DFence(*this->renderer, commandQueue.Get(), fenceTimeout));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 mesh manager.");
		meshManager.reset(new Direct3D12MeshManager(*this->renderer, device));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 mesh manager created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render object manager.");
		renderObjectManager.reset(new Direct3D12RenderObjectManager(*this->renderer, device));
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render object manager created.");
	}

	Direct3D12GraphicsPipeline::~Direct3D12GraphicsPipeline() noexcept
	{
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 render object manager.");
		renderObjectManager.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render object manager destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 mesh manager.");
		meshManager.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 mesh manager destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 material.");
		material.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 camera.");
		camera.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 camera destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 render target.");
		renderTarget.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target destroyed.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 fence.");
		fence.reset();
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence destroyed.");

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

	PonyMath::Core::RGBA<FLOAT>& Direct3D12GraphicsPipeline::ClearColor() noexcept
	{
		return renderTarget->ClearColor();
	}

	const PonyMath::Core::RGBA<FLOAT>& Direct3D12GraphicsPipeline::ClearColor() const noexcept
	{
		return renderTarget->ClearColor();
	}

	PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12GraphicsPipeline::CameraTrsMatrix() noexcept
	{
		return camera->TrsMatrix();
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12GraphicsPipeline::CameraTrsMatrix() const noexcept
	{
		return camera->TrsMatrix();
	}

	ID3D12CommandQueue* Direct3D12GraphicsPipeline::GetCommandQueue() const
	{
		return commandQueue.Get();
	}

	void Direct3D12GraphicsPipeline::Initialize(const Screen::Resolution<UINT>& resolution, const FLOAT fov, const FLOAT nearPlane, const FLOAT farPlane, const std::span<ID3D12Resource2*> buffers, const DXGI_FORMAT rtvFormat)
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 camera. Resolution: '{}'.", resolution.ToString());
		camera.reset(new Direct3D12Camera(resolution, fov, nearPlane, farPlane));
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 camera created.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Get command queue device.");
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		if (const HRESULT result = commandQueue->GetDevice(IID_PPV_ARGS(device.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Command queue device gotten.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 render target manager.");
		renderTarget.reset(new Direct3D12RenderTarget(device.Get(), buffers, rtvFormat));
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 render target manager created.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 root signature shader.");
		const auto rootSignatureShader = Direct3D12Shader("RootSignature");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 root signature shader loaded.");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 vertex shader.");
		const auto vertexShader = Direct3D12Shader("VertexShader");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 vertex shader loaded.");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Load Direct3D 12 pixel shader.");
		const auto pixelShader = Direct3D12Shader("PixelShader");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 pixel shader loaded.");
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 material.");
		material.reset(new Direct3D12Material(device.Get(), rootSignatureShader, vertexShader, pixelShader, rtvFormat));
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material created.");
	}

	void Direct3D12GraphicsPipeline::PopulateCommands(const UINT bufferIndex) const
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

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set camera view.");
		commandList->RSSetViewports(1, &camera->ViewPort());
		commandList->RSSetScissorRects(1, &camera->ViewRect());

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

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render targets.");
		const D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = renderTarget->GetRtvHandle(bufferIndex);
		commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set clear color to {}.", renderTarget->ClearColor().ToString());
		commandList->ClearRenderTargetView(rtvHandle, renderTarget->ClearColor().Span().data(), 0, nullptr);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set pipeline state.");
		commandList->SetGraphicsRootSignature(material->GetRootSignature());
		commandList->SetPipelineState(material->GetPipelineState());
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		const PonyMath::Core::Matrix4x4<FLOAT> vp = camera->ProjectionMatrix() * camera->TrsMatrix().Inverse();

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render objects.");
		for (auto renderObject = renderObjectManager->RenderObjectBegin(); renderObject != renderObjectManager->RenderObjectEnd(); ++renderObject)
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render object with '{}' id.", renderObject->first.id);
			const Direct3D12Mesh& renderMesh = renderObject->second.RenderMesh();
			commandList->IASetVertexBuffers(0, 1, &renderMesh.VerticesView());
			commandList->IASetVertexBuffers(1, 1, &renderMesh.VertexColorsView());
			commandList->IASetIndexBuffer(&renderMesh.VertexIndicesView());
			const PonyMath::Core::Matrix4x4<FLOAT> mvp = vp * renderObject->second.TrsMatrix();
			commandList->SetGraphicsRoot32BitConstants(0, mvp.ComponentCount, mvp.Span().data(), 0);
			commandList->DrawIndexedInstanced(renderMesh.IndexCount(), 1, 0, 0, 0);
		}

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

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Close command list.");
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12GraphicsPipeline::Execute() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command list.");
		ID3D12CommandList* const commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(1, commandLists);
	}

	void Direct3D12GraphicsPipeline::WaitForEndOfFrame() const
	{
		fence->Wait();
	}

	RenderObjectHandle Direct3D12GraphicsPipeline::CreateRenderObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& trs) const
	{
		const Direct3D12Mesh renderMesh = meshManager->CreateDirect3D12Mesh(mesh);

		return renderObjectManager->CreateRenderObject(renderMesh, trs);
	}

	void Direct3D12GraphicsPipeline::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) const noexcept
	{
		renderObjectManager->DestroyRenderObject(renderObjectHandle);
	}

	void Direct3D12GraphicsPipeline::UpdateRenderObjectTrs(const RenderObjectHandle handle, const PonyMath::Core::Matrix4x4<FLOAT>& trs) const noexcept
	{
		renderObjectManager->UpdateRenderObjectTrs(handle, trs);
	}
}
