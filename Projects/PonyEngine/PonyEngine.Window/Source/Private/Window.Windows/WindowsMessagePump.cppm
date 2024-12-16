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

export module PonyEngine.Window.Windows.Detail:WindowsMessagePump;

import <algorithm>;
import <exception>;
import <ranges>;
import <span>;
import <typeinfo>;
import <unordered_map>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Window.Windows;

import :IWindowsWindowSystemContext;

export namespace PonyEngine::Window
{
	/// @brief Windows message pump.
	class WindowsMessagePump final : public IWindowsMessagePump, public IWindowsMessageHandler
	{
	public:
		/// @brief Creates a @p WindowsMessagePump.
		/// @param windowSystem Windows window system context.
		[[nodiscard("Pure constructor")]]
		explicit WindowsMessagePump(IWindowsWindowSystemContext& windowSystem) noexcept;
		WindowsMessagePump(const WindowsMessagePump&) = delete;
		WindowsMessagePump(WindowsMessagePump&&) = delete;

		~WindowsMessagePump() noexcept = default;

		virtual void AddMessageObserver(IWindowsMessageObserver& observer, std::span<const UINT> messageTypes) override;
		virtual void RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept override;

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept override;

		/// @brief Pumps messages.
		void Pump();

		WindowsMessagePump& operator =(const WindowsMessagePump&) = delete;
		WindowsMessagePump& operator =(WindowsMessagePump&&) = delete;

	private:
		IWindowsWindowSystemContext* windowSystem; ///< Windows window system context.

		std::unordered_map<UINT, std::vector<IWindowsMessageObserver*>> messageObservers; ///< Message observers.
	};
}

namespace PonyEngine::Window
{
	WindowsMessagePump::WindowsMessagePump(IWindowsWindowSystemContext& windowSystem) noexcept :
		windowSystem{&windowSystem}
	{
	}

	void WindowsMessagePump::AddMessageObserver(IWindowsMessageObserver& observer, const std::span<const UINT> messageTypes)
	{
		for (const UINT messageType : messageTypes)
		{
			std::vector<IWindowsMessageObserver*>& observers = messageObservers[messageType];
			assert(std::ranges::find(observers, &observer) == observers.cend() && "The window message observer has already been added.");
			observers.push_back(&observer);
		}
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer added.", typeid(observer).name());
	}

	void WindowsMessagePump::RemoveMessageObserver(IWindowsMessageObserver& observer) noexcept
	{
		for (std::vector<IWindowsMessageObserver*>& observers : std::ranges::views::values(messageObservers))
		{
			if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
			{
				observers.erase(position);
			}
		}
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Debug, "'{}' window message observer removed.", typeid(observer).name());
	}

	LRESULT WindowsMessagePump::HandleMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
	{
		PONY_LOG(windowSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Received '{}' command.", uMsg);

		if (const auto position = messageObservers.find(uMsg); position != messageObservers.cend())
		{
			for (IWindowsMessageObserver* const observer : position->second)
			{
				try
				{
					observer->Observe(uMsg, wParam, lParam);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(windowSystem->Logger(), e, "On calling '{}' Windows message observer.", typeid(*observer).name());
				}
			}
		}

		return DefWindowProcW(windowSystem->WindowHandle(), uMsg, wParam, lParam);
	}

	void WindowsMessagePump::Pump()
	{
		const HWND hWnd = windowSystem->WindowHandle();

		MSG message;
		while (PeekMessageW(&message, hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
}
