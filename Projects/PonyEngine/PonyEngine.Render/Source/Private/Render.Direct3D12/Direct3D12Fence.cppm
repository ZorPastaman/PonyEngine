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

export module PonyEngine.Render.Direct3D12:Direct3D12Fence;

import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Render;

import PonyEngine.Render.Core;

export namespace PonyEngine::Render
{
	class Direct3DFence final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3DFence(IRenderer& renderer, ID3D12CommandQueue* commandQueue, DWORD fenceTimeout);
		Direct3DFence(const Direct3DFence&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3DFence(Direct3DFence&& other) noexcept = default;

		~Direct3DFence() noexcept;

		void Wait();

		Direct3DFence& operator =(const Direct3DFence&) = delete;
		Direct3DFence& operator =(Direct3DFence&&) noexcept = default;

	private:
		UINT64 fenceValue;
		DWORD fenceTimeout;

		IRenderer* renderer;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

		HANDLE fenceEvent;
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence;
	};
}

namespace PonyEngine::Render
{
	Direct3DFence::Direct3DFence(IRenderer& renderer, ID3D12CommandQueue* const commandQueue, const DWORD fenceTimeout) :
		fenceValue{0LL},
		fenceTimeout{fenceTimeout},
		renderer{&renderer},
		commandQueue(commandQueue)
	{
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		if (const HRESULT result = commandQueue->GetDevice(IID_PPV_ARGS(device.GetAddressOf())); FAILED(result))
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Create fence event.");
		if ((fenceEvent = CreateEventA(nullptr, false, false, nullptr)) == nullptr) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create fence event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Fence event created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fenceEvent));

		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 fence.");
		if (const HRESULT result = device->CreateFence(fenceValue++, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));
	}

	Direct3DFence::~Direct3DFence() noexcept
	{
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 fence.");
		fence.Reset();
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence released.");

		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Close fence event.");
		if (!CloseHandle(fenceEvent)) [[unlikely]]
		{
			PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Error, "Failed to close fence event. Error code: '0x{:X}'", GetLastError());
		}
		PONY_LOG(renderer->Logger(), PonyDebug::Log::LogType::Info, "Fence event closed.");
	}

	void Direct3DFence::Wait()
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
}
