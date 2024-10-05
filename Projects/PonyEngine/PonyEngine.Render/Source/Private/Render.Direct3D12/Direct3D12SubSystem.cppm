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

export module PonyEngine.Render.Direct3D12:Direct3D12SubSystem;

import <cstddef>;
import <cstdint>;
import <filesystem>;
import <fstream>;
import <memory>;
import <ranges>;
import <span>;
import <stdexcept>;
import <type_traits>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyBase.Geometry;
import PonyBase.Math;
import PonyBase.GuidUtility;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

import :Direct3D12Camera;
import :Direct3D12Fence;
import :Direct3D12Material;
import :Direct3D12Mesh;
import :Direct3D12MeshHelper;
import :Direct3D12RenderObject;
import :Direct3D12Shader;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem(IRenderer& renderer, D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Math::RGBA<FLOAT>& ClearColor() noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Math::RGBA<FLOAT>& ClearColor() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		void Initialize(const PonyBase::Math::Vector2<UINT>& resolution, DXGI_FORMAT rtvFormat, std::span<const Microsoft::WRL::ComPtr<ID3D12Resource2>> buffers);

		void PopulateCommands(UINT bufferIndex);
		void Execute() const;
		void WaitForEndOfFrame() const;

		RenderObjectHandle CreateRenderObject(const PonyBase::Geometry::Mesh& mesh);
		void DestroyRenderObject(RenderObjectHandle renderObjectHandle) noexcept;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		GUID AcquireGuid() const;

		PonyBase::Math::RGBA<FLOAT> clearColor;

		IRenderer* renderer;

		GUID guid;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device; // TODO: Split the subsystem to pipeline and data
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;
		std::unique_ptr<Direct3DFence> fence;

		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource2>> backBuffers;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;

		std::unique_ptr<Direct3D12Camera> camera;

		std::unique_ptr<Direct3D12Material> material;

		std::unordered_map<RenderObjectHandle, Direct3D12RenderObject, RenderObjectHandleHash> renderObjects;
		std::size_t nextRenderObjectId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRenderer& renderer, const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout) :
		clearColor(PonyBase::Math::RGBA<FLOAT>::Predefined::Black),
		renderer{&renderer},
		guid{AcquireGuid()},
		nextRenderObjectId{1}
	{
		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

#ifdef _DEBUG
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 debug interface with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Debug, "Enable Direct3D 12 debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 device. Feature level: '0x{:X}.'", static_cast<unsigned int>(featureLevel));
		if (const HRESULT result = D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(device.Get()));

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

		fence.reset(new Direct3DFence(*this->renderer, commandQueue.Get(), fenceTimeout));
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 material.");
		material.reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 material released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 camera.");
		camera.reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 camera released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 rtv handles.");
		rtvHandles.clear();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 rtv handles released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 back buffers.");
		backBuffers.clear();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 back buffers released.");

		fence.reset();

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command list.");
		commandList.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command list released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command allocator.");
		commandAllocator.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command allocator released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command queue.");
		commandQueue.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 device.");
		device.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device released.");

#ifdef _DEBUG
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 debug interface.");
		debug.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface released.");
