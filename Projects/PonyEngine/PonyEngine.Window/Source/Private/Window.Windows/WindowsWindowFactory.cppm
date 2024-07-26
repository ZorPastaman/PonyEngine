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

#include "PonyEngine/Log/EngineLog.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindowFactory;

import <exception>;
import <format>;
import <stdexcept>;
import <string>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.Input;
import PonyEngine.StringUtility;
import PonyEngine.Window.Windows.Factory;

import :CreateWindowParams;
import :IWindowProc;
import :WindowProcFunction;
import :WindowsWindow;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowFactory final : public IWindowsWindowFactory, public Core::ISystemDestroyer
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param loggerToUse Logger.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowFactory(Log::ILogger& loggerToUse, const WindowsClassParams& classParams);
		WindowsWindowFactory(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory(WindowsWindowFactory&&) = delete;

		~WindowsWindowFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::SystemInfo Create(Core::IEngine& engine) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowParams& NextWindowParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowParams& NextWindowParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams& NextWindowsWindowParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowParams& NextWindowsWindowParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetSystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		WindowsWindowFactory& operator =(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory& operator =(WindowsWindowFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindowFactory"; ///< Class name.

	private:
		WindowParams windowParams; ///< Platform-independent window parameters.
		WindowsWindowParams windowsWindowParams; ///< Windows window parameters.

		Log::ILogger* logger; ///< Logger.

		HINSTANCE hInstance; ///< This dll instance.
		ATOM classAtom; ///< Window class atom.
	};
}

namespace PonyEngine::Window
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR GetDefaultCursor();

	WindowsWindowFactory::WindowsWindowFactory(Log::ILogger& loggerToUse, const WindowsClassParams& classParams) :
		logger{&loggerToUse},
		hInstance{NULL}
	{
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&GetDefaultCursor), &hInstance) || hInstance == NULL)
		{
			throw std::logic_error(std::format("Couldn't find a dll module to create a window. Error code: '{}'.", GetLastError()));
		}

		WNDCLASSW wc{};
		wc.lpszClassName = classParams.name.c_str();
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = hInstance;
		wc.hIcon = classParams.icon;
		wc.hCursor = classParams.cursor == NULL ? GetDefaultCursor() : classParams.cursor;
		wc.style = classParams.style;

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Register window class '{}'.", Utility::ConvertToString(classParams.name)).c_str());
		classAtom = RegisterClassW(&wc);
		if (!classAtom)
		{
			throw std::logic_error(std::format("Couldn't register a class. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window class '{}' registered.", classAtom).c_str());
	}

	WindowsWindowFactory::~WindowsWindowFactory() noexcept
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Unregister window class '{}'.", classAtom).c_str());
		try
		{
			if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classAtom), hInstance))
			{
				throw std::logic_error(std::format("Couldn't unregister a class. Error code: '{}'.", GetLastError()));
			}
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E_GENERAL(logger, e, "On unregistering a window class");
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window class '{}' unregistered.", classAtom).c_str());
	}

	Core::SystemInfo WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		CreateWindowParams createWindowParams;
		createWindowParams.title = windowParams.title;
		createWindowParams.style = windowsWindowParams.style;
		createWindowParams.extendedStyle = windowsWindowParams.extendedStyle;
		createWindowParams.horizontalPosition = windowParams.horizontalPosition;
		createWindowParams.verticalPosition = windowParams.verticalPosition;
		createWindowParams.width = windowParams.width;
		createWindowParams.height = windowParams.height;
		createWindowParams.cmdShow = windowsWindowParams.showCmd;

		const auto window = new WindowsWindow(engine, hInstance, classAtom, createWindowParams);
		const HWND hWnd = window->GetWindowHandle();
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Register window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		RegisterWindowProc(hWnd, window);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window proc registered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		return Core::SystemInfo::CreateDeduced<IWindow, IWindowsWindow, Input::IKeyboardProvider>(*window, *this, true);
	}

	void WindowsWindowFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<WindowsWindow*>(system) && "Tried to destroy a system of the wrong type."));
		const auto windowsWindow = static_cast<WindowsWindow*>(system);
		const HWND hWnd = windowsWindow->GetWindowHandle();

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Unregister window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
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
			PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("The window is already destroyed. No unregistering a window proc required. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Window proc unregistered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());

		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Destroy windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
		delete windowsWindow;
		PONY_LOG_GENERAL(logger, Log::LogType::Info, std::format("Windows window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd)).c_str());
	}

	WindowParams& WindowsWindowFactory::NextWindowParams() noexcept
	{
		return windowParams;
	}

	const WindowParams& WindowsWindowFactory::NextWindowParams() const noexcept
	{
		return windowParams;
	}

	WindowsWindowParams& WindowsWindowFactory::NextWindowsWindowParams() noexcept
	{
		return windowsWindowParams;
	}

	const WindowsWindowParams& WindowsWindowFactory::NextWindowsWindowParams() const noexcept
	{
		return windowsWindowParams;
	}

	const char* WindowsWindowFactory::GetSystemName() const noexcept
	{
		return WindowsWindow::StaticName;
	}

	const char* WindowsWindowFactory::GetName() const noexcept
	{
		return StaticName;
	}

	HCURSOR GetDefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageW(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (cursor == NULL)
		{
			throw std::logic_error(std::format("Couldn't load a class cursor. Error code: '{}'", GetLastError()));
		}

		return cursor;
	}
}
