/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Window.Implementation:WindowsWindow;

import <algorithm>;
import <cassert>;
import <format>;
import <exception>;
import <iostream>;
import <stdexcept>;
import <string>;
import <utility>;
import <vector>;

import <windows.h>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Window;

import :IEngineWindow;
import :WindowsKeyCodeMap;

namespace PonyEngine::Window
{
	/// @brief Engine window for @p Windows platform.
	export class WindowsWindow final : public IEngineWindow
	{
	public:
		/// @brief Creates a @p WindowsWindow
		/// @param title Window title.
		/// @param engine Engine that owns the window.
		/// @param hInstance Application that owns the engine.
		/// @param nCmdShow Show type.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(const std::string& title, Core::IEngine& engine, HINSTANCE hInstance, int nCmdShow);
		WindowsWindow(const WindowsWindow&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(WindowsWindow&& other);

		virtual ~WindowsWindow() noexcept;

		virtual std::string GetTitle() const override;
		virtual bool SetTitle(const std::string& title) override;

		inline virtual void AddKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) override;
		virtual void RemoveKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) override;

		inline virtual void* GetNativeWindow() override;

		inline virtual void ShowWindow() override;

		virtual void Tick() override;

	private:
		/// @brief Processes a window message.
		/// @param uMsg Window message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Process result.
		LRESULT LocalWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		/// @brief Updates a window cursor.
		void UpdateCursor();

		/// @brief Sends a keyboard message to the @p m_keyboardMessageListeners.
		/// @param wParam Windows key code.
		/// @param isDown @a True if the button is pressed, @a false if it's up.
		void PushKeyboardKeyMessage(WPARAM wParam, bool isDown);

		std::vector<Listeners::IKeyboardListener*> m_keyboardMessageListeners; /// @brief Keyboard message listeners.

		const std::wstring m_className; /// @brief Window class name.
		Core::IEngine& m_engine; /// @brief Engine that owns the window.
		const HINSTANCE m_hInstance; /// @brief Application that owns the engine.
		HWND m_hWnd; /// @brief Window handler.
		const int m_nCmdShow; /// @brief Show type.

		friend static LRESULT CALLBACK GlobalWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

	/// @brief Process window messages.
	/// @details Actually, it translates invocations to a corresponding @p WindowsWindow.
	///          It's needed because WinAPI doesn't take pointers to member functions.
	/// @param hWnd Window handler.
	/// @param uMsg Window message.
	/// @param wParam WParam.
	/// @param lParam LParam.
	/// @return Process result.
	static LRESULT CALLBACK GlobalWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WindowsWindow::WindowsWindow(const std::string& title, Core::IEngine& engine, const HINSTANCE hInstance, const int nCmdShow) :
		m_keyboardMessageListeners{},
		m_className(title.cbegin(), title.cend()),
		m_engine{engine},
		m_hInstance(hInstance),
		m_nCmdShow{nCmdShow}
	{
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Create a window class");
		WNDCLASS wc{};
		wc.lpfnWndProc = &GlobalWindowProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = m_className.c_str();
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window class created");
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Register a window class");
		RegisterClass(&wc);
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window class registered");

		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Create a window");
		m_hWnd = CreateWindowEx(
			0,
			m_className.c_str(),
			std::wstring(title.cbegin(), title.cend()).c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			m_hInstance,
			NULL
		);

		if (m_hWnd == NULL)
		{
			UnregisterClass(m_className.c_str(), m_hInstance);

			throw std::logic_error("Windows hasn't created a window.");
		}
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window created");

		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	WindowsWindow::WindowsWindow(WindowsWindow&& other) :
		m_keyboardMessageListeners(std::move(other.m_keyboardMessageListeners)),
		m_className(std::move(other.m_className)),
		m_engine{other.m_engine},
		m_hInstance(std::move(other.m_hInstance)),
		m_hWnd(std::move(other.m_hWnd)),
		m_nCmdShow{other.m_nCmdShow}
	{
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
		try
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Destroy a window");
			DestroyWindow(m_hWnd);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window destroyed");
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Unregister a window class");
			UnregisterClass(m_className.c_str(), m_hInstance);
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Window class unregistered");
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E(m_engine.GetLogger(), e, "On a window destroy");
		}
	}

