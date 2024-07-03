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

#include "PonyEngine/Log/LogMacro.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindowFactory;

import <cstdint>;
import <exception>;
import <format>;
import <functional>;
import <stdexcept>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Log;
import PonyEngine.Input;
import PonyEngine.Utility;
import PonyEngine.Window;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factories;

import :IWindowProc;
import :WindowParams;
import :WindowProcFunction;
import :WindowsWindow;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowFactory final : public IWindowsWindowFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param logger Logger.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowFactory(Log::ILogger& logger, const WindowClassParams& classParams);
		WindowsWindowFactory(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory(WindowsWindowFactory&&) = delete;

		~WindowsWindowFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::SystemInfo Create(Core::IEngine& engine) override;
		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const wchar_t* GetTitle() const noexcept override;
		virtual void SetTitle(const wchar_t* title) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetWindowName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual int GetCmdShow() const noexcept override;
		virtual void SetCmdShow(int cmdShow) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		WindowsWindowFactory& operator =(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory& operator =(WindowsWindowFactory&&) = delete;

		static constexpr const char* Name = "PonyEngine::Window::WindowsWindowFactory"; ///< Class name.

	private:
		void Destroy(Core::ISystem* system) const noexcept;

		WindowParams windowParams; ///< Window parameters.

		Log::ILogger& logger; ///< Logger.

		HINSTANCE hInstance; ///< This dll instance.
		ATOM classAtom; ///< Window class atom.
	};
}

namespace PonyEngine::Window
{
	/// @brief Empty function.
	void Dummy();

	WindowsWindowFactory::WindowsWindowFactory(Log::ILogger& logger, const WindowClassParams& classParams) :
		logger{logger},
		hInstance{NULL}
	{
		if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&Dummy), &hInstance) || hInstance == NULL)
		{
			throw std::logic_error(std::format("Couldn't find a dll module to create a window. Error code: '{}'.", GetLastError()));
		}

		const wchar_t* const className = classParams.GetWindowClassName().c_str();

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Load a main cursor. Cursor id: '{}'.", reinterpret_cast<std::uintptr_t>(IDC_ARROW)).c_str());
		const auto cursor = static_cast<HCURSOR>(LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (cursor == NULL)
		{
			throw std::logic_error(std::format("Couldn't load a class cursor. Error code: '{}'", GetLastError()));
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Main cursor loaded. Cursor id: '{}'.", reinterpret_cast<std::uintptr_t>(IDC_ARROW)).c_str());

		WNDCLASS wc{};
		wc.hCursor = cursor;
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Register a window class '{}'.", Utility::ConvertToString(className)).c_str());
		classAtom = RegisterClass(&wc);
		if (!classAtom)
		{
			throw std::logic_error(std::format("Couldn't register a class. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window class '{}' registered with id '{}'.", Utility::ConvertToString(className), classAtom).c_str());
	}

	WindowsWindowFactory::~WindowsWindowFactory() noexcept
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Unregister a window class with id '{}'.", classAtom).c_str());
		try
		{
			if (!UnregisterClass(reinterpret_cast<LPCTSTR>(classAtom), hInstance))
			{
				throw std::logic_error(std::format("Couldn't unregister a class. Error code: '{}'.", GetLastError()));
			}
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E_GENERAL(logger, e, "On unregistering a window class");
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window class with id '{}' unregistered.", classAtom).c_str());
	}

	Core::SystemInfo WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		const auto window = new WindowsWindow(engine, hInstance, classAtom, windowParams);
		const HWND hWnd = window->GetWindowHandle();
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Register a window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		RegisterWindowProc(hWnd, window);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window proc registered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		Core::SystemInfo systemInfo;
		systemInfo.Set<WindowsWindow, IWindow, IWindowsWindow, Input::IKeyboardProvider>(window, std::bind(&WindowsWindowFactory::Destroy, this, std::placeholders::_1), true);

		return systemInfo;
	}

	void WindowsWindowFactory::Destroy(Core::ISystem* const system) const noexcept
	{
		assert((dynamic_cast<WindowsWindow*>(system) != nullptr));
		const auto windowsWindow = static_cast<WindowsWindow*>(system);
		const HWND hWnd = windowsWindow->GetWindowHandle();

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Unregister a window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		if (windowsWindow->IsWindowAlive())
		{
			try
			{
				UnregisterWindowProc(windowsWindow->GetWindowHandle());
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E_GENERAL(logger, e, "On unregistering a window proc");
			}
		}
		else
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window is already destroyed. No unregistering a window proc required. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window proc unregistered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Destroy a windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		delete windowsWindow;
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Windows window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	const char* WindowsWindowFactory::GetSystemName() const noexcept
	{
		return WindowsWindow::Name;
	}

	const wchar_t* WindowsWindowFactory::GetTitle() const noexcept
	{
		return windowParams.title.c_str();
	}

	void WindowsWindowFactory::SetTitle(const wchar_t* const title) noexcept
	{
		windowParams.title = title;
	}

	const char* WindowsWindowFactory::GetWindowName() const noexcept
	{
		return WindowsWindow::Name;
	}

	int WindowsWindowFactory::GetCmdShow() const noexcept
	{
		return windowParams.cmdShow;
	}

	void WindowsWindowFactory::SetCmdShow(const int cmdShow) noexcept
	{
		windowParams.cmdShow = cmdShow;
	}

	const char* WindowsWindowFactory::GetName() const noexcept
	{
		return Name;
	}

	void Dummy()
	{
	}
}
