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
#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Platform/Windows/Input.h"

export module PonyEngine.Surface.Impl:Windows.RawInputManager;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.MessagePump;
import PonyEngine.Surface;

import: Windows.RawInputDeviceContainer;

export namespace PonyEngine::Surface::Windows
{
	/// @brief Raw input manager.
	class RawInputManager final
	{
	public:
		/// @brief Creates a raw input manager.
		/// @param application Application context.
		/// @param surfaceService Surface service.
		[[nodiscard("Pure constructor")]]
		RawInputManager(Application::Windows::IApplicationContext& application, ISurfaceService& surfaceService) noexcept;
		RawInputManager(const RawInputManager&) = delete;
		RawInputManager(RawInputManager&&) = delete;

		~RawInputManager() noexcept = default;

		/// @brief Adds the raw input observer.
		/// @param observer Raw input observer.
		/// @param usagePage Device usage page.
		/// @param usage Device usage.
		void AddRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage);
		/// @brief Adds the raw input observer.
		/// @param observer Raw input observer.
		/// @param rawInputUsages Device usages.
		void AddRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages);
		/// @brief Removes the raw input observer.
		/// @param observer Raw input observer.
		/// @param usagePage Device usage page.
		/// @param usage Device usage.
		void RemoveRawInputObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) noexcept;
		/// @brief Removes the raw input observer.
		/// @param observer Raw input observer.
		/// @param rawInputUsages Device usages.
		void RemoveRawInputObserver(IRawInputObserver& observer, std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept;
		/// @brief Removes the raw input observer.
		/// @param observer Raw input observer.
		void RemoveRawInputObserver(IRawInputObserver& observer) noexcept;

		/// @brief Observes the WM_INPUT message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveRawInput(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes the WM_INPUT_DEVICE_CHANGE message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Result.
		[[nodiscard("The value must be returned to the system")]]
		LRESULT ObserveInputDeviceChange(WPARAM wParam, LPARAM lParam) noexcept;

		RawInputManager& operator =(const RawInputManager&) = delete;
		RawInputManager& operator =(RawInputManager&&) = delete;

	private:
		/// @brief Registers a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		void RegisterRawInputType(USHORT usagePage, USHORT usage);
		/// @brief Unregisters a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		void UnregisterRawInputType(USHORT usagePage, USHORT usage);
		/// @brief Registers/unregisters a raw input type.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		/// @param flags Registration flags.
		void RegisterRawInputType(USHORT usagePage, USHORT usage, DWORD flags);
		/// @brief Gets a type from the device handle.
		/// @param handle Device handle.
		/// @return Usage type.
		[[nodiscard("Pure function")]]
		static DWORD GetUsageType(HANDLE handle);

		/// @brief Packs the two USHORT values into a DWORD.
		/// @param first High bit value.
		/// @param second Low bit value.
		/// @return Value pack.
		[[nodiscard("Pure function")]]
		static constexpr DWORD Pack(USHORT first, USHORT second) noexcept;
		/// @brief Unpacks the DWORD value into two USHORT values.
		/// @param value Value.
		/// @return High bit value and low bit value.
		[[nodiscard("Pure function")]]
		static constexpr std::pair<USHORT, USHORT> Unpack(DWORD value) noexcept;

		Application::Windows::IApplicationContext* application; ///< Application context.
		ISurfaceService* surfaceService;
		MessagePump::IPumpService* pumpService; ///< Message pump service.

		RawInputDeviceContainer deviceContainer; ///< Device container.

		std::unordered_map<DWORD, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		std::vector<BYTE> rawInputTemp; ///< Raw input temp data.
	};
}

namespace PonyEngine::Surface::Windows
{
	RawInputManager::RawInputManager(Application::Windows::IApplicationContext& application, ISurfaceService& surfaceService) noexcept :
		application{&application},
		surfaceService{&surfaceService},
		pumpService{&this->application->GetService<MessagePump::IPumpService>()}
	{
	}

