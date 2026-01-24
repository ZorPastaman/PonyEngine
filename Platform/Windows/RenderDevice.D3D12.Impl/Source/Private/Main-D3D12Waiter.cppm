/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Waiter;

import std;

import PonyEngine.Log;
import PonyEngine.RenderDevice.Ext;

import :D3D12Fence;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Waiter final : public IWaiter
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12Waiter(IRenderDeviceContext& renderDevice);
		D3D12Waiter(const D3D12Waiter&) = delete;
		D3D12Waiter(D3D12Waiter&&) = delete;

		~D3D12Waiter() noexcept;

		virtual void Wait(std::span<const FenceValue> fenceValues, std::chrono::nanoseconds timeout) override;

		D3D12Waiter& operator =(const D3D12Waiter&) = delete;
		D3D12Waiter& operator =(D3D12Waiter&&) = delete;

	private:
		IRenderDeviceContext* renderDevice;

		HANDLE waitEvent;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Waiter::D3D12Waiter(IRenderDeviceContext& renderDevice) :
		renderDevice{&renderDevice}
	{
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Creating wait handle done...");
		if (!((waitEvent = CreateEventA(nullptr, false, false, nullptr)))) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to create wait event: Error code: '0x{:X}'", GetLastError()));
		}
		PONY_LOG(this->renderDevice->Logger(), Log::LogType::Info, "Creating wait handle done. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(waitEvent));
	}

	D3D12Waiter::~D3D12Waiter() noexcept
	{
		if (!CloseHandle(waitEvent)) [[unlikely]]
		{
			PONY_LOG(renderDevice->Logger(), Log::LogType::Error, "Failed to close wait handle. Handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(waitEvent));
		}
	}

	void D3D12Waiter::Wait(const std::span<const FenceValue> fenceValues, const std::chrono::nanoseconds timeout)
	{
		const std::chrono::time_point<std::chrono::steady_clock> startPoint = std::chrono::steady_clock::now();

		for (const FenceValue& fenceValue : fenceValues)
		{
#ifndef NDEBUG
			if (!fenceValue.fence || typeid(*fenceValue.fence) != typeid(D3D12Fence)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid fence");
			}
#endif

			if (const auto fence = static_cast<const D3D12Fence*>(fenceValue.fence); fence->CompletedValue() < fenceValue.value)
			{
				const std::chrono::time_point<std::chrono::steady_clock> fencePoint = std::chrono::steady_clock::now();
				const auto timeDiff = fencePoint - startPoint;
				if (timeDiff > timeout) [[unlikely]]
				{
					throw std::runtime_error("Timeout");
				}
				const std::chrono::milliseconds remaining = std::chrono::duration_cast<std::chrono::milliseconds>(timeout - timeDiff);

				fence->SetEventOnCompletion(fenceValue.value, waitEvent);
				if (const DWORD result = WaitForSingleObjectEx(waitEvent, static_cast<DWORD>(remaining.count()), false); result != WAIT_OBJECT_0) [[unlikely]]
				{
					if (result == WAIT_TIMEOUT)
					{
						throw std::runtime_error("Timeout");
					}

					throw std::runtime_error(std::format("Failed to wait for fence event: Result = '0x{:X}", static_cast<std::make_unsigned_t<HRESULT>>(result)));
				}
			}
		}
	}
}
