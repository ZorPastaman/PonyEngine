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

export module PonyEngine.Window.Windows.Implementation:WindowsWindowSystemFactory;

import <cstdint>;
import <exception>;
import <format>;
import <stdexcept>;
import <string>;
import <utility>;

import PonyEngine.Core.Factory;
import PonyEngine.Log;
import PonyEngine.StringUtility;
import PonyEngine.Window.Windows.Factory;

import :IWindowProc;
import :WindowProcFunction;
import :WindowsWindowSystem;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowSystemFactory final : public Core::ISystemFactory, public IWindowsWindowSystemFactory, public Core::ISystemDestroyer
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param loggerToUse Logger.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystemFactory(Log::ILogger& loggerToUse, const WindowsClassParams& classParams);
		WindowsWindowSystemFactory(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory(WindowsWindowSystemFactory&&) = delete;

		~WindowsWindowSystemFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowParams NextWindowParams() const noexcept override;
		virtual void NextWindowParams(const WindowParams& params) noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams NextWindowsWindowParams() const noexcept override;
		virtual void NextWindowsWindowParams(const WindowsWindowParams& params) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsWindowSystemFactory& operator =(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory& operator =(WindowsWindowSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindowSystemFactory"; ///< Class name.

	private:
		Log::ILogger* const logger; ///< Logger.

		const HINSTANCE hInstance; ///< This dll instance.
		const ATOM classAtom; ///< Window class atom.

		WindowsWindowParams windowParams; ///< Next window parameters.
	};
}

namespace PonyEngine::Window
{
	/// @brief Gets HInstance.
	/// @return HInstance.
	[[nodiscard("Pure function")]]
	HINSTANCE GetHInstance();

	[[nodiscard("Pure function")]]
	ATOM RegisterWindowClass(Log::ILogger& logger, HINSTANCE hInstance, const WindowsClassParams& classParams);

	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();

	WindowsWindowSystemFactory::WindowsWindowSystemFactory(Log::ILogger& loggerToUse, const WindowsClassParams& classParams) :
		logger{&loggerToUse},
		hInstance{GetHInstance()},
		classAtom{RegisterWindowClass(loggerToUse, hInstance, classParams)}
	{
	}

	WindowsWindowSystemFactory::~WindowsWindowSystemFactory() noexcept
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Unregister window class '{}'.", classAtom);
		if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classAtom), hInstance))
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Error, "Couldn't unregister class. Error code: '{}'.", GetLastError());
		}
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window class unregistered.");
	}

	Core::SystemData WindowsWindowSystemFactory::Create(const Core::SystemParams& params)
	{
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Create Windows window.");
		const auto system = new WindowsWindowSystem(params.engine, hInstance, classAtom, windowParams);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Windows window created.");
		const HWND hWnd = system->WindowHandle();
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Register window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		RegisterWindowProc(hWnd, system);
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window proc registered.");
		const auto deleter = Core::SystemDeleter(*this);
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IWindowSystem, IWindowsWindowSystem, Input::IKeyboardProvider>(*system);

		return Core::SystemData
		{
			.system = Core::SystemUniquePtr(system, deleter),
			.tickableSystem = system,
			.publicInterfaces = std::move(interfaces)
		};
	}

	void WindowsWindowSystemFactory::Destroy(Core::ISystem* const system) noexcept
	{
		assert((dynamic_cast<WindowsWindowSystem*>(system) && "Tried to destroy a system of the wrong type."));
		const auto windowsWindow = static_cast<WindowsWindowSystem*>(system);
		const HWND hWnd = windowsWindow->WindowHandle();

		if (windowsWindow->IsWindowAlive())
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Unregister window proc. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			UnregisterWindowProc(hWnd);
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Window proc unregistered.");
		}
		else
		{
			PONY_LOG_GENERAL(logger, Log::LogType::Info, "Skip unregistering window proc 'cause window has already been destroyed. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		}

		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Destroy Windows window. Window handle: '{}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		delete windowsWindow;
		PONY_LOG_GENERAL(logger, Log::LogType::Info, "Windows window destroyed.");
	}

	WindowParams WindowsWindowSystemFactory::NextWindowParams() const noexcept
	{
		return static_cast<WindowParams>(windowParams);
	}

	void WindowsWindowSystemFactory::NextWindowParams(const WindowParams& params) noexcept
	{
		windowParams.title = params.title;
		windowParams.position = params.position;
		windowParams.size = params.size;
	}

	WindowsWindowParams WindowsWindowSystemFactory::NextWindowsWindowParams() const noexcept
	{
		return windowParams;
	}

	void WindowsWindowSystemFactory::NextWindowsWindowParams(const WindowsWindowParams& params) noexcept
	{
		windowParams = params;
	}

	const char* WindowsWindowSystemFactory::SystemName() const noexcept
	{
		return WindowsWindowSystem::StaticName;
	}

	const char* WindowsWindowSystemFactory::Name() const noexcept
	{
		return StaticName;
	}

	HINSTANCE GetHInstance()
	{
		HINSTANCE hInstance;
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&DefaultCursor), &hInstance) || !hInstance)
		{
			throw std::logic_error(std::format("Couldn't find dll module to create window. Error code: '{}'.", GetLastError()));
		}

		return hInstance;
	}

	ATOM RegisterWindowClass(Log::ILogger& logger, const HINSTANCE hInstance, const WindowsClassParams& classParams)
	{
		const auto wc = WNDCLASSEXW
		{
			.cbSize = sizeof(WNDCLASSEXW),
			.style = classParams.style,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = hInstance,
			.hIcon = classParams.icon,
			.hCursor = classParams.cursor ? classParams.cursor : DefaultCursor(),
			.hbrBackground = NULL,
			.lpszMenuName = NULL,
			.lpszClassName = classParams.name.c_str(),
			.hIconSm = NULL
		};

		PONY_LOG_GENERAL(&logger, Log::LogType::Info, "Register window class '{}'. HInstance: '{}'; Style: '{}'; Icon: '{}'; Cursor: '{}'.", Utility::ConvertToString(wc.lpszClassName), reinterpret_cast<std::uintptr_t>(wc.hInstance), wc.style, reinterpret_cast<std::uintptr_t>(wc.hIcon), reinterpret_cast<std::uintptr_t>(wc.hCursor));
		const ATOM classAtom = RegisterClassExW(&wc);
		if (!classAtom)
		{
			throw std::logic_error(Utility::SafeFormat("Couldn't register class. Error code: '{}'.", GetLastError()));
		}
		PONY_LOG_GENERAL(&logger, Log::LogType::Info, "Window class '{}' registered.", classAtom);

		return classAtom;
	}

	HCURSOR DefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageW(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::logic_error(Utility::SafeFormat("Couldn't load default cursor. Error code: '{}'.", GetLastError()));
		}

		return cursor;
	}
}
