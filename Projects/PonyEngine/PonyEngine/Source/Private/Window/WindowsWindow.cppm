/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window.Implementation:WindowsWindow;

import <string>;
import <utility>;
import <windows.h>;

import :IEngineWindow;

namespace PonyEngine::Window
{
	export class WindowsWindow final : public IEngineWindow
	{
	public:
		WindowsWindow(std::string title, HINSTANCE hInstance, int nCmdShow);
		WindowsWindow(const WindowsWindow& other) = delete;
		WindowsWindow(WindowsWindow&& other);

		virtual ~WindowsWindow();

		virtual void ShowWindow() override;

	private:
		WNDCLASS m_wc;
		std::wstring m_windowName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;
		int m_nCmdShow;
	};

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WindowsWindow::WindowsWindow(std::string title, HINSTANCE hInstance, int nCmdShow) :
		m_wc{},
		m_windowName(title.begin(), title.end()),
		m_hInstance(hInstance),
		m_nCmdShow{nCmdShow}
	{
		m_wc.lpfnWndProc = WindowProc;
		m_wc.hInstance = m_hInstance;
		m_wc.lpszClassName = m_windowName.c_str();
		RegisterClass(&m_wc);

		m_hWnd = CreateWindowEx(
			0,
			m_windowName.c_str(),
			m_windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			m_hInstance,
			NULL
		);
	}

	WindowsWindow::WindowsWindow(WindowsWindow&& other) :
		m_wc(std::move(other.m_wc)),
		m_windowName(std::move(other.m_windowName)),
		m_hInstance(std::move(other.m_hInstance)),
		m_hWnd(std::move(other.m_hWnd)),
		m_nCmdShow{other.m_nCmdShow}
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		DestroyWindow(m_hWnd);
		UnregisterClass(m_windowName.c_str(), m_hInstance);
	}

	void WindowsWindow::ShowWindow()
	{
		::ShowWindow(m_hWnd, m_nCmdShow);
	}

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
