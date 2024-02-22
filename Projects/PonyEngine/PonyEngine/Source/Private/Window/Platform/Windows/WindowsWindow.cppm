/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowsWindow;

import <cassert>;
import <exception>;
import <stdexcept>;
import <string>;
import <utility>;
import <vector>;

import <windows.h>;

import PonyEngine.Core;
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

		inline virtual void AddKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) override;
		virtual void RemoveKeyboardMessageListener(Listeners::IKeyboardListener* keyboardMessageListener) override;

		inline virtual void ShowWindow() override;

		virtual void Tick() override;

	private:
		/// @brief Processes a window message.
		/// @param uMsg Window message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Process result.
		LRESULT LocalWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	WindowsWindow::WindowsWindow(const std::string& title, Core::IEngine& engine, HINSTANCE hInstance, int nCmdShow) :
		m_keyboardMessageListeners{},
		m_className(title.begin(), title.end()),
		m_engine{engine},
		m_hInstance(hInstance),
		m_nCmdShow{nCmdShow}
	{
		WNDCLASS wc{};
		wc.lpfnWndProc = &GlobalWindowProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = m_className.c_str();
		RegisterClass(&wc);

		m_hWnd = CreateWindowEx(
			0,
			m_className.c_str(),
			std::wstring(title.begin(), title.end()).c_str(),
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
			DestroyWindow(m_hWnd);
			UnregisterClass(m_className.c_str(), m_hInstance);
		}
		catch (const std::exception& e)
		{
			m_engine.GetLogger().LogException(e, "On a window destroy");
		}
	}

	inline void WindowsWindow::AddKeyboardMessageListener(Listeners::IKeyboardListener* const keyboardMessageListener)
	{
		assert((keyboardMessageListener != nullptr));
		m_keyboardMessageListeners.push_back(keyboardMessageListener);
	}

	void WindowsWindow::RemoveKeyboardMessageListener(Listeners::IKeyboardListener* const keyboardMessageListener)
	{
		const std::vector<Listeners::IKeyboardListener*>::const_iterator position = std::find(m_keyboardMessageListeners.cbegin(), m_keyboardMessageListeners.cend(), keyboardMessageListener);

		if (position != m_keyboardMessageListeners.cend()) [[likely]]
		{
			m_keyboardMessageListeners.erase(position);
		}
	}

	inline void WindowsWindow::ShowWindow()
	{
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	void WindowsWindow::Tick()
	{
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
			m_engine.Stop(0);
			break;
		// Input
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			PushKeyboardKeyMessage(wParam, true);
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			PushKeyboardKeyMessage(wParam, false);
			break;
		}

		return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::PushKeyboardKeyMessage(const WPARAM wParam, const bool isDown)
	{
		const std::unordered_map<WPARAM, Messages::KeyboardKeyCode>::const_iterator pair = WindowsKeyCodeMap.find(wParam);
		if (pair != WindowsKeyCodeMap.cend())
		{
			Messages::KeyboardMessage keyboardMessage(pair->second, isDown);

			for (Listeners::IKeyboardListener* const listener : m_keyboardMessageListeners)
			{
				try
				{
					listener->Listen(keyboardMessage);
				}
				catch (const std::exception& e)
				{
					m_engine.GetLogger().LogException(e, "On listening to a keyboard key message");
				}
			}
		}
	}

	static LRESULT CALLBACK GlobalWindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		WindowsWindow* const window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (window == nullptr) [[unlikely]]
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return window->LocalWindowProc(uMsg, wParam, lParam);
	}
}
