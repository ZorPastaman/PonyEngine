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
import <stdexcept>;
import <string>;
import <vector>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Utility;
import PonyEngine.Window;
import PonyEngine.Window.Windows;

import :IWindowProc;
import :WindowParams;
import :WindowsKeyCodeMap;

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
		WindowsWindow(Core::IEngine& engine, HINSTANCE hInstance, const std::wstring& className, const WindowParams& windowParams);
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;

		virtual ~WindowsWindow() noexcept;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetName() const noexcept override; // TODO: add to logs

		[[nodiscard("Pure function")]]
		inline virtual const std::wstring& GetTitle() const noexcept override;
		virtual void SetTitle(const std::wstring& title) override;

		inline virtual void AddKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;
		virtual void RemoveKeyboardMessageObserver(IKeyboardObserver* keyboardMessageObserver) override;

		inline virtual void ShowWindow() override;

		virtual void Tick() override;

		[[nodiscard("Pure function")]]
		inline virtual HWND GetWindowHandle() const noexcept;

		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		WindowsWindow& operator =(const WindowsWindow&) = delete;
		WindowsWindow& operator =(WindowsWindow&&) = delete;

	private:
		/// @brief Updates a window cursor.
		void UpdateCursor();

		/// @brief Sends a keyboard message to the @p m_keyboardMessageObservers.
		/// @param wParam Windows key code.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(WPARAM wParam, bool isDown);

	public:
		static const char* const Name;

	private:
		std::vector<IKeyboardObserver*> m_keyboardMessageObservers; /// @brief Keyboard message observers.

		std::wstring m_title;
		Core::IEngine& m_engine; /// @brief Engine that owns the window.
		HWND m_hWnd; /// @brief Window handler.
		const int m_nCmdShow; /// @brief Show type.
	};

	WindowsWindow::WindowsWindow(Core::IEngine& engine, const HINSTANCE hInstance, const std::wstring& className, const WindowParams& windowParams) :
		m_keyboardMessageObservers{},
		m_title(windowParams.title),
		m_engine{engine},
		m_nCmdShow{windowParams.cmdShow}
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Create a window of the class '{}'.", Utility::ConvertToString(className)).c_str());
		m_hWnd = CreateWindowEx(
			0,
			className.c_str(),
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
			throw std::logic_error(std::format("Windows hasn't created a window. Error code: {}.", GetLastError()));
		}

		PONY_LOG(m_engine, Debug::Log::LogType::Info, std::format("Window of the class '{}' created.", Utility::ConvertToString(className)).c_str());
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Destroy a window.");
		try
		{
			DestroyWindow(m_hWnd);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(m_engine, e, "On a window destroy.");
		}
		PONY_LOG(m_engine, Debug::Log::LogType::Info, "Window destroyed.");
	}

	inline const char* WindowsWindow::GetName() const noexcept
	{
		return Name;
	}

	inline const std::wstring& WindowsWindow::GetTitle() const noexcept // TODO: use const wchar_t* in get/set
	{
		return m_title;
	}

	void WindowsWindow::SetTitle(const std::wstring& title)
	{
		if (!SetWindowText(m_hWnd, title.c_str()))
		{
			throw std::logic_error(std::format("Couldn't set a new window title. Error code: {}.", GetLastError()));
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

	LRESULT WindowsWindow::WindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_DESTROY:
			PONY_LOG(m_engine, Debug::Log::LogType::Info, "Received a destroy command.");
			m_engine.Stop(0);
			break;
		// Window
		case WM_SETCURSOR:
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, "Received a set cursor command.");
			UpdateCursor(); // TODO: Seems it's enough to check it once. Need to check.
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Received a key down command with the code '{}'.", wParam).c_str());
			PushKeyboardKeyMessage(wParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Received a key up command with the code '{}'.", wParam).c_str());
			PushKeyboardKeyMessage(wParam, false);
			break;
		}

		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::UpdateCursor()
	{
		PONY_LOG(m_engine, Debug::Log::LogType::Verbose, "Update a cursor to a standard arrow.");
		HANDLE hCursor = LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED); // TODO: Make appropriate checks based on the todo from windowproc.
		if (hCursor != NULL) [[likely]]
		{
			SetCursor(static_cast<HCURSOR>(hCursor));
		}
		else [[unlikely]]
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Error, "Couldn't load an arrow cursor.");
		}
	}

	void WindowsWindow::PushKeyboardKeyMessage(const WPARAM wParam, const bool isDown)
	{
		// TODO: manage Shift, Ctrl and Alt in the correct way.
		const std::unordered_map<WPARAM, KeyboardKeyCode>::const_iterator pair = WindowsKeyCodeMap.find(wParam);

		if (pair != WindowsKeyCodeMap.cend())
		{
			PONY_LOG(m_engine, Debug::Log::LogType::Verbose, std::format("Push a keyboard message to the observers. KeyCode: '{}'. IsDown: '{}'.", ToString(pair->second), isDown).c_str());

			const KeyboardMessage keyboardMessage(pair->second, isDown);

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
