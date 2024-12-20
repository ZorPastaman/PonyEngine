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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12GpuWaiter;

import <cstdint>;
import <memory>;
import <stdexcept>;
import <type_traits>;

import :Direct3D12Fence;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 gpu waiter.
	/// @details It makes a command queue to wait for another command queue.
	class Direct3D12GpuWaiter final
	{
	public:
		/// @brief Creates a @p Direct3D12GpuWaiter.
		/// @param d3d12System Direct3D12 system context.
		/// @param waitedCommandQueue Waited command queue.
		/// @param waitingCommandQueue Waiting command queue.
		[[nodiscard("Pure constructor")]]
		Direct3D12GpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& waitingCommandQueue);
		Direct3D12GpuWaiter(const Direct3D12GpuWaiter&) = delete;
		Direct3D12GpuWaiter(Direct3D12GpuWaiter&&) = delete;

		~Direct3D12GpuWaiter() noexcept;

		/// @brief Sets the name to the cpu waiter components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Submit a wait command.
		void Wait();

		Direct3D12GpuWaiter& operator =(const Direct3D12GpuWaiter&) = delete;
		Direct3D12GpuWaiter& operator =(Direct3D12GpuWaiter&&) = delete;

	private:
		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::unique_ptr<Direct3D12Fence> fence; ///< Fence.
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> waitingCommandQueue; ///< Waiting command queue.
	};
}

namespace PonyEngine::Render
{
	Direct3D12GpuWaiter::Direct3D12GpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& waitedCommandQueue, ID3D12CommandQueue& waitingCommandQueue) :
		d3d12System{&d3d12System},
		fence(std::make_unique<Direct3D12Fence>(d3d12System, waitedCommandQueue)),
		waitingCommandQueue(&waitingCommandQueue)
	{
	}

	Direct3D12GpuWaiter::~Direct3D12GpuWaiter() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Release waiting command queue.");
		waitingCommandQueue.Reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Waiting command queue released.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy fence.");
		fence.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Fence destroyed.");
	}

	void Direct3D12GpuWaiter::Name(const std::string_view name)
	{
		fence->Name(name);
	}

	void Direct3D12GpuWaiter::Wait()
	{
		fence->Signal();

		if (const UINT64 currentValue = fence->CurrentValue(); fence->CompletedValue() < currentValue)
		{
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "Set wait. Fence value: {}.", currentValue);
			if (const HRESULT result = waitingCommandQueue->Wait(&fence->Fence(), currentValue); FAILED(result))
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to set gpu wait with '0x{:X}' result. Fence value: '{}'.", static_cast<std::make_unsigned_t<HRESULT>>(result), currentValue));
			}
		}
		else
		{
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Verbose, "No need to wait for fence.");
		}
	}
}