	void RawInputManager::AddRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		const DWORD usageType = Pack(usagePage, usage);
		std::vector<IRawInputObserver*>& observers = rawInputObservers[usageType];
		observers.push_back(&observer);

		if (observers.size() == 1uz)
		{
			try
			{
				RegisterRawInputType(usagePage, usage);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On registering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
				observers.pop_back();

				throw;
			}
		}
	}

	void RawInputManager::AddRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages)
	{
		for (std::size_t i = 0uz; i < rawInputUsages.size(); ++i)
		{
			try
			{
				AddRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
			}
			catch (...)
			{
				while (i-- > 0uz)
				{
					RemoveRawInputObserver(observer, rawInputUsages[i].first, rawInputUsages[i].second);
				}

				throw;
			}
		}
	}

	void RawInputManager::RemoveRawInputObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage) noexcept
	{
		const DWORD usageType = Pack(usagePage, usage);
		if (const auto position = rawInputObservers.find(usageType); position != rawInputObservers.cend()) [[likely]]
		{
			if (const auto pos = std::ranges::find(position->second, &observer); pos != position->second.cend()) [[likely]]
			{
				position->second.erase(pos);
				if (position->second.empty())
				{
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG_X(application->Logger(), std::current_exception(), "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}

				return;
			}
		}

		PONY_LOG(application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void RawInputManager::RemoveRawInputObserver(IRawInputObserver& observer, const std::span<const std::pair<USHORT, USHORT>> rawInputUsages) noexcept
	{
		for (const auto [usagePage, usage] : rawInputUsages)
		{
			RemoveRawInputObserver(observer, usagePage, usage);
		}
	}

	void RawInputManager::RemoveRawInputObserver(IRawInputObserver& observer) noexcept
	{
		std::size_t erased = 0uz;

		for (auto& [type, observers] : rawInputObservers)
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
				++erased;

				if (observers.empty())
				{
					const auto [usagePage, usage] = Unpack(type);
					try
					{
						UnregisterRawInputType(usagePage, usage);
					}
					catch (...)
					{
						PONY_LOG_X(application->Logger(), std::current_exception(), "On unregistering raw input type. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
					}
				}
			}
		}

		PONY_LOG_IF(erased == 0uz, application->Logger(), Log::LogType::Warning, "Tried to remove raw input observer that hadn't been added.");
	}

	LRESULT RawInputManager::ObserveRawInput(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto rawInputInfo = reinterpret_cast<HRAWINPUT>(lParam);
		UINT size = 0u;
		if (GetRawInputData(rawInputInfo, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER))) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}
		if (size < 1u) [[unlikely]]
		{
			return 0;
		}
		try
		{
			rawInputTemp.resize(size);
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On resizing raw input cache.");
			return 0;
		}
		if (GetRawInputData(rawInputInfo, RID_INPUT, rawInputTemp.data(), &size, sizeof(RAWINPUTHEADER)) != rawInputTemp.size()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(rawInputTemp.data());
		if (const std::size_t index = deviceContainer.IndexOf(input->header.hDevice); index < deviceContainer.Size()) [[likely]]
		{
			const DWORD deviceType = deviceContainer.DeviceType(index);

			if (const auto observerPosition = rawInputObservers.find(deviceType); observerPosition != rawInputObservers.cend())
			{
				const std::chrono::time_point<std::chrono::steady_clock> time = pumpService->LastMessageTime();
				const Math::Vector2<std::int32_t> cursorPosition = pumpService->LastMessageCursorPosition();

				for (IRawInputObserver* const observer : observerPosition->second)
				{
					try
					{
						observer->Observe(*input, time, cursorPosition);
					}
					catch (...)
					{
						PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' raw input observer.", typeid(*observer).name());
					}
				}
			}
		}

		return 0;
	}

	LRESULT RawInputManager::ObserveInputDeviceChange(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		bool isConnected;
		switch (wParam)
		{
		case GIDC_ARRIVAL:
			isConnected = true;
			break;
		case GIDC_REMOVAL:
			isConnected = false;
			break;
		default:
			return 0;
		}

		const auto deviceHandle = reinterpret_cast<HANDLE>(lParam);
		if (!deviceHandle)
		{
			return 0;
		}

		try
		{
			DWORD usageType;
			if (isConnected)
			{
				usageType = GetUsageType(deviceHandle);
				deviceContainer.Add(deviceHandle, usageType);

			}
			else if (const std::size_t index = deviceContainer.IndexOf(deviceHandle); index < deviceContainer.Size())
			{
				usageType = deviceContainer.DeviceType(index);
				deviceContainer.Remove(index);
			}
			else [[unlikely]]
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Unknown device disconnected. Device handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(deviceHandle));
				return 0;
			}

			if (const auto observerPosition = rawInputObservers.find(usageType); observerPosition != rawInputObservers.cend())
			{
				for (IRawInputObserver* const observer : observerPosition->second)
				{
					try
					{
						observer->OnDeviceConnectionChanged(deviceHandle, isConnected);
					}
					catch (...)
					{
						PONY_LOG_X(application->Logger(), std::current_exception(), "On calling '{}' raw input observer on input device change.", typeid(*observer).name());
					}
				}
			}
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On updating device connection state. Device handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(deviceHandle));
		}

		return 0;
	}

	void RawInputManager::RegisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering raw input type... Usage page: '{}'; Usage: '{}'.", usagePage, usage);
		RegisterRawInputType(usagePage, usage, RIDEV_DEVNOTIFY);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Registering raw input type done. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void RawInputManager::UnregisterRawInputType(const USHORT usagePage, const USHORT usage)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering raw input type... Usage page: '{}'; Usage: '{}'.", usagePage, usage);
		RegisterRawInputType(usagePage, usage, RIDEV_REMOVE);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Unregistering raw input type done. Usage page: '{}'; Usage: '{}'.", usagePage, usage);
	}

	void RawInputManager::RegisterRawInputType(const USHORT usagePage, const USHORT usage, const DWORD flags)
	{
		const auto rid = RAWINPUTDEVICE
		{
			.usUsagePage = usagePage,
			.usUsage = usage,
			.dwFlags = flags,
			.hwndTarget = flags & RIDEV_REMOVE ? nullptr : surfaceService->Handle()
		};

		if (!RegisterRawInputDevices(&rid, 1u, sizeof(rid))) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to register/unregister raw input device. Usage page: '0x{:X}'; Usage: '0x{:X}'; Flags: '0x{:X}'; Window handle: '0x{:X}'. Error code: '0x{:X}'.", rid.usUsagePage, rid.usUsage, rid.dwFlags, reinterpret_cast<std::uintptr_t>(rid.hwndTarget), GetLastError()));
		}
	}

	DWORD RawInputManager::GetUsageType(const HANDLE handle)
	{
		auto info = RID_DEVICE_INFO{.cbSize = sizeof(RID_DEVICE_INFO)};
		UINT size = sizeof(info);
		if (!GetRawInputDeviceInfoA(handle, RIDI_DEVICEINFO, &info, &size)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get device info. Error code: '0x{:X}'.", GetLastError()));
		}

		switch (info.dwType)
		{
		case RIM_TYPEMOUSE:
			return Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
		case RIM_TYPEKEYBOARD:
			return Pack(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
		case RIM_TYPEHID:
			return Pack(info.hid.usUsagePage, info.hid.usUsage);
		default: [[unlikely]]
			throw std::runtime_error("Unexpected device type.");
		}
	}

	constexpr DWORD RawInputManager::Pack(const USHORT first, const USHORT second) noexcept
	{
		return static_cast<DWORD>(first) << 16 | second;
	}

	constexpr std::pair<USHORT, USHORT> RawInputManager::Unpack(const DWORD value) noexcept
	{
		return std::pair(static_cast<USHORT>(value >> 16), static_cast<USHORT>(value));
	}
}
