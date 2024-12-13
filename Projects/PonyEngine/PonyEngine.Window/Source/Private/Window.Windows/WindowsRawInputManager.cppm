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

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Detail:WindowsRawInputManager;

import <algorithm>;
import <array>;
import <exception>;
import <span>;
import <stdexcept>;
import <typeinfo>;
import <unordered_map>;
import <vector>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

import :IWindowsWindowSystemContext;

export namespace PonyEngine::Window
{
	/// @brief Windows raw input manager.
	class WindowsRawInputManager final : public IWindowsRawInputManager, private IWindowsMessageObserver
	{
	public:
		/// @brief Creates a @p WindowsRawInputManager.
		/// @param windowSystem Windows window system context.
		[[nodiscard("Pure constructor")]]
		explicit WindowsRawInputManager(IWindowsWindowSystemContext& windowSystem) noexcept;
		WindowsRawInputManager(const WindowsRawInputManager&) = delete;
		WindowsRawInputManager(WindowsRawInputManager&&) = delete;

		~WindowsRawInputManager() noexcept;

		virtual void AddRawInputObserver(IWindowsRawInputObserver& observer, std::span<const DWORD> rawInputTypes) override;
		virtual void RemoveRawInputObserver(IWindowsRawInputObserver& observer) noexcept override;

		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsRawInputManager& operator =(const WindowsRawInputManager&) = delete;
		WindowsRawInputManager& operator =(WindowsRawInputManager&&) = delete;

	private:
		/// @brief Registers the raw input type.
		/// @param rawInputType Raw input type to register. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		void RegisterRawInputType(DWORD rawInputType);
		/// @brief Unregisters the raw input type.
		/// @param rawInputType Raw input type to unregister. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		void UnregisterRawInputType(DWORD rawInputType);
		/// @brief Registers the raw input type.
		/// @param rawInputType Raw input type to register. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.
		/// @param flags Registration flags.
		/// @param windowHandle Window handle.
		void RegisterRawInputType(DWORD rawInputType, DWORD flags, HWND windowHandle);

		IWindowsWindowSystemContext* windowSystem; ///< Windows window system context.

		std::unordered_map<DWORD, std::vector<IWindowsRawInputObserver*>> rawInputObservers; ///< Raw input observers.

		std::vector<BYTE> rawInput; ///< Raw input cache.
	};
}

namespace PonyEngine::Window
{
	WindowsRawInputManager::WindowsRawInputManager(IWindowsWindowSystemContext& windowSystem) noexcept :
		windowSystem{&windowSystem}
	{
		this->windowSystem->MessagePump().AddMessageObserver(*this, std::array<UINT, 1> { WM_INPUT });
	}

	WindowsRawInputManager::~WindowsRawInputManager() noexcept
	{
		windowSystem->MessagePump().RemoveMessageObserver(*this);
	}

	void WindowsRawInputManager::AddRawInputObserver(IWindowsRawInputObserver& observer, const std::span<const DWORD> rawInputTypes)
	{
		for (const DWORD rawInputType : rawInputTypes)
		{
			assert(rawInputType == RIM_TYPEMOUSE || rawInputType == RIM_TYPEKEYBOARD && "Incorrect raw input type: '{}'. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are supported only.");

			if (const auto typePosition = rawInputObservers.find(rawInputType); typePosition == rawInputObservers.cend() || typePosition->second.empty())
			{
				RegisterRawInputType(rawInputType);
			}

			std::vector<IWindowsRawInputObserver*>& observers = rawInputObservers[rawInputType];
			assert(std::ranges::find(observers, &observer) == observers.cend() && "The raw input observer has already been added.");
			observers.push_back(&observer);
		}
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input observer added.", typeid(observer).name());
	}

	void WindowsRawInputManager::RemoveRawInputObserver(IWindowsRawInputObserver& observer) noexcept
	{
		for (auto& [inputType, observers] : rawInputObservers)
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);

				if (observers.empty())
				{
					try
					{
						UnregisterRawInputType(inputType);
					}
					catch (const std::exception& e)
					{
						PONY_LOG_E(windowSystem->Logger(), e, "On unregistering raw input type {}.", inputType);
					}
				}
			}
		}
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input observer removed.", typeid(observer).name());
	}

	void WindowsRawInputManager::Observe(const UINT uMsg, const WPARAM, const LPARAM lParam)
	{
		assert(uMsg == WM_INPUT && "The message type is incorrect.");

		const auto hRawInput = reinterpret_cast<HRAWINPUT>(lParam);

		UINT size = 0u;
		if (GetRawInputData(hRawInput, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER))) [[unlikely]]
		{
			PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Error, "Failed to get raw input size. Error code: '0x{:X}'.", GetLastError());

			return;
		}
		if (size < 1u) [[unlikely]]
		{
			return;
		}

		rawInput.resize(size);
		if (GetRawInputData(hRawInput, RID_INPUT, rawInput.data(), &size, sizeof(RAWINPUTHEADER)) != rawInput.size()) [[unlikely]]
		{
			PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Error, "Failed to get raw input. Error code: '0x{:X}'.", GetLastError());

			return;
		}

		const RAWINPUT* const input = reinterpret_cast<RAWINPUT*>(rawInput.data());
		if (const auto observerPosition = rawInputObservers.find(input->header.dwType); observerPosition != rawInputObservers.cend())
		{
			for (IWindowsRawInputObserver* const observer : observerPosition->second)
			{
				try
				{
					observer->Observe(*input);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(windowSystem->Logger(), e, "On calling '{}' Windows raw input observer.", typeid(*observer).name());
				}
			}
		}
	}

	void WindowsRawInputManager::RegisterRawInputType(const DWORD rawInputType)
	{
		RegisterRawInputType(rawInputType, DWORD{0}, windowSystem->WindowHandle());
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input type registered.", rawInputType);
	}

	void WindowsRawInputManager::UnregisterRawInputType(const DWORD rawInputType)
	{
		RegisterRawInputType(rawInputType, RIDEV_REMOVE, nullptr);
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' raw input type unregistered.", rawInputType);
	}

	void WindowsRawInputManager::RegisterRawInputType(const DWORD rawInputType, const DWORD flags, const HWND windowHandle)
	{
		auto rid = RAWINPUTDEVICE{.dwFlags = flags, .hwndTarget = windowHandle};

		switch (rawInputType)
		{
		case RIM_TYPEMOUSE:
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			break;
		case RIM_TYPEKEYBOARD:
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x06;
			break;
		default: [[unlikely]]
			assert(false && "The raw input type is incorrect. RIM_TYPEMOUSE and RIM_TYPEKEYBOARD are only supported.");
			return;
		}

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) [[unlikely]]
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register raw input device. Usage page: '0x{:X}'; Usage: '0x{:X}'; Flags: '0x{:X}'; Window handle: '0x{:X}'. Error code: '0x{:X}'.", rid.usUsagePage, rid.usUsage, rid.dwFlags, reinterpret_cast<std::uintptr_t>(rid.hwndTarget), GetLastError()));
		}
	}
}