	std::string WindowsWindow::GetTitle() const
	{
		size_t length = GetWindowTextLength(m_hWnd) + 1;
		std::string title(length, 0);

		wchar_t* wtitle = new wchar_t[length];

		try
		{
			std::fill_n(wtitle, length, wchar_t{0});
			GetWindowText(m_hWnd, wtitle, length);

			for (size_t i = 0; i < length; ++i)
			{
				title[i] = static_cast<char>(wtitle[i]);
			}
		}
		catch (const std::exception& e)
		{
			delete[] wtitle;
			throw e;
		}

		delete[] wtitle;

		return title;
	}

	bool WindowsWindow::SetTitle(const std::string& title)
	{
		std::wstring wtitle(title.cbegin(), title.cend());
		return SetWindowText(m_hWnd, wtitle.c_str());
	}

	inline void WindowsWindow::AddKeyboardMessageListener(Listeners::IKeyboardListener* const keyboardMessageListener)
	{
		assert((keyboardMessageListener != nullptr));
		PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Add a keyboard message listener '{}'", keyboardMessageListener->GetName()));

		m_keyboardMessageListeners.push_back(keyboardMessageListener);
	}

	void WindowsWindow::RemoveKeyboardMessageListener(Listeners::IKeyboardListener* const keyboardMessageListener)
	{
		PONY_LOG_IF(keyboardMessageListener == nullptr, m_engine.GetLogger(), Debug::Log::LogType::Warning, "Tried to remove a nullptr keyboard message listener");

		const std::vector<Listeners::IKeyboardListener*>::const_iterator position = std::find(m_keyboardMessageListeners.cbegin(), m_keyboardMessageListeners.cend(), keyboardMessageListener);

		if (position != m_keyboardMessageListeners.cend()) [[likely]]
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, std::format("Remove a keyboard message listener '{}'", keyboardMessageListener->GetName()));
			m_keyboardMessageListeners.erase(position);
		}
		else [[unlikely]]
		{
			PONY_LOG_IF(keyboardMessageListener != nullptr, m_engine.GetLogger(), Debug::Log::LogType::Warning, std::format("Tried to remove a not added keyboard message listener '{}'", keyboardMessageListener->GetName()));
		}
	}

	inline void* WindowsWindow::GetNativeWindow()
	{
		return static_cast<void*>(&m_hWnd);
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
		}
	}

	LRESULT WindowsWindow::LocalWindowProc(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		// Main
		case WM_DESTROY:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Info, "Received a destroy command");
			m_engine.Stop(0);
			break;
		case WM_SETCURSOR:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, "Received a set cursor command");
			UpdateCursor();
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Received a key down command with the code '{}'", wParam));
			PushKeyboardKeyMessage(wParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Received a key up command with the code '{}'", wParam));
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
		const std::unordered_map<WPARAM, Messages::KeyboardKeyCode>::const_iterator pair = WindowsKeyCodeMap.find(wParam);
		if (pair != WindowsKeyCodeMap.cend())
		{
			PONY_LOG(m_engine.GetLogger(), Debug::Log::LogType::Verbose, std::format("Push a keyboard message to the listeners. KeyCode: '{}'. IsDown: '{}'", PonyEngine::Window::Messages::ToString(pair->second), isDown));

			const Messages::KeyboardMessage keyboardMessage(pair->second, isDown);

			for (Listeners::IKeyboardListener* const listener : m_keyboardMessageListeners)
			{
				try
				{
					listener->Listen(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					PONY_LOG_E(m_engine.GetLogger(), e, "On listening to a keyboard key message");
				}
			}
		}
	}

	static LRESULT CALLBACK GlobalWindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		WindowsWindow* const window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (window == nullptr) [[unlikely]]
		{
			PONY_CERR("Window pointer is nullptr. The window window won't receive a command.");
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return window->LocalWindowProc(uMsg, wParam, lParam);
	}
}
