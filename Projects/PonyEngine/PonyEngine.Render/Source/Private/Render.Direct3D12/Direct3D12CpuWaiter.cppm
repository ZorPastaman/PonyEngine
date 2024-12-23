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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12CpuWaiter;

import <memory>;
import <stdexcept>;
import <string>;
import <string_view>;
import <type_traits>;

import PonyBase.StringUtility;

import :Direct3D12Fence;
import :IDirect3D12SystemContext;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 cpu waiter.
	/// @details It's a wrapper over @p Direct3D12Fence that adds a wait event.
	class Direct3D12CpuWaiter final
	{
	public:
		/// @brief Creates a @p Direct3D12CpuWaiter.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueue Command queue.
		/// @param waitTimeout Wait timeout.
		[[nodiscard("Pure constructor")]]
		Direct3D12CpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& commandQueue, DWORD waitTimeout);
		Direct3D12CpuWaiter(const Direct3D12CpuWaiter&) = delete;
		Direct3D12CpuWaiter(Direct3D12CpuWaiter&&) = delete;

		~Direct3D12CpuWaiter() noexcept;

		/// @brief Sets the name to the cpu waiter components.
		/// @param name Name.
		void Name(std::string_view name);

		/// @brief Waits for the command queue fence.
		void Wait();

		Direct3D12CpuWaiter& operator =(const Direct3D12CpuWaiter&) = delete;
		Direct3D12CpuWaiter& operator =(Direct3D12CpuWaiter&&) = delete;

	private:
		DWORD waitTimeout; ///< Wait timeout.

		IDirect3D12SystemContext* d3d12System; ///< Direct3D12 system context.

		std::unique_ptr<Direct3D12Fence> fence; ///< Fence.
		HANDLE waitEvent; ///< Wait event.
	};
}

namespace PonyEngine::Render
{
	Direct3D12CpuWaiter::Direct3D12CpuWaiter(IDirect3D12SystemContext& d3d12System, ID3D12CommandQueue& commandQueue, const DWORD waitTimeout) :
		waitTimeout{waitTimeout},
		d3d12System{&d3d12System},
		fence(std::make_unique<Direct3D12Fence>(d3d12System, commandQueue))
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create wait event.");
		if ((waitEvent = CreateEventA(nullptr, false, false, nullptr)) == nullptr) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create wait event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Wait event created.");
	}

	Direct3D12CpuWaiter::~Direct3D12CpuWaiter() noexcept
	{
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Close wait event.");
		if (!CloseHandle(waitEvent)) [[unlikely]]
		{
			PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Error, "Failed to close wait event. Error code: '0x{:X}'", GetLastError());
		}
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Wait event closed.");

		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Destroy fence.");
		fence.reset();
		PONY_LOG(d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Fence destroyed.");
	}

	void Direct3D12CpuWaiter::Name(const std::string_view name)
	{
		fence->Name(name);
	}

	void Direct3D12CpuWaiter::Wait()
	{
		fence->Signal();

		if (const UINT64 currentFenceValue = fence->CurrentValue(); fence->CompletedValue() < currentFenceValue)
		{
			fence->SetEvent(currentFenceValue, waitEvent);
			if (const DWORD result = WaitForSingleObjectEx(waitEvent, waitTimeout, false); result != WAIT_OBJECT_0) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to wait for fence event with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}
	}
}
