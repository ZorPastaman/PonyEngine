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

export module PonyEngine.Render.Direct3D12.Detail:CpuWaiter;

import <memory>;
import <stdexcept>;
import <string_view>;

import PonyBase.Utility;

import :Fence;
import :ISubSystemContext;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 cpu waiter.
	/// @details It's a wrapper over @p Direct3D12Fence that adds a wait event.
	class CpuWaiter final
	{
	public:
		/// @brief Creates a @p CpuWaiter.
		/// @param d3d12System Direct3D12 system context.
		/// @param commandQueue Command queue.
		/// @param waitTimeout Wait timeout.
		[[nodiscard("Pure constructor")]]
		CpuWaiter(ISubSystemContext& d3d12System, ID3D12CommandQueue& commandQueue, DWORD waitTimeout);
		CpuWaiter(const CpuWaiter&) = delete;
		CpuWaiter(CpuWaiter&&) = delete;

		~CpuWaiter() noexcept;

		/// @brief Waits for the command queue fence.
		void Wait();

		/// @brief Sets the name to the cpu waiter components.
		/// @param name Name.
		void Name(std::string_view name);

		CpuWaiter& operator =(const CpuWaiter&) = delete;
		CpuWaiter& operator =(CpuWaiter&&) = delete;

	private:
		DWORD waitTimeout; ///< Wait timeout.

		ISubSystemContext* d3d12System; ///< Direct3D12 system context.

		std::unique_ptr<Fence> fence; ///< Fence.
		HANDLE waitEvent; ///< Wait event.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	CpuWaiter::CpuWaiter(ISubSystemContext& d3d12System, ID3D12CommandQueue& commandQueue, const DWORD waitTimeout) :
		waitTimeout{waitTimeout},
		d3d12System{&d3d12System},
		fence(std::make_unique<Fence>(d3d12System, commandQueue))
	{
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Create wait event.");
		if (!((waitEvent = CreateEventA(nullptr, false, false, nullptr)))) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create wait event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->d3d12System->Logger(), PonyDebug::Log::LogType::Info, "Wait event created.");
	}

	CpuWaiter::~CpuWaiter() noexcept
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

	void CpuWaiter::Wait()
	{
		fence->Signal();
		fence->Wait(waitEvent, waitTimeout);
	}

	void CpuWaiter::Name(const std::string_view name)
	{
		fence->Name(name);
	}
}
