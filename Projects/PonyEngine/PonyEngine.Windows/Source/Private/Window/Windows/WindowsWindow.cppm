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

#include "Platform/Windows/Framework.h"
#include "Debug/Log/LogMacro.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindow;

import <algorithm>;
import <cstdint>;
import <format>;
import <exception>;
import <ranges>;
import <stdexcept>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Window;
import PonyEngine.Window.Windows;

import :IWindowProc;
import :WindowParams;
import :WindowsKeyCodeUtility;

export namespace PonyEngine::Window
{
	/// @brief Engine window for @p Windows platform.
	class WindowsWindow final : public IWindowsWindow, public IWindowProc
	{
	public:
		/// @brief Creates a @p WindowsWindow.
		/// @param engine Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(Core::IEngine& engine, HINSTANCE hInstance, ATOM className, const WindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		~WindowsWindow() noexcept;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) override;

		virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;

		virtual void ShowWindow() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		virtual HWND GetWindowHandle() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual bool IsWindowAlive() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

	private:
		/// @brief Responds to a destroy message.
		void Destroy() noexcept;

		/// @brief Sends a keyboard message to the @p m_keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown) const;

	public:
		static const char* const Name; ///< WindowsWindow class name.

	private:
		std::vector<IKeyboardObserver*> m_keyboardMessageObservers; ///< Keyboard message observers.

		std::wstring m_title; ///< Window title.
		HWND m_hWnd; ///< Window handler.
		const int m_nCmdShow; ///< Show type.
		bool m_isAlive; ///< Is the system window alive?

		Core::IEngine& m_engine; ///< Engine that owns the window.
	};
}

namespace PonyEngine::Window
{
	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const ATOM className, const WindowParams& windowParams) :
		m_title(windowParams.title),
		m_nCmdShow{windowParams.cmdShow},
		m_isAlive{false},
		m_engine{engine}
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Create a system window of the class id '{}'.", className).c_str());
		m_hWnd = CreateWindowEx(
			0,
			reinterpret_cast<LPCTSTR>(className),
			m_title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (m_hWnd == NULL)
		{
			throw std::logic_error(std::format("Windows hasn't created a window. Error code: '{}'.", GetLastError()));
		}

		m_isAlive = true;
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("System window of the class id '{}' created. Window handle: '{}'.", className, reinterpret_cast<std::uintptr_t>(m_hWnd)).c_str());
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Destroy a system window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(m_hWnd)).c_str());
		try
		{
			DestroyWindow(m_hWnd);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(m_engine, e, "On a window destroy.");
		}
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("System window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(m_hWnd)).c_str());
	}

	const char* WindowsWindow::GetName() const noexcept
	{
		return Name;
	}

	const wchar_t* WindowsWindow::GetTitle() const noexcept
	{
		return m_title.c_str();
	}

	void WindowsWindow::SetTitle(const wchar_t* const title)
	{
		if (!SetWindowText(m_hWnd, title))
		{
			throw std::logic_error(std::format("Couldn't set a new window title. Error code: '{}'.", GetLastError()));
		}

		m_title = title;
	}

	void WindowsWindow::AddKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver != nullptr));
		assert((std::ranges::find(std::as_const(m_keyboardMessageObservers), keyboardMessageObserver) == m_keyboardMessageObservers.cend()));
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Add a keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());

		m_keyboardMessageObservers.push_back(keyboardMessageObserver);
	}

	void WindowsWindow::RemoveKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(keyboardMessageObserver == nullptr, m_engine, Debug::Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer.");

		if (const auto position = std::ranges::find(std::as_const(m_keyboardMessageObservers), keyboardMessageObserver); position != m_keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Remove a keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());
			m_keyboardMessageObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver != nullptr, m_engine, Debug::Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		}
	}

	void WindowsWindow::ShowWindow()
	{
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	void WindowsWindow::Tick()
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Verbose, "Dispatch messages.");

		MSG message;
		while (PeekMessage(&message, m_hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return m_hWnd;
	}

	bool WindowsWindow::IsWindowAlive() const noexcept
	{
		return m_isAlive;
	}

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_DESTROY:
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Received a destroy command.");
			Destroy();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Received a key down command with the code '{}' and param '{}'.", wParam, lParam).c_str());
			PushKeyboardKeyMessage(lParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Received a key up command with the code '{}' and param '{}'.", wParam, lParam).c_str());
			PushKeyboardKeyMessage(lParam, false);
			break;
		default: 
			break;
		}

		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::Destroy() noexcept
	{
		m_isAlive = false;
		m_engine.Stop();
	}

	void WindowsWindow::PushKeyboardKeyMessage(const LPARAM lParam, const bool isDown) const
	{
		if (const KeyboardKeyCode keyCode = ConvertToKeyCode(lParam); keyCode != KeyboardKeyCode::None)
		{
			const KeyboardMessage keyboardMessage(keyCode, isDown);
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Push a keyboard message '{}' to the observers.", keyboardMessage.ToString()).c_str());

			for (IKeyboardObserver* const observer : m_keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(m_engine, e, "On observing to a keyboard key message.");
				}
			}
		}
	}

	const char* const WindowsWindow::Name = "PonyEngine::Window::WindowsWindow";
}
