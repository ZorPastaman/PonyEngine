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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Fence;

import <cstdint>;
import <stdexcept>;
import <type_traits>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Render.Direct3D12;
import PonyEngine.Render.Detail;

export namespace PonyEngine::Render
{
	class Direct3D12Fence final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Fence(IRenderContext& render, ID3D12CommandQueue* commandQueue);
		Direct3D12Fence(const Direct3D12Fence&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12Fence(Direct3D12Fence&& other) noexcept = default;

		~Direct3D12Fence() noexcept;

		[[nodiscard("Pure function")]]
		UINT64 CurrentFenceValue() const noexcept;
		[[nodiscard("Pure function")]]
		UINT64 CompletedFenceValue() const noexcept;

		void Signal();
		void SetEvent(UINT64 fenceValue, HANDLE event);

		Direct3D12Fence& operator =(const Direct3D12Fence&) = delete;
		Direct3D12Fence& operator =(Direct3D12Fence&&) noexcept = default;

	private:
		UINT64 currentFenceValue;

		IRenderContext* render;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Fence::Direct3D12Fence(IRenderContext& render, ID3D12CommandQueue* const commandQueue) :
		currentFenceValue{0LL},
		render{&render},
		commandQueue(commandQueue)
	{
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Get command queue device.");
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		if (const HRESULT result = this->commandQueue->GetDevice(IID_PPV_ARGS(device.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to get Direct3D 12 device with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Command queue device gotten.");

		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Acquire Direct3D 12 fence.");
		if (const HRESULT result = device->CreateFence(currentFenceValue++, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire Direct3D 12 fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));
	}

	Direct3D12Fence::~Direct3D12Fence() noexcept
	{
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 fence.");
		fence.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence released.");

		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release Direct3D 12 command queue.");
		commandQueue.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 command queue released.");
	}

	UINT64 Direct3D12Fence::CurrentFenceValue() const noexcept
	{
		return currentFenceValue;
	}

	UINT64 Direct3D12Fence::CompletedFenceValue() const noexcept
	{
		return fence->GetCompletedValue();
	}

	void Direct3D12Fence::Signal()
	{
		++currentFenceValue;
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Verbose, "Signal command queue. Fence value: '{}'.", currentFenceValue);
		if (const HRESULT result = commandQueue->Signal(fence.Get(), currentFenceValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentFenceValue));
		}
	}

	void Direct3D12Fence::SetEvent(const UINT64 fenceValue, const HANDLE event)
	{
		if (const HRESULT result = fence->SetEventOnCompletion(fenceValue, event); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set event on completion with '0x{:X}' result", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
