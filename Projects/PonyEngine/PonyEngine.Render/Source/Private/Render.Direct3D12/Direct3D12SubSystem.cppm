/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

#include "PonyEngine/Render/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12:Direct3D12SubSystem;

import <cstdint>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;

import PonyEngine.Render.Core;

export namespace PonyEngine::Render
{
	/// @brief Direct3D 12 sys-system.
	class Direct3D12SubSystem final
	{
	public:
		[[nodiscard("Pure function")]]
		explicit Direct3D12SubSystem(IRenderer& renderer);
		Direct3D12SubSystem(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem(Direct3D12SubSystem&&) = delete;

		~Direct3D12SubSystem() noexcept;

		Direct3D12SubSystem& operator =(const Direct3D12SubSystem&) = delete;
		Direct3D12SubSystem& operator =(Direct3D12SubSystem&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		static GUID GetGuid();

		UINT64 fenceValue;

		IRenderer* renderer;

		GUID guid;

#ifdef _DEBUG
		Microsoft::WRL::ComPtr<ID3D12Debug6> debug;
#endif
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence;
	};
}

namespace PonyEngine::Render
{
	Direct3D12SubSystem::Direct3D12SubSystem(IRenderer& renderer) :
		fenceValue{0},
		renderer{&renderer},
		guid{GetGuid()}
	{
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "'{:X}-{:X}-{:X}-{:X}' guid gotten for Direct3D 12 render system.", guid.Data1, guid.Data2, guid.Data3, *reinterpret_cast<std::uint64_t*>(guid.Data4));

#ifdef _DEBUG
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 debug interface.");
		if (const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(debug.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 debug interface with '0x{:X}' result.", result));
		}
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(debug.Get()));

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Debug, "Enable Direct3D 12 debug layer.");
		debug->EnableDebugLayer();
#endif

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 device.");
		if (const HRESULT result = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(device.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create Direct3D 12 device with '0x{:X}' result.", result));
		}
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(device.Get()));

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 command queue.");
		constexpr auto commandQueueDescription = D3D12_COMMAND_QUEUE_DESC
		{
			.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
			.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
			.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
			.NodeMask = 0
		};
		if (const HRESULT result = device->CreateCommandQueue1(&commandQueueDescription, guid, IID_PPV_ARGS(commandQueue.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create Direct3D 12 command queue with '0x{:X}' result.", result));
		}
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(commandQueue.Get()));

		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Create Direct3D 12 fence.");
		if (const HRESULT result = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create Direct3D 12 fence with '0x{:X}' result.", result));
		}
		PONY_LOG(this->renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));
	}

	Direct3D12SubSystem::~Direct3D12SubSystem() noexcept
	{
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 fence.");
		fence.Reset();
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence destroyed.");

		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 command queue.");
		commandQueue.Reset();
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue destroyed.");

		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 device.");
		device.Reset();
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 device destroyed.");

#ifdef _DEBUG
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 debug interface.");
		debug.Reset();
		PONY_LOG(renderer->Engine().Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 debug interface destroyed.");
#endif
	}

	GUID Direct3D12SubSystem::GetGuid()
	{
		GUID guid;
		if (const HRESULT result = CoCreateGuid(&guid); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get guid for Direct3D 12 render system with '0x{:X}' result.", result));
		}

		return guid;
	}
}
