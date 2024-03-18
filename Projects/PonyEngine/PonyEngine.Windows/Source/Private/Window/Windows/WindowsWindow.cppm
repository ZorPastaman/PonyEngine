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
import <format>;
import <exception>;
import <iostream>;
import <stdexcept>;
import <string>;
import <utility>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Utility;
import PonyEngine.Window;
import PonyEngine.Window.Windows;

import :WindowParams;
import :WindowsKeyCodeMap;

namespace PonyEngine::Window
{
	/// @brief Engine window for @p Windows platform.
	export class WindowsWindow final : public IWindowsWindow
	{
	public:
		/// @brief Creates a @p WindowsWindow.
		/// @param engine Engine that owns the window.
		/// @param hInstance Instance that owns the engine.
		/// @param className Class name of a registered class.
		/// @param windowParams Window parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(Core::IEngine& engine, HINSTANCE hInstance, const std::wstring& className, const WindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		virtual ~WindowsWindow() noexcept;

		[[nodiscard("Pure function")]]
		virtual std::wstring GetTitle() const override;
		inline virtual void SetTitle(const std::wstring& title) override;

		inline virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;

		inline virtual void ShowWindow() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		inline virtual HWND GetWindowHandle() const noexcept;

		/// @brief Processes a window message.
		/// @param uMsg Window message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Process result.
		LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

	private:
		/// @brief Updates a window cursor.
		void UpdateCursor();

		/// @brief Sends a keyboard message to the @p m_keyboardMessageObservers.
		/// @param wParam Windows key code.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(WPARAM wParam, bool isDown);

		std::vector<IKeyboardObserver*> m_keyboardMessageObservers; /// @brief Keyboard message observers.

		Core::IEngine& m_engine; /// @brief Engine that owns the window.
		HWND m_hWnd; /// @brief Window handler.
		const int m_nCmdShow; /// @brief Show type.
	};

	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const std::wstring& className, const WindowParams& windowParams) :
		m_keyboardMessageObservers{},
		m_engine{engine},
		m_nCmdShow{windowParams.cmdShow}
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Create a window of the class '{}'", Utility::ConvertToString(className)).c_str());
		m_hWnd = CreateWindowEx(
			0,
			className.c_str(),
			windowParams.title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (m_hWnd == NULL)
		{
			throw std::logic_error("Windows hasn't created a window.");
		}
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Window of the class '{}' created", Utility::ConvertToString(className)).c_str());

		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy a window");
		try
		{
			DestroyWindow(m_hWnd);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(m_engine.GetLogger(), e, "On a window destroy");
		}
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window destroyed");
	}

	std::wstring WindowsWindow::GetTitle() const
	{
		std::wstring title;
		size_t length = static_cast<size_t>(GetWindowTextLength(m_hWnd)) + 1;
		wchar_t* titleChars = new wchar_t[length];

		try
		{
			std::fill_n(titleChars, length, wchar_t{0});
			GetWindowText(m_hWnd, titleChars, static_cast<int>(length));
			title = titleChars;
		}
		catch (const std::exception& e)
		{
			delete[] titleChars;
			throw e;
		}

		delete[] titleChars;

		return title;
	}

	inline void WindowsWindow::SetTitle(const std::wstring& title)
	{
		SetWindowText(m_hWnd, title.c_str());
	}

	inline void WindowsWindow::AddKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		assert((keyboardMessageObserver != nullptr));
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Add a keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());

		m_keyboardMessageObservers.push_back(keyboardMessageObserver);
	}

	void WindowsWindow::RemoveKeyboardMessageObserver(IKeyboardObserver* const keyboardMessageObserver)
	{
		PONY_LOG_IF(keyboardMessageObserver == nullptr, m_engine.GetLogger(), Debug::Log::LogType::Warning, "Tried to remove a nullptr keyboard message observer");

		const std::vector<IKeyboardObserver*>::const_iterator position = std::find(m_keyboardMessageObservers.cbegin(), m_keyboardMessageObservers.cend(), keyboardMessageObserver);

		if (position != m_keyboardMessageObservers.cend()) [[likely]]
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Remove a keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());
			m_keyboardMessageObservers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageObserver != nullptr, m_engine.GetLogger(), Debug::Log::LogType::Warning, std::format("Tried to remove a not added keyboard message observer '{}'", keyboardMessageObserver->GetName()).c_str());
		}
	}

	inline void WindowsWindow::ShowWindow()
	{
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	void WindowsWindow::Tick()
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Dispatch messages");

		MSG message;
		while (PeekMessage(&message, m_hWnd, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			DispatchMessage(&message);

			if (TranslateMessage(&message))
			{
				DispatchMessage(&message);
			}
		}
	}

	inline HWND WindowsWindow::GetWindowHandle() const noexcept
	{
		return m_hWnd;
	}

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_DESTROY:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Received a destroy command");
			m_engine.Stop(0);
			break;
		// Window
		case WM_SETCURSOR:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Received a set cursor command");
			UpdateCursor();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Received a key down command with the code '{}'", wParam).c_str());
			PushKeyboardKeyMessage(wParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Received a key up command with the code '{}'", wParam).c_str());
			PushKeyboardKeyMessage(wParam, false);
			break;
		}

		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::UpdateCursor()
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Update a cursor to a standard arrow");
		HANDLE hCursor = LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		if (hCursor != NULL) [[likely]]
		{
			SetCursor(static_cast<HCURSOR>(hCursor));
		}
		else [[unlikely]]
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Error, "Couldn't load an arrow cursor");
		}
	}

	void WindowsWindow::PushKeyboardKeyMessage(const WPARAM wParam, const bool isDown)
	{
		const std::unordered_map<WPARAM, KeyboardKeyCode>::const_iterator pair = WindowsKeyCodeMap.find(wParam);
		if (pair != WindowsKeyCodeMap.cend())
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Push a keyboard message to the observers. KeyCode: '{}'. IsDown: '{}'", ToString(pair->second), isDown).c_str());

			const KeyboardMessage keyboardMessage(pair->second, isDown);

			for (IKeyboardObserver* const observer : m_keyboardMessageObservers)
			{
				try
				{
					observer->Observe(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(m_engine.GetLogger(), e, "On observing to a keyboard key message");
				}
			}
		}
	}
}
