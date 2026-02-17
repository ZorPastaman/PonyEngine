/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Waiter;

import std;

import PonyEngine.RenderDevice;

import :Fence;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class Waiter final : public IWaiter
	{
	public:
		[[nodiscard("Pure constructor")]]
		Waiter() noexcept = default;
		Waiter(const Waiter&) = delete;
		Waiter(Waiter&&) = delete;

		~Waiter() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::size_t MaxFences() const noexcept override;
		virtual void Wait(std::span<const FenceValue> fenceValues, std::chrono::nanoseconds timeout) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		Waiter& operator =(const Waiter&) = delete;
		Waiter& operator =(Waiter&&) = delete;

	private:
		void CreateEvents(std::size_t count);
		std::size_t Signal(std::span<const FenceValue> fenceValues);
		void Wait(std::size_t count, std::chrono::milliseconds timeout);

		void ValidateFences(std::span<const FenceValue> fenceValues) const;

		std::vector<HANDLE> waitEvents;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Waiter::~Waiter() noexcept
	{
		for (std::size_t i = waitEvents.size(); i-- > 0uz; )
		{
			CloseHandle(waitEvents[i]);
		}
	}

	std::size_t Waiter::MaxFences() const noexcept
	{
		return MAXIMUM_WAIT_OBJECTS;
	}

	void Waiter::Wait(const std::span<const FenceValue> fenceValues, const std::chrono::nanoseconds timeout)
	{
		ValidateFences(fenceValues);

		CreateEvents(fenceValues.size());
		const std::size_t waitCount = Signal(fenceValues);
		Wait(waitCount, std::chrono::duration_cast<std::chrono::milliseconds>(timeout));
	}

	std::string_view Waiter::Name() const noexcept
	{
		return name;
	}

	void Waiter::Name(const std::string_view name)
	{
		this->name = name;
	}

	void Waiter::CreateEvents(const std::size_t count)
	{
		waitEvents.reserve(count);
		for (std::size_t i = waitEvents.size(); i < count; ++i)
		{
			if (const HANDLE waitEvent = CreateEventA(nullptr, false, false, nullptr)) [[likely]]
			{
				waitEvents.push_back(waitEvent);
			}
			else [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to create wait event: Error code: '0x{:X}'", GetLastError()));
			}
		}
	}

	std::size_t Waiter::Signal(const std::span<const FenceValue> fenceValues)
	{
		std::size_t waitCount = 0uz;
		for (const FenceValue& fenceValue : fenceValues)
		{
			if (const auto fence = static_cast<const Fence*>(fenceValue.fence); fence->CompletedValue() < fenceValue.value)
			{
				fence->SetEventOnCompletion(fenceValue.value, waitEvents[waitCount++]);
			}
		}

		return waitCount;
	}

	void Waiter::Wait(const std::size_t count, const std::chrono::milliseconds timeout)
	{
		if (count == 0uz)
		{
			return;
		}

		const DWORD nativeTimeout = timeout.count() > std::numeric_limits<DWORD>::max() ? std::numeric_limits<DWORD>::max() : static_cast<DWORD>(timeout.count());
		if (const DWORD result = WaitForMultipleObjectsEx(static_cast<DWORD>(count), waitEvents.data(), true, nativeTimeout, false); result != WAIT_OBJECT_0) [[unlikely]]
		{
			if (result == WAIT_TIMEOUT)
			{
				throw std::runtime_error("Timeout");
			}
			if (result == WAIT_FAILED)
			{
				throw std::runtime_error(std::format("Failed to wait for fence event: ErrorCode = '0x{:X}", GetLastError()));
			}

			throw std::runtime_error(std::format("Failed to wait for fence event: Result = '0x{:X}", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}

	void Waiter::ValidateFences(const std::span<const FenceValue> fenceValues) const
	{
#ifndef NDEBUG
		if (fenceValues.size() > MaxFences()) [[unlikely]]
		{
			throw std::invalid_argument("Too many fences");
		}

		for (const FenceValue& fenceValue : fenceValues)
		{
			if (!fenceValue.fence || typeid(*fenceValue.fence) != typeid(Fence)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid fence");
			}
		}
#endif
	}
}
