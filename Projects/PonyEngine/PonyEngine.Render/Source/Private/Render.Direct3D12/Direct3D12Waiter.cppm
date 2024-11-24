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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Waiter;

import <memory>;

import :Direct3D12Fence;
import :IDirect3D12RenderContext;

export namespace PonyEngine::Render
{
	class Direct3D12Waiter final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12Waiter(IDirect3D12RenderContext& render, ID3D12CommandQueue& commandQueue, DWORD waitTimeout);
		Direct3D12Waiter(const Direct3D12Waiter&) = delete;
		Direct3D12Waiter(Direct3D12Waiter&&) = delete;

		~Direct3D12Waiter() noexcept;

		void Wait();

		Direct3D12Waiter& operator =(const Direct3D12Waiter&) = delete;
		Direct3D12Waiter& operator =(Direct3D12Waiter&&) = delete;

	private:
		DWORD waitTimeout;

		IDirect3D12RenderContext* render;

		std::unique_ptr<Direct3D12Fence> fence;
		HANDLE waitEvent;
	};
}

namespace PonyEngine::Render
{
	Direct3D12Waiter::Direct3D12Waiter(IDirect3D12RenderContext& render, ID3D12CommandQueue& commandQueue, const DWORD waitTimeout) :
		waitTimeout{waitTimeout},
		render{&render},
		fence(std::make_unique<Direct3D12Fence>(render, commandQueue))
	{
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Create wait event.");
		if ((waitEvent = CreateEventA(nullptr, false, false, nullptr)) == nullptr) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to create wait event. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->render->Logger(), PonyDebug::Log::LogType::Info, "Wait event created at '0x{:X}'.", reinterpret_cast<std::uintptr_t>(waitEvent));
	}

	Direct3D12Waiter::~Direct3D12Waiter() noexcept
	{
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Close wait event.");
		if (!CloseHandle(waitEvent)) [[unlikely]]
		{
			PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Error, "Failed to close wait event. Error code: '0x{:X}'", GetLastError());
		}
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Wait event closed.");

		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Destroy Direct3D 12 fence.");
		fence.reset();
		PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Info, "Direct3D 12 fence destroyed.");
	}

	void Direct3D12Waiter::Wait()
	{
		fence->Signal();

		if (const UINT64 currentFenceValue = fence->CurrentValue(); fence->CompletedValue() < currentFenceValue)
		{
			PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Verbose, "Set wait event. Fence value: '{}'. Timeout: '{} ms'.", currentFenceValue, waitTimeout);
			fence->SetEvent(currentFenceValue, waitEvent);
			if (const DWORD result = WaitForSingleObjectEx(waitEvent, waitTimeout, false); result != WAIT_OBJECT_0) [[unlikely]]
			{
				throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to wait for fence event with '0x{:X}' result.", static_cast<std::make_unsigned_t<HRESULT>>(result)));
			}
		}
		else
		{
			PONY_LOG(render->Logger(), PonyDebug::Log::LogType::Verbose, "No need to wait for fence.");
		}
	}
}
