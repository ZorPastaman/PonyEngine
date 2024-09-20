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

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Implementation:WindowsWindowSystemFactory;

import <cstdint>;
import <exception>;
import <format>;
import <stdexcept>;
import <string>;
import <utility>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core.Factory;

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
		/// @param application Application.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystemFactory(Core::IApplication& application, const WindowsClassParams& classParams);
		WindowsWindowSystemFactory(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory(WindowsWindowSystemFactory&&) = delete;

		~WindowsWindowSystemFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngine& engine, const Core::SystemParams& params) override;
		virtual void Destroy(Core::ISystem* system) noexcept override;

		[[nodiscard("Pure function")]]
		virtual WindowsWindowParams& WindowParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowParams& WindowParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsWindowSystemFactory& operator =(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory& operator =(WindowsWindowSystemFactory&&) = delete;

		static constexpr auto StaticName = "PonyEngine::Window::WindowsWindowSystemFactory"; ///< Class name.

	private:
		/// @brief Gets this dll instance.
		/// @return Instance.
		[[nodiscard("Pure function")]]
		static HINSTANCE GetInstance();
		/// @brief Creates Windows class.
		/// @param classParams Class parameters.
		/// @return Created class.
		[[nodiscard("Pure function")]]
		ATOM CreateClass(const WindowsClassParams& classParams) const;

		WindowsWindowParams windowParams; ///< Next window parameters.

		Core::IApplication* application; ///< Application.

		HINSTANCE hInstance; ///< This dll instance.
		ATOM classAtom; ///< Window class atom.
	};
}

namespace PonyEngine::Window
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();

	WindowsWindowSystemFactory::WindowsWindowSystemFactory(Core::IApplication& application, const WindowsClassParams& classParams) :
		application{&application},
		hInstance{GetInstance()},
		classAtom{CreateClass(classParams)}
	{
	}

	WindowsWindowSystemFactory::~WindowsWindowSystemFactory() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Unregister window class '0x{:X}'.", classAtom);
		if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classAtom), hInstance))
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Error, "Couldn't unregister class. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window class unregistered.");
	}

	Core::SystemData WindowsWindowSystemFactory::Create(Core::IEngine& engine, const Core::SystemParams&)
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window.");
		const auto system = new WindowsWindowSystem(engine, hInstance, classAtom, windowParams);
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Windows window created.");
		const HWND hWnd = system->WindowHandle();
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Register window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		RegisterWindowProc(hWnd, system);
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window proc registered.");
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
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Unregister window proc. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
			UnregisterWindowProc(hWnd);
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window proc unregistered.");
		}
		else
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Skip unregistering window proc 'cause window has already been destroyed. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		}

		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Destroy Windows window. Window handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(hWnd));
		delete windowsWindow;
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Windows window destroyed.");
	}

	WindowsWindowParams& WindowsWindowSystemFactory::WindowParams() noexcept
	{
		return windowParams;
	}

	const WindowsWindowParams& WindowsWindowSystemFactory::WindowParams() const noexcept
	{
		return windowParams;
	}

	const char* WindowsWindowSystemFactory::SystemName() const noexcept
	{
		return WindowsWindowSystem::StaticName;
	}

	const char* WindowsWindowSystemFactory::Name() const noexcept
	{
		return StaticName;
	}

	HINSTANCE WindowsWindowSystemFactory::GetInstance()
	{
		HINSTANCE hInstance = nullptr;
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&DefaultCursor), &hInstance) || !hInstance)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to find dll module to create window. Error code: '0x{:X}'.", GetLastError()));
		}

		return hInstance;
	}

	ATOM WindowsWindowSystemFactory::CreateClass(const WindowsClassParams& classParams) const
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
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = classParams.name.c_str(),
			.hIconSm = classParams.smallIcon
		};

		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Register window class '{}'. HInstance: '0x{:X}'; Style: '0x{:X}'; Icon: '0x{:X}'; Cursor: '0x{:X}'; Small icon: '0x{:X}'.",
			PonyBase::Utility::ConvertToString(wc.lpszClassName), reinterpret_cast<std::uintptr_t>(wc.hInstance), wc.style, reinterpret_cast<std::uintptr_t>(wc.hIcon), 
			reinterpret_cast<std::uintptr_t>(wc.hCursor), reinterpret_cast<std::uintptr_t>(wc.hIconSm));
		const ATOM atom = RegisterClassExW(&wc);
		if (!atom)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register class. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Window class '0x{:X}' registered.", atom);

		return atom;
	}

	HCURSOR DefaultCursor()
	{
		const auto cursor = static_cast<HCURSOR>(LoadImageW(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
		if (!cursor)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to load default cursor. Error code: '0x{:X}'.", GetLastError()));
		}

		return cursor;
	}
}