#endif
	}

	PonyBase::Math::RGBA<FLOAT>& Direct3D12SubSystem::ClearColor() noexcept
	{
		return clearColor;
	}

	const PonyBase::Math::RGBA<FLOAT>& Direct3D12SubSystem::ClearColor() const noexcept
	{
		return clearColor;
	}

	ID3D12CommandQueue* Direct3D12SubSystem::GetCommandQueue() const
	{
		return commandQueue.Get();
	}

	void Direct3D12SubSystem::Initialize(const PonyBase::Math::Vector2<UINT>& resolution, const DXGI_FORMAT rtvFormat, const std::span<const Microsoft::WRL::ComPtr<ID3D12Resource2>> buffers)
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Set Direct3D 12 camera with resolution of '{}'.", resolution.ToString());
		camera.reset(new Direct3D12Camera(resolution));

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Set back buffers.");
		backBuffers.resize(buffers.size());
		for (std::size_t i = 0; i < backBuffers.size(); ++i)
		{
			backBuffers[i] = buffers[i];
		}

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 rtv handles.");
		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = static_cast<UINT>(buffers.size()),
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device->CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(rtvDescriptorHeap.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvHandles.resize(buffers.size());
		rtvHandles[0].ptr = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for (std::size_t i = 1; i < rtvHandles.size(); ++i)
		{
			rtvHandles[i].ptr = rtvHandles[i - 1].ptr + rtvDescriptorHandleIncrement;
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 rtv descriptors acquired.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create render target views.");
		const auto rtvDescription = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{}
		};
		for (std::size_t i = 0; i < buffers.size(); ++i)
		{
			device->CreateRenderTargetView(buffers[i].Get(), &rtvDescription, rtvHandles[i]);
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render target views created.");

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

	void Direct3D12SubSystem::PopulateCommands(const UINT bufferIndex)
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

		commandList->RSSetViewports(1, &camera->ViewPort());
		commandList->RSSetScissorRects(1, &camera->ViewRect());

		const auto renderTargetBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = backBuffers[bufferIndex].Get(),
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
				.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as render target.", reinterpret_cast<std::uintptr_t>(backBuffers[bufferIndex].Get()), bufferIndex);
		commandList->ResourceBarrier(1, &renderTargetBarrier);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render targets.");
		commandList->OMSetRenderTargets(1, &rtvHandles[bufferIndex], false, nullptr);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set clear color.");
		commandList->ClearRenderTargetView(rtvHandles[bufferIndex], clearColor.Span().data(), 0, nullptr);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set pipeline state.");
		commandList->SetPipelineState(material->GetPipelineState());

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render objects.");
		for (const auto& renderObject : renderObjects)
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render object with '{}' id.", renderObject.first.id);
			const Direct3D12Mesh& renderMesh = renderObject.second.MeshResource(); // TODO: rename meshResource to renderMesh.
			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			commandList->IASetVertexBuffers(0, 1, &renderMesh.VerticesView());
			commandList->IASetVertexBuffers(1, 1, &renderMesh.VertexColorsView());
			commandList->IASetIndexBuffer(&renderMesh.VertexIndicesView());
			commandList->DrawIndexedInstanced(renderMesh.IndexCount(), 1, 0, 0, 0);
		}

		const auto presentBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = backBuffers[bufferIndex].Get(),
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
				.StateAfter = D3D12_RESOURCE_STATE_PRESENT
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as present.", reinterpret_cast<std::uintptr_t>(backBuffers[bufferIndex].Get()), bufferIndex);
		commandList->ResourceBarrier(1, &presentBarrier);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Close command list.");
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to close command list with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Direct3D12SubSystem::Execute() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Execute command list.");
		ID3D12CommandList* const commandLists[] = { commandList.Get() };
		commandQueue->ExecuteCommandLists(1, commandLists);
	}

	void Direct3D12SubSystem::WaitForEndOfFrame() const
	{
		fence->Wait();
	}

	RenderObjectHandle Direct3D12SubSystem::CreateRenderObject(const PonyBase::Geometry::Mesh& mesh)
	{
		const size_t id = nextRenderObjectId++;

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create render mesh.");
		const auto renderMesh = CreateDirect3D12Mesh(device.Get(), mesh);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render mesh created.");

		renderObjects.emplace(id, renderMesh);
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render object created. ID: '{}'.", id);

		return RenderObjectHandle{.id = id};
	}

	void Direct3D12SubSystem::DestroyRenderObject(const RenderObjectHandle renderObjectHandle) noexcept
	{
		if (const auto position = renderObjects.find(renderObjectHandle); position != renderObjects.cend()) [[likely]]
		{
			renderObjects.erase(position);
		}
	}

	GUID Direct3D12SubSystem::AcquireGuid() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire guid.");
		GUID acquiredGuid;
		if (const HRESULT result = CoCreateGuid(&acquiredGuid); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get guid for Direct3D 12 render system with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "'{}' guid acquired.", PonyBase::Utility::ToString(acquiredGuid));

		return acquiredGuid;
	}
}
