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

		/// @brief Gets the fence.
		/// @return Fence.
		[[nodiscard("Pure function")]]
		ID3D12Fence1& ControlledFence() noexcept;
		/// @brief Gets the fence.
		/// @return Fence.
		[[nodiscard("Pure function")]]
		const ID3D12Fence1& ControlledFence() const noexcept;

		/// @brief Gets the current fence value.
		/// @return Current fence value.
		[[nodiscard("Pure function")]]
		UINT64 CurrentValue() const noexcept;
		/// @brief Gets the completed fence value.
		/// @return Completed fence value.
		[[nodiscard("Pure function")]]
		UINT64 CompletedValue() const noexcept;

		/// @brief Sets the name to the fence components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Increases the current fence value and signals the fence.
		void Signal();
		/// @brief Sets the waiting event.
		/// @param fenceValue Fence value to wait for.
		/// @param event Waiting event.
		void SetEvent(UINT64 fenceValue, HANDLE event) const;

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

	ID3D12Fence1& Fence::ControlledFence() noexcept
	{
		return *fence.Get();
	}

	const ID3D12Fence1& Fence::ControlledFence() const noexcept
	{
		return *fence.Get();
	}

	UINT64 Fence::CurrentValue() const noexcept
	{
		return currentValue;
	}

	UINT64 Fence::CompletedValue() const noexcept
	{
		return fence->GetCompletedValue();
	}

	void Fence::Name(const std::string_view name)
	{
		constexpr std::string_view fenceName = " - Fence";

		auto componentName = std::string();
		componentName.reserve(name.size() + fenceName.size());
		componentName.append(name).append(fenceName);
		SetName(*fence.Get(), componentName);
	}

	void Fence::Signal()
	{
		++currentValue;
		if (const HRESULT result = commandQueue->Signal(fence.Get(), currentValue); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to signal command queue with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
		}
	}

	void Fence::SetEvent(const UINT64 fenceValue, const HANDLE event) const
	{
		if (const HRESULT result = fence->SetEventOnCompletion(fenceValue, event); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set event on completion with '0x{:X}' result", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
