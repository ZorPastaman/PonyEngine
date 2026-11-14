/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <hidusage.h>

export module PonyEngine.WinInput.Impl:InputDispatcher;

import std;

import PonyEngine.Application;
import PonyEngine.FileSystem.WinAPI;
import PonyEngine.Log;
import PonyEngine.WinInput;

namespace PonyEngine::WinInput
{
	/// @brief Window proc for the @p InputDispatcher.
	/// @param hwnd Window handle.
	/// @param msg Message.
	/// @param wParam wParam.
	/// @param lParam lParam.
	/// @return Result.
	[[nodiscard("Must be returned to system")]]
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
}

export namespace PonyEngine::WinInput
{
	/// @brief WinAPI input dispatcher.
	class InputDispatcher final : public IInputDispatcher
	{
	public:
		/// @brief Creates an input dispatcher.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit InputDispatcher(Application::IApplication& application);
		InputDispatcher(const InputDispatcher&) = delete;
		InputDispatcher(InputDispatcher&&) = delete;

		~InputDispatcher() noexcept;

		virtual void AddObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) override;
		virtual void RemoveObserver(IRawInputObserver& observer, USHORT usagePage, USHORT usage) override;

		InputDispatcher& operator =(const InputDispatcher&) = delete;
		InputDispatcher& operator =(InputDispatcher&&) = delete;

	private:
		/// @brief Observes WM_INPUT.
		/// @param wParam wParam.
		/// @param lParam lParam.
		[[nodiscard("Must be returned to system")]]
		LRESULT ObserveRawInput(WPARAM wParam, LPARAM lParam) noexcept;
		/// @brief Observes WM_INPUT_DEVICE_CHANGE.
		/// @param wParam wParam.
		/// @param lParam lParam.
		[[nodiscard("Must be returned to system")]]
		LRESULT ObserveRawInputDeviceChange(WPARAM wParam, LPARAM lParam) noexcept;

		/// @brief Adds the device.
		/// @param deviceHandle Device handle.
		/// @return Usage key.
		[[nodiscard("Must be used")]]
		UINT AddDevice(HANDLE deviceHandle);
		/// @brief Removes a device.
		/// deviceHandle Device handle.
		/// @return Usage key.
		[[nodiscard("Must be used")]]
		UINT RemoveDevice(HANDLE deviceHandle) noexcept;

		/// @brief Gets a usage key (usage page | usage).
		/// @param header Raw input header.
		/// @return Usage key.
		[[nodiscard("Pure function")]]
		UINT GetUsageKey(const RAWINPUTHEADER& header) const noexcept;
		/// @brief Gets a usage key (usage page | usage).
		/// @param deviceHandle Device handle.
		/// @return Usage key.
		[[nodiscard("Pure function")]]
		UINT GetUsageKey(HANDLE deviceHandle) const noexcept;
		/// @brief Finds a usage key among previously connected devices.
		/// @param deviceHandle Device handle.
		/// @return Usage key and handle index.
		[[nodiscard("Pure function")]]
		std::pair<UINT, std::size_t> FindUsageKey(HANDLE deviceHandle) const noexcept;

		/// @brief Calculates a total count of raw input observers.
		/// @return Raw input observer count.
		[[nodiscard("Pure function")]]
		std::size_t RawInputObserverCount() const noexcept;

		/// @brief Combines a usage key out of the usage page and usage.
		/// @param usagePage Usage page.
		/// @param usage Usage.
		/// @return Usage key.
		[[nodiscard("Pure function")]]
		static constexpr UINT ToUsageKey(USHORT usagePage, USHORT usage) noexcept;

		Application::IApplication* application; ///< Application.
		Log::ILogService* logService; ///< Log service.

		HMODULE moduleHandle; ///< Module instance handle.
		ATOM classHandle; /// Registered class handle.
		HWND hwnd; ///< Window handle.

		std::unordered_map<UINT, std::vector<IRawInputObserver*>> rawInputObservers; ///< Raw input observers.
		std::unordered_map<UINT, std::vector<HANDLE>> connectedDevices; ///< Connected devices.

		friend LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	};
}

