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
		virtual Core::SystemUniquePtr Create(Core::IEngine& engine) override;
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
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&GetDefaultCursor), &hInstance) || !hInstance)
		{
			throw std::logic_error(std::format("Couldn't find a dll module to create a window. Error code: '{}'.", GetLastError()));
		}

		const auto wc = WNDCLASSEXW
		{
			.cbSize = sizeof(WNDCLASSEXW),
			.style = classParams.style,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = hInstance,
			.hIcon = classParams.icon,
			.hCursor = classParams.cursor ? classParams.cursor : GetDefaultCursor(),
			.hbrBackground = NULL,
			.lpszMenuName = NULL,
			.lpszClassName = classParams.name.c_str(),
			.hIconSm = NULL
		};

		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Register window class '{}'.", Utility::ConvertToString(classParams.name));
		classAtom = RegisterClassExW(&wc);
		if (!classAtom)
		{
			throw std::logic_error(std::format("Couldn't register a class. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window class '{}' registered.", classAtom);
	}

	WindowsWindowFactory::~WindowsWindowFactory() noexcept
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Unregister window class '{}'.", classAtom);
		if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classAtom), hInstance))
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Error, "Couldn't unregister a class. Error code: '{}'.", GetLastError());
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window class '{}' unregistered.", classAtom);
	}

	Core::SystemUniquePtr WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		const auto createWindowParams = CreateWindowParams
		{
			.title = windowParams.title,
			.style = windowsWindowParams.style,
			.extendedStyle = windowsWindowParams.extendedStyle,
			.horizontalPosition = windowParams.horizontalPosition,
			.verticalPosition = windowParams.verticalPosition,
			.width = windowParams.width,
			.height = windowParams.height,
			.cmdShow = windowsWindowParams.showCmd
		};

		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Create Windows window.");
		const auto window = new WindowsWindow(engine, hInstance, classAtom, createWindowParams);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Windows window created.");
		const HWND hWnd = window->GetWindowHandle();
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Register window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		RegisterWindowProc(hWnd, window);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window proc registered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));

		return Core::SystemUniquePtr(window, Core::SystemDeleter(*this));
	}

	void WindowsWindowFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<WindowsWindow*>(system) && "Tried to destroy a system of the wrong type."));
		const auto windowsWindow = static_cast<WindowsWindow*>(system);
		const HWND hWnd = windowsWindow->GetWindowHandle();

		if (windowsWindow->IsWindowAlive())
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Unregister window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			UnregisterWindowProc(hWnd);
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window proc unregistered. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		}
		else
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Skip unregistering window proc 'cause the window has already been destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		}

		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Destroy Windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		delete windowsWindow;
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Windows window destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
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
		if (!cursor)
		{
			throw std::logic_error(std::format("Couldn't load a class cursor. Error code: '{}'", GetLastError()));
		}

		return cursor;
	}
}
