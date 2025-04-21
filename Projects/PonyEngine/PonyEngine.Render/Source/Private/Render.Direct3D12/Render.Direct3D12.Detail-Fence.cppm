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

export module PonyEngine.Render.Direct3D12.Detail:Fence;

import <cstdint>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.Utility;

import PonyDebug.Log;

import :ISubSystemContext;
import :ObjectUtility;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 fence.
	class Fence final
	{
	public:
		/// @brief Creates a @p Fence.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueue Command queue.
		[[nodiscard("Pure constructor")]]
		Fence(ISubSystemContext& d3d12System, ID3D12CommandQueue& commandQueue);
		Fence(const Fence&) = delete;
		[[nodiscard("Pure constructor")]]
		Fence(Fence&& other) noexcept = default;

		~Fence() noexcept;

		/// @brief Increases the current fence value and signals the fence.
		void Signal();
		/// @brief Sets the wait event and waits for it.
		/// @param waitEvent Wait event.
		/// @param waitTimeout Wait timeout.
		void Wait(HANDLE waitEvent, DWORD waitTimeout) const;
		/// @brief Sets the waiting command queue to wait for the fence.
		/// @param waitingCommandQueue Waiting command queue.
		void Wait(ID3D12CommandQueue& waitingCommandQueue) const;

		/// @brief Sets the name to the fence components.
		/// @param name Name.
		void Name(std::string_view name);

		Fence& operator =(const Fence&) = delete;
		Fence& operator =(Fence&& other) noexcept = default;

	private:
		UINT64 currentValue; ///< Current fence value.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue; ///< Command queue.
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence; ///< Fence.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Fence::Fence(ISubSystemContext& d3d12System, ID3D12CommandQueue& commandQueue) :
		currentValue{0LL},
		d3d12System{&d3d12System},
		commandQueue(&commandQueue)
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Acquire fence. Fence value: '{}'", currentValue);
		if (const HRESULT result = this->d3d12System->Device().CreateFence(currentValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to acquire fence with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Fence acquired.");
	}

	Fence::~Fence() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release fence.");
		fence.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Fence released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release command queue.");
		commandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Command queue released.");
	}

	void Fence::Signal()
	{
		++currentValue;
		if (const HRESULT result = commandQueue->Signal(fence.Get(), currentValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
		}
	}

	void Fence::Wait(const HANDLE waitEvent, const DWORD waitTimeout) const
	{
		if (fence->GetCompletedValue() < currentValue)
		{
			if (const HRESULT result = fence->SetEventOnCompletion(currentValue, waitEvent); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set fence event with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
			}

			if (const DWORD result = WaitForSingleObjectEx(waitEvent, waitTimeout, false); result != WAIT_OBJECT_0) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to wait for fence event with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
			}
		}
	}

	void Fence::Wait(ID3D12CommandQueue& waitingCommandQueue) const
	{
		if (fence->GetCompletedValue() < currentValue)
		{
			if (const HRESULT result = waitingCommandQueue.Wait(fence.Get(), currentValue); FAILED(result)) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set gpu wait with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
			}
		}
	}

	void Fence::Name(const std::string_view name)
	{
		SetName(*fence.Get(), name);
	}
}
