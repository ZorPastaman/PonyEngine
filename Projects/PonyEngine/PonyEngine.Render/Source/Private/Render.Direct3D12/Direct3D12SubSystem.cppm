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

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <utility>;
import <vector>;

import PonyBase.Math;
import PonyBase.GuidUtility;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		Direct3D12SubSystem(IRenderer& renderer, UINT bufferCount, DXGI_FORMAT rtvFormat, D3D_FEATURE_LEVEL featureLevel, INT commandQueuePriority, DWORD fenceTimeout);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		[[nodiscard("Pure function")]]
		UINT& BufferIndex() noexcept;
		[[nodiscard("Pure function")]]
		const UINT& BufferIndex() const noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Math::RGBA<FLOAT>& ClearColor() noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Math::RGBA<FLOAT>& ClearColor() const noexcept;

		[[nodiscard("Pure function")]]
		ID3D12CommandQueue* GetCommandQueue() const;

		[[nodiscard("Pure function")]]
		ID3D12Resource2* GetBuffer(UINT targetBufferIndex) const noexcept;
		[[nodiscard("Pure function")]]
		ID3D12Resource2** GetBufferPointer(UINT targetBufferIndex) const noexcept;

		void Initialize() const;

		void PopulateCommands();
		void Execute() const;
		void WaitForEndOfFrame();

		[[nodiscard("Won't be able to destroy")]]
		IRenderObject& CreateRenderObject(const Mesh& mesh);
		void DestroyRenderObject(IRenderObject& renderObject) noexcept;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		GUID AcquireGuid() const;

		[[nodiscard("Pure function")]]
		std::unique_ptr<Microsoft::WRL::ComPtr<ID3D12Resource2>[]> CreateBuffers() const;

		[[nodiscard("Pure function")]]
		std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE[]> CreateRtvHandles() const;

		void ReleaseBuffers() const noexcept;

		UINT bufferCount;
		UINT bufferIndex;

		DXGI_FORMAT rtvFormat;
		PonyBase::Math::RGBA<FLOAT> clearColor;

		UINT64 fenceValue;
		DWORD fenceTimeout;

		IRenderer* renderer;

		GUID guid;

		HANDLE fenceEvent;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device; // TODO: Split the subsystem to pipeline and data
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;

		std::unique_ptr<Microsoft::WRL::ComPtr<ID3D12Resource2>[]> buffers;

		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE[]> rtvHandles;

		Microsoft::WRL::ComPtr<ID3D12Fence1> fence;

		std::vector<Direct3D12RenderObject> renderObjects;
		std::size_t nextId;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRenderer& renderer, const UINT bufferCount, const DXGI_FORMAT rtvFormat, const D3D_FEATURE_LEVEL featureLevel, const INT commandQueuePriority, const DWORD fenceTimeout) :
		bufferCount{bufferCount},
		bufferIndex{0u},
		rtvFormat{rtvFormat},
		clearColor(PonyBase::Math::RGBA<FLOAT>::Predefined::Black),
		fenceValue{0LL},
		fenceTimeout{fenceTimeout},
		renderer{&renderer},
		guid{AcquireGuid()},
		buffers{CreateBuffers()},
		rtvHandles{CreateRtvHandles()},
		nextId{0}
	{
		constexpr D3D12_COMMAND_LIST_TYPE commandListType = D3D12_COMMAND_LIST_TYPE_DIRECT;

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create fence event.");
		if ((fenceEvent = CreateEventA(nullptr, false, false, nullptr)) == nullptr) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create fence event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Fence event created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fenceEvent));

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

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 rtv descriptors.");
		const auto rtvDescriptorHeapDescriptor = D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = bufferCount,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
		if (const HRESULT result = device->CreateDescriptorHeap(&rtvDescriptorHeapDescriptor, IID_PPV_ARGS(rtvDescriptorHeap.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire rtv descriptor heap with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		rtvHandles[0].ptr = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr;
		const UINT rtvDescriptorHandleIncrement = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		for (UINT i = 1u; i < bufferCount; ++i)
		{
			rtvHandles[i].ptr = rtvHandles[i - 1].ptr + rtvDescriptorHandleIncrement;
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 rtv descriptors acquired.");

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 fence.");
		if (const HRESULT result = device->CreateFence(fenceValue++, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 fence.");
		fence.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 rtv descriptors.");
		rtvHandles.reset();
		rtvDescriptorHeap.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 rtv descriptors released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 buffers.");
		ReleaseBuffers();
		buffers.reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 buffers released.");

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

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Close fence event.");
		if (!CloseHandle(fenceEvent)) [[unlikely]]
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Error, "Failed to close fence event. Error code: '0x{:X}'", GetLastError());
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Fence event closed.");
	}

	UINT& Direct3D12SubSystem::BufferIndex() noexcept
	{
		return bufferIndex;
	}

	const UINT& Direct3D12SubSystem::BufferIndex() const noexcept
	{
		return bufferIndex;
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

	ID3D12Resource2* Direct3D12SubSystem::GetBuffer(const UINT targetBufferIndex) const noexcept
	{
		return buffers[targetBufferIndex].Get();
	}

	ID3D12Resource2** Direct3D12SubSystem::GetBufferPointer(const UINT targetBufferIndex) const noexcept
	{
		return buffers[targetBufferIndex].GetAddressOf();
	}

	void Direct3D12SubSystem::Initialize() const
	{
		const auto rtvDescription = D3D12_RENDER_TARGET_VIEW_DESC
		{
			.Format = rtvFormat,
			.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = D3D12_TEX2D_RTV{.MipSlice = 0u, .PlaneSlice = 0u}
		};

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create render target views.");
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			device->CreateRenderTargetView(buffers[i].Get(), &rtvDescription, rtvHandles[i]);
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Render target views created.");
	}

	void Direct3D12SubSystem::PopulateCommands()
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

		const auto renderTargetBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = buffers[bufferIndex].Get(),
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
				.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as render target.", reinterpret_cast<std::uintptr_t>(buffers[bufferIndex].Get()), bufferIndex);
		commandList->ResourceBarrier(1, &renderTargetBarrier);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set render targets.");
		commandList->OMSetRenderTargets(1, &rtvHandles[bufferIndex], false, nullptr);

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set clear color.");
		commandList->ClearRenderTargetView(rtvHandles[bufferIndex], clearColor.Span().data(), 0, nullptr);

		const auto presentBarrier = D3D12_RESOURCE_BARRIER
		{
			.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
			.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
			.Transition = D3D12_RESOURCE_TRANSITION_BARRIER
			{
				.pResource = buffers[bufferIndex].Get(),
				.Subresource = 0,
				.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
				.StateAfter = D3D12_RESOURCE_STATE_PRESENT
			}
		};
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Set back buffer at '0x{:X}' at index '{}' as present.", reinterpret_cast<std::uintptr_t>(buffers[bufferIndex].Get()), bufferIndex);
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

	void Direct3D12SubSystem::WaitForEndOfFrame()
	{
		const UINT64 currentFenceValue = fenceValue++;
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Signal command queue. Fence value: '{}'.", currentFenceValue);
		if (const HRESULT result = commandQueue->Signal(fence.Get(), currentFenceValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentFenceValue));
		}

		if (fence->GetCompletedValue() < currentFenceValue)
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "Wait for fence. Fence value: '{}'. Timeout: '{} ms'.", currentFenceValue, fenceTimeout);
			if (const HRESULT result = fence->SetEventOnCompletion(currentFenceValue, fenceEvent); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set event on completion with '0x{:X}' result", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
			if (const DWORD result = WaitForSingleObjectEx(fenceEvent, fenceTimeout, false); result != WAIT_OBJECT_0) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to wait for fence event with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}
		else
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Verbose, "No need to wait for fence.");
		}
	}

	IRenderObject& Direct3D12SubSystem::CreateRenderObject(const Mesh& mesh)
	{
		return renderObjects.emplace_back(mesh, nextId++);
	}

	void Direct3D12SubSystem::DestroyRenderObject(IRenderObject& renderObject) noexcept // TODO: Change to unique_ptr
	{
		for (std::size_t i = 0; i < renderObjects.size(); ++i)
		{
			if (renderObjects[i].Id() == renderObject.Id())
			{
				renderObjects.erase(renderObjects.begin() + i);
				break;
			}
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

	std::unique_ptr<Microsoft::WRL::ComPtr<ID3D12Resource2>[]> Direct3D12SubSystem::CreateBuffers() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create buffer array. Buffer count: '{}'.", bufferCount);
		auto resourceBuffers = std::unique_ptr<Microsoft::WRL::ComPtr<ID3D12Resource2>[]>(new Microsoft::WRL::ComPtr<ID3D12Resource2>[bufferCount]);
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			resourceBuffers[i] = Microsoft::WRL::ComPtr<ID3D12Resource2>();
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Buffer array created.");

		return resourceBuffers;
	}

	std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE[]> Direct3D12SubSystem::CreateRtvHandles() const
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Create RTV handle array. Buffer count: '{}'.", bufferCount);
		auto createdRtvHandles = std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE[]>(new D3D12_CPU_DESCRIPTOR_HANDLE[bufferCount]);
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			createdRtvHandles[i] = D3D12_CPU_DESCRIPTOR_HANDLE();
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "RTV handle array created.");

		return createdRtvHandles;
	}

	void Direct3D12SubSystem::ReleaseBuffers() const noexcept
	{
		for (UINT i = 0u; i < bufferCount; ++i)
		{
			buffers[i].Reset();
		}
	}
}
