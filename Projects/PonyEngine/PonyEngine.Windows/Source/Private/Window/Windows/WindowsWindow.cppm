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

namespace PonyEngine::Window
{
	/// @brief Engine window for @p Windows platform.
	export class WindowsWindow final : public IWindowsWindow, public IWindowProc
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

		virtual ~WindowsWindow() noexcept;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetName() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) override;

		inline virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;

		inline virtual void ShowWindow() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		inline virtual HWND GetWindowHandle() const noexcept;

		[[nodiscard("Pure function")]]
		inline virtual bool IsWindowAlive() const noexcept override;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

	private:
		/// @brief Responds to a destroy message.
		inline void Destroy() noexcept;

		/// @brief Sends a keyboard message to the @p m_keyboardMessageObservers.
		/// @param lParam Windows key info.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(LPARAM lParam, bool isDown);

	public:
		static const char* const Name; /// @brief WindowsWindow class name.

	private:
		std::vector<IKeyboardObserver*> m_keyboardMessageObservers; /// @brief Keyboard message observers.

		std::wstring m_title;
		HWND m_hWnd; /// @brief Window handler.
		const int m_nCmdShow; /// @brief Show type.
		bool m_isAlive; /// @brief Is the system window alive?

		Core::IEngine& m_engine; /// @brief Engine that owns the window.
	};

	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const ATOM className, const WindowParams& windowParams) :
		m_keyboardMessageObservers{},
		m_title(windowParams.title),
		m_engine{engine},
		m_nCmdShow{windowParams.cmdShow},
		m_isAlive{false}
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

	inline const char* WindowsWindow::GetName() const noexcept
	{
		return Name;
	}

	inline const wchar_t* WindowsWindow::GetTitle() const noexcept
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

	inline void WindowsWindow::AddKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver != nullptr));
		assert((std::find(m_keyboardMessageObservers.cbegin(), m_keyboardMessageObservers.cend(), keyboardMessageObserver) == m_keyboardMessageObservers.cend()));
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Add a keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());

		m_keyboardMessageObservers.push_back(keyboardMessageObserver);
	}

	void WindowsWindow::RemoveKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(keyboardMessageObserver == nullptr, m_engine, Debug::Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer.");

		const std::vector<IKeyboardObserver*>::const_iterator position = std::find(m_keyboardMessageObservers.cbegin(), m_keyboardMessageObservers.cend(), keyboardMessageObserver);

		if (position != m_keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Remove a keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());
			m_keyboardMessageObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver != nullptr, m_engine, Debug::Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'.", keyboardMessageObserver->GetName()).c_str());
		}
	}

	inline void WindowsWindow::ShowWindow()
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

	inline HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return m_hWnd;
	}

	inline bool WindowsWindow::IsWindowAlive() const noexcept
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
		}

		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	inline void WindowsWindow::Destroy() noexcept
	{
		m_isAlive = false;
		m_engine.Stop(0);
	}

	void WindowsWindow::PushKeyboardKeyMessage(const LPARAM lParam, const bool isDown)
	{
		const KeyboardKeyCode keyCode = ConvertToKeyCode(lParam);

		if (keyCode != KeyboardKeyCode::None)
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
