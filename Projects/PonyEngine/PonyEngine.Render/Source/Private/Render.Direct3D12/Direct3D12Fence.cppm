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

import :IDirect3D12RenderContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 fence.
	class Direct3D12Fence final
	{
	public:
		/// @brief Creates a @p Direct3D12Fence.
		/// @param render Render context.
		/// @param commandQueue Command queue.
		[[nodiscard("Pure constructor")]]
		Direct3D12Fence(IDirect3D12RenderContext& render, ID3D12CommandQueue& commandQueue);
		Direct3D12Fence(const Direct3D12Fence&) = delete;
		[[nodiscard("Pure constructor")]]
		Direct3D12Fence(Direct3D12Fence&& other) noexcept = default;

		~Direct3D12Fence() noexcept;

		/// @brief Gets the fence.
		/// @return Fence.
		[[nodiscard("Pure function")]]
		ID3D12Fence1& Fence() noexcept;
		/// @brief Gets the fence.
		/// @return Fence.
		[[nodiscard("Pure function")]]
		const ID3D12Fence1& Fence() const noexcept;

		/// @brief Gets the current fence value.
		/// @return Current fence value.
		[[nodiscard("Pure function")]]
		UINT64 CurrentValue() const noexcept;
		/// @brief Gets the completed fence value.
		/// @return Completed fence value.
		[[nodiscard("Pure function")]]
		UINT64 CompletedValue() const noexcept;

		/// @brief Increases the current fence value and signals the fence.
		void Signal();
		/// @brief Sets the waiting event.
		/// @param fenceValue Fence value to wait for.
		/// @param event Waiting event.
		void SetEvent(UINT64 fenceValue, HANDLE event) const;

		Direct3D12Fence& operator =(const Direct3D12Fence&) = delete;
		Direct3D12Fence& operator =(Direct3D12Fence&& other) noexcept = default;

	private:
		UINT64 currentValue; ///< Current fence value.

		IDirect3D12RenderContext* render; ///< Render context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Command queue.
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence; ///< Fence.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Fence::Direct3D12Fence(IDirect3D12RenderContext& render, ID3D12CommandQueue& commandQueue) :
		currentValue{0LL},
		render{&render},
		commandQueue(&commandQueue)
	{
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Acquire fence. Fence value: '{}'", currentValue);
		if (const HRESULT result = this->render->Device().CreateFence(currentValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Fence acquired at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(fence.Get()));
	}

	Direct3D12Fence::~Direct3D12Fence() noexcept
	{
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release fence.");
		fence.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Fence released.");

		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Release command queue.");
		commandQueue.Reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Command queue released.");
	}

	ID3D12Fence1& Direct3D12Fence::Fence() noexcept
	{
		return *fence.Get();
	}

	const ID3D12Fence1& Direct3D12Fence::Fence() const noexcept
	{
		return *fence.Get();
	}

	UINT64 Direct3D12Fence::CurrentValue() const noexcept
	{
		return currentValue;
	}

	UINT64 Direct3D12Fence::CompletedValue() const noexcept
	{
		return fence->GetCompletedValue();
	}

	void Direct3D12Fence::Signal()
	{
		++currentValue;
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Verbose, "Signal command queue. Fence value: '{}'.", currentValue);
		if (const HRESULT result = commandQueue->Signal(fence.Get(), currentValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
		}
	}

	void Direct3D12Fence::SetEvent(const UINT64 fenceValue, const HANDLE event) const
	{
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Verbose, "Set fence event. Fence value: '{}'; Handle: '0x{:X}'.", fenceValue, reinterpret_cast<std::uintptr_t>(event));
		if (const HRESULT result = fence->SetEventOnCompletion(fenceValue, event); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set event on completion with '0x{:X}' result", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
