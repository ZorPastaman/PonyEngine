/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowsWindow;

import <exception>;
import <stdexcept>;
import <string>;
import <utility>;
import <vector>;
import <windows.h>;

import PonyEngine.Core;
import PonyEngine.Window;

import :IEngineWindow;
import :WindowsKeyCodeToKeyboardKeyCode;

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
		WindowsWindow(const WindowsWindow& other) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		WindowsWindow(WindowsWindow&& other);

		virtual ~WindowsWindow() noexcept;

		virtual void AddKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener) override;
		virtual void RemoveKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener) override;

		virtual void ShowWindow() override;

		virtual void Tick() override;

	private:
		/// @brief Processes a window message.
		/// @param uMsg Window message.
		/// @param wParam WParam.
		/// @param lParam LParam.
		/// @return Process result.
		LRESULT LocalWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void PushKeyboardKeyMessage(WPARAM wParam, bool isDown) noexcept;

		std::vector<MessageListeners::IKeyboardMessageListener*> m_keyboardMessageListeners;

		std::wstring m_className; /// @brief Window class name.
		Core::IEngine& m_engine; /// @brief Engine that owns the window.
		HINSTANCE m_hInstance; /// @brief Application that owns the engine.
		HWND m_hWnd; /// @brief Window handler.
		int m_nCmdShow; /// @brief Show type.

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

	void WindowsWindow::AddKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener)
	{
		m_keyboardMessageListeners.push_back(&keyboardMessageListener);
	}

	void WindowsWindow::RemoveKeyboardMessageListener(MessageListeners::IKeyboardMessageListener& keyboardMessageListener)
	{
		const std::vector<MessageListeners::IKeyboardMessageListener*>::iterator position = std::find(m_keyboardMessageListeners.begin(), m_keyboardMessageListeners.end(), &keyboardMessageListener);

		if (position != m_keyboardMessageListeners.end()) [[likely]]
		{
			m_keyboardMessageListeners.erase(position);
		}
	}

	void WindowsWindow::ShowWindow()
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

	LRESULT WindowsWindow::LocalWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

	void WindowsWindow::PushKeyboardKeyMessage(WPARAM wParam, bool isDown) noexcept
	{
		const std::unordered_map<WPARAM, Messages::KeyboardKeyCode>::const_iterator pair = WindowsKeyCodeToKeyboardKeyCode.find(wParam);
		if (pair != WindowsKeyCodeToKeyboardKeyCode.end())
		{
			Messages::KeyboardMessage keyboardMessage(pair->second, isDown);

			for (MessageListeners::IKeyboardMessageListener* const listener : m_keyboardMessageListeners)
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

	static LRESULT CALLBACK GlobalWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (window == nullptr) [[unlikely]]
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return window->LocalWindowProc(uMsg, wParam, lParam);
	}
}