namespace PonyEngine::WinInput
{
	LRESULT WindowProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		if (msg == WM_CREATE) [[unlikely]]
		{
			const auto dispatcher = static_cast<InputDispatcher*>(reinterpret_cast<CREATESTRUCTA*>(lParam)->lpCreateParams);
			SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(dispatcher));
			return 0;
		}

		if (const auto dispatcher = reinterpret_cast<InputDispatcher*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA))) [[likely]]
		{
			switch (msg)
			{
			case WM_INPUT:
				return dispatcher->ObserveRawInput(wParam, lParam);
			case WM_INPUT_DEVICE_CHANGE:
				return dispatcher->ObserveRawInputDeviceChange(wParam, lParam);
			default:
				break;
			}
		}

		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}

	InputDispatcher::InputDispatcher(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()},
		moduleHandle{FileSystem::GetModule()}
	{
		const auto wc = WNDCLASSEXA
		{
			.cbSize = sizeof(WNDCLASSEXA),
			.style = 0u,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = moduleHandle,
			.hIcon = nullptr,
			.hCursor = nullptr,
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = "PonyEngineRawInput",
			.hIconSm = nullptr
		};
		classHandle = RegisterClassExA(&wc);
		if (!classHandle) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to register class: ErrorCode = '0x{:X}'", GetLastError()));
		}

		hwnd = CreateWindowExA(0, reinterpret_cast<LPCSTR>(classHandle), "PonyEngineRawInput", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, moduleHandle, this);
		if (!hwnd) [[unlikely]]
		{
			const DWORD windowError = GetLastError();

			if (!UnregisterClassA(reinterpret_cast<LPCSTR>(classHandle), moduleHandle)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to window unregister class on message window creation failure. Error code: '0x{:X}'.", GetLastError());
			}

			throw std::runtime_error(std::format("Failed to create message window: Error code = '0x{:X}'", windowError));
		}
	}

	InputDispatcher::~InputDispatcher() noexcept
	{
		assert(RawInputObserverCount() == 0uz && "Some WinAPI input raw input observers weren't removed.");

		if (!DestroyWindow(hwnd)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to destroy message window. Error code: '0x{:X}'.", GetLastError());
		}
		if (!UnregisterClassA(reinterpret_cast<LPCSTR>(classHandle), moduleHandle)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to unregister window class. Error code: '0x{:X}'.", GetLastError());
		}
	}

	void InputDispatcher::AddObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");

		const UINT usageKey = ToUsageKey(usagePage, usage);
		std::vector<IRawInputObserver*>& usageObservers = rawInputObservers[usageKey];
		usageObservers.push_back(&observer);

		if (usageObservers.size() == 1uz)
		{
			const auto rid = RAWINPUTDEVICE{.usUsagePage = usagePage, .usUsage = usage, .dwFlags = RIDEV_INPUTSINK | RIDEV_DEVNOTIFY, .hwndTarget = hwnd};
			RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE));
		}

		if (const auto position = connectedDevices.find(usageKey); position != connectedDevices.cend())
		{
			for (const HANDLE handle : position->second)
			{
				observer.OnDeviceConnectionChanged(handle, true);
			}
		}
	}

	void InputDispatcher::RemoveObserver(IRawInputObserver& observer, const USHORT usagePage, const USHORT usage)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");

		const UINT usageKey = ToUsageKey(usagePage, usage);
		if (const auto usagePosition = rawInputObservers.find(usageKey); usagePosition != rawInputObservers.cend()) [[likely]]
		{
			if (const auto observerPosition = std::ranges::find(usagePosition->second, &observer); observerPosition != usagePosition->second.cend()) [[likely]]
			{
				usagePosition->second.erase(observerPosition);

				if (usagePosition->second.empty())
				{
					const auto rid = RAWINPUTDEVICE{.usUsagePage = usagePage, .usUsage = usage, .dwFlags = RIDEV_REMOVE, .hwndTarget = nullptr};
					RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE));
				}

				return;
			}
		}

		assert(false && "Observer wasn't added");
	}

	LRESULT InputDispatcher::ObserveRawInput(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto rawInputInfo = reinterpret_cast<HRAWINPUT>(lParam);
		UINT size = 0u;
		if (GetRawInputData(rawInputInfo, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER))) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}
		if (size < 1u) [[unlikely]]
		{
			return 0;
		}

		std::shared_ptr<Application::IBuffer> buffer;
		try
		{
			buffer = application->CreateBuffer(size);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On allocating raw input buffer.");
			return 0;
		}

		const std::span<std::byte> bufferData = buffer->Span();
		if (GetRawInputData(rawInputInfo, RID_INPUT, bufferData.data(), &size, sizeof(RAWINPUTHEADER)) != size) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());
			return 0;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(bufferData.data());
		const UINT usageKey = GetUsageKey(input->header);
		if (usageKey == 0u) [[unlikely]]
		{
			return 0;
		}

		if (const auto position = rawInputObservers.find(usageKey); position != rawInputObservers.cend()) [[likely]]
		{
			for (IRawInputObserver* const observer : position->second)
			{
				try
				{
					observer->OnInput(*input);
				}
				catch (...)
				{
					PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' raw input observer on input.", typeid(*observer).name());
				}
			}
		}

		return 0;
	}

	LRESULT InputDispatcher::ObserveRawInputDeviceChange(const WPARAM wParam, const LPARAM lParam) noexcept
	{
		const auto deviceHandle = reinterpret_cast<HANDLE>(lParam);
		if (!deviceHandle) [[unlikely]]
		{
			return 0;
		}

		UINT usageKey;
		bool isConnected;
		try
		{
			switch (wParam)
			{
			case GIDC_ARRIVAL:
				usageKey = AddDevice(deviceHandle);
				isConnected = true;
				break;
			case GIDC_REMOVAL:
				usageKey = RemoveDevice(deviceHandle);
				isConnected = false;
				break;
			default: [[unlikely]]
				return 0;
			}
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On updating WinAPI connected device list.");
			return 0;
		}

		if (usageKey != 0u)
		{
			if (const auto position = rawInputObservers.find(usageKey); position != rawInputObservers.cend()) [[likely]]
			{
				for (IRawInputObserver* const observer : position->second)
				{
					try
					{
						observer->OnDeviceConnectionChanged(deviceHandle, isConnected);
					}
					catch (...)
					{
						PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On calling '{}' raw input observer on device connection changed.", 
							typeid(*observer).name());
					}
				}
			}
		}

		return 0;
	}

	UINT InputDispatcher::AddDevice(const HANDLE deviceHandle)
	{
		const UINT usageKey = GetUsageKey(deviceHandle);
		if (usageKey != 0u)
		{
			connectedDevices[usageKey].push_back(deviceHandle);
		}

		return usageKey;
	}

	UINT InputDispatcher::RemoveDevice(const HANDLE deviceHandle) noexcept
	{
		const auto [usageKey, deviceIndex] = FindUsageKey(deviceHandle);
		if (usageKey != 0u)
		{
			std::vector<HANDLE>& devices = connectedDevices[usageKey];
			devices.erase(devices.cbegin() + deviceIndex);
		}

		return usageKey;
	}

	UINT InputDispatcher::GetUsageKey(const RAWINPUTHEADER& header) const noexcept
	{
		switch (header.dwType)
		{
		case RIM_TYPEKEYBOARD:
			return ToUsageKey(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
		case RIM_TYPEMOUSE:
			return ToUsageKey(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
		case RIM_TYPEHID:
			return GetUsageKey(header.hDevice);
		default:
			return 0u;
		}
	}

	UINT InputDispatcher::GetUsageKey(const HANDLE deviceHandle) const noexcept
	{
		auto info = RID_DEVICE_INFO{.cbSize = sizeof(RID_DEVICE_INFO)};
		UINT size = sizeof(info);
		if (GetRawInputDeviceInfoA(deviceHandle, RIDI_DEVICEINFO, &info, &size) != std::numeric_limits<UINT>::max()) [[likely]]
		{
			switch (info.dwType)
			{
			case RIM_TYPEKEYBOARD:
				return ToUsageKey(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
			case RIM_TYPEMOUSE:
				return ToUsageKey(HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
			case RIM_TYPEHID:
				return ToUsageKey(info.hid.usUsagePage, info.hid.usUsage);
			default:
				return 0u;
			}
		}

		PONY_LOG(logService, Log::LogType::Error, "Failed to get hid device usage. Handle: '0x{:X}'; Error code: '0x{:X}'.", 
			reinterpret_cast<std::uintptr_t>(deviceHandle), GetLastError());
		return 0u;
	}

	std::pair<UINT, std::size_t> InputDispatcher::FindUsageKey(const HANDLE deviceHandle) const noexcept
	{
		for (const auto& [usageKey, handles] : connectedDevices)
		{
			const std::size_t index = std::ranges::find(handles, deviceHandle) - handles.cbegin();
			if (index < handles.size())
			{
				return std::pair(usageKey, index);
			}
		}

		return std::pair(0u, std::numeric_limits<std::size_t>::max());
	}

	std::size_t InputDispatcher::RawInputObserverCount() const noexcept
	{
		std::size_t count = 0uz;
		for (const std::vector<IRawInputObserver*>& inputObservers : std::views::values(rawInputObservers))
		{
			count += inputObservers.size();
		}

		return count;
	}

	constexpr UINT InputDispatcher::ToUsageKey(const USHORT usagePage, const USHORT usage) noexcept
	{
		return static_cast<UINT>(usagePage) << 16 | usage;
	}
}
