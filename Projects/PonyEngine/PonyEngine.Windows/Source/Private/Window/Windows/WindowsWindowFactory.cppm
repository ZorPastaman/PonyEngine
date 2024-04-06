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

export module PonyEngine.Window.Windows.Implementation:WindowsWindowFactory;

import <cstdint>;
import <exception>;
import <format>;
import <stdexcept>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Utility;
import PonyEngine.Window;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factories;

import :IWindowProc;
import :WindowParams;
import :WindowProcFunction;
import :WindowsWindow;

namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	export class WindowsWindowFactory final : public IWindowsWindowFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param logger Logger.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams);
		WindowsWindowFactory(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory(WindowsWindowFactory&&) = delete;

		virtual ~WindowsWindowFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual IWindowsWindow* Create(Core::IEngine& engine) override;
		virtual void Destroy(IWindow* window) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const wchar_t* GetTitle() const noexcept override;
		inline virtual void SetTitle(const wchar_t* title) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const char* GetWindowName() const noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual int GetCmdShow() const noexcept override;
		inline virtual void SetCmdShow(int cmdShow) noexcept override;

		WindowsWindowFactory& operator =(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory& operator =(WindowsWindowFactory&&) = delete;

	private:
		WindowParams m_windowParams; /// @brief Window parameters.

		Debug::Log::ILogger& m_logger; /// @brief Logger.

		HINSTANCE m_hInstance; /// @brief This dll instance.
		ATOM m_className; /// @brief Window class atom.
	};

	/// @brief Empty function.
	static void Dummy();

	WindowsWindowFactory::WindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams) :
		m_windowParams(),
		m_logger{logger},
		m_hInstance{NULL}		
	{
		if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&Dummy), &m_hInstance) || m_hInstance == NULL)
		{
			throw std::logic_error(std::format("Couldn't find a dll module to create a window. Error code: '{}'.", GetLastError()));
		}

		const wchar_t* const className = classParams.GetWindowClassName().c_str();

		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Load a main cursor. Cursor id: '{}'.", reinterpret_cast<std::uintptr_t>(IDC_ARROW)).c_str());
		HCURSOR cursor = static_cast<HCURSOR>(LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (cursor == NULL)
		{
			throw std::logic_error(std::format("Couldn't load a class cursor. Error code: '{}'", GetLastError()));
		}
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Main cursor loaded. Cursor id: '{}'.", reinterpret_cast<std::uintptr_t>(IDC_ARROW)).c_str());

		WNDCLASS wc{};
		wc.hCursor = cursor;
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = className;

		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Register a window class '{}'.", Utility::ConvertToString(className)).c_str());
		m_className = RegisterClass(&wc);
		if (!m_className)
		{
			throw std::logic_error(std::format("Couldn't register a class. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window class '{}' registered with id '{}'.", Utility::ConvertToString(className), m_className).c_str());
	}

	WindowsWindowFactory::~WindowsWindowFactory() noexcept
	{
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Unregister a window class with id '{}'.", m_className).c_str());
		try
		{
			if (!UnregisterClass(reinterpret_cast<LPCTSTR>(m_className), m_hInstance))
			{
				throw std::logic_error(std::format("Couldn't unregister a class. Error code: '{}'.", GetLastError()));
			}
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E_GENERAL(m_logger, e, "On unregistering a window class");
		}
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window class with id '{}' unregistered.", m_className).c_str());
	}

	IWindowsWindow* WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		WindowsWindow* const window = new WindowsWindow(engine, m_hInstance, m_className, m_windowParams);
		const HWND hWnd = window->GetWindowHandle();
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Register a window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		RegisterWindowProc(hWnd, window);
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window proc registered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		return window;
	}

	void WindowsWindowFactory::Destroy(IWindow* const window) noexcept
	{
		assert((dynamic_cast<WindowsWindow*>(window) != nullptr));
		WindowsWindow* const windowsWindow = static_cast<WindowsWindow*>(window);
		const HWND hWnd = windowsWindow->GetWindowHandle();

		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Unregister a window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		if (windowsWindow->IsWindowAlive())
		{
			try
			{
				UnregisterWindowProc(windowsWindow->GetWindowHandle());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E_GENERAL(m_logger, e, "On unregistering a window proc");
			}
		}
		else
		{
			PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window is already destroyed. No unregistering a window proc required. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		}
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window proc unregistered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Destroy a windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		delete windowsWindow;
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Windows window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	inline const wchar_t* WindowsWindowFactory::GetTitle() const noexcept
	{
		return m_windowParams.title.c_str();
	}

	inline void WindowsWindowFactory::SetTitle(const wchar_t* const title) noexcept
	{
		m_windowParams.title = title;
	}

	inline const char* WindowsWindowFactory::GetWindowName() const noexcept
	{
		return WindowsWindow::Name;
	}

	inline int WindowsWindowFactory::GetCmdShow() const noexcept
	{
		return m_windowParams.cmdShow;
	}

	inline void WindowsWindowFactory::SetCmdShow(const int cmdShow) noexcept
	{
		m_windowParams.cmdShow = cmdShow;
	}

	void Dummy()
	{
	}
}
