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
import <string_view>;
import <utility>;

import PonyBase.Memory;
import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core.Factory;

import PonyEngine.Window.Windows.Factory;

import :IWindowProc;
import :WindowsWindowSystem;

export namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	class WindowsWindowSystemFactory final : public IWindowsWindowSystemFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param application Application context.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowSystemFactory(Core::IApplicationContext& application, const WindowsClassParams& classParams);
		WindowsWindowSystemFactory(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory(WindowsWindowSystemFactory&&) = delete;

		~WindowsWindowSystemFactory() noexcept;

		[[nodiscard("Pure function")]]
		virtual Core::SystemData Create(Core::IEngineContext& engine, const Core::EngineSystemParams& params) override;

		[[nodiscard("Pure function")]]
		virtual WindowsWindowSystemParams& SystemParams() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const WindowsWindowSystemParams& SystemParams() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view SystemName() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		WindowsWindowSystemFactory& operator =(const WindowsWindowSystemFactory&) = delete;
		WindowsWindowSystemFactory& operator =(WindowsWindowSystemFactory&&) = delete;

		static constexpr std::string_view StaticName = "PonyEngine::Window::WindowsWindowSystemFactory"; ///< Class name.

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

		WindowsWindowSystemParams windowParams; ///< Next window parameters.

		Core::IApplicationContext* application; ///< Application.

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

	WindowsWindowSystemFactory::WindowsWindowSystemFactory(Core::IApplicationContext& application, const WindowsClassParams& classParams) :
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

	Core::SystemData WindowsWindowSystemFactory::Create(Core::IEngineContext& engine, const Core::EngineSystemParams&)
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Create Windows window.");
		auto system = PonyBase::Memory::UniquePointer<WindowsWindowSystem>::Create(engine, hInstance, classAtom, windowParams);
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Windows window created.");
		auto interfaces = Core::ObjectInterfaces();
		interfaces.AddInterfacesDeduced<IWindowSystem, IWindowsWindowSystem, Input::IKeyboardProvider>(*system);

		return Core::SystemData
		{
			.system = PonyBase::Memory::UniquePointer<Core::ITickableEngineSystem>(std::move(system)),
			.publicInterfaces = std::move(interfaces)
		};
	}

	WindowsWindowSystemParams& WindowsWindowSystemFactory::SystemParams() noexcept
	{
		return windowParams;
	}

	const WindowsWindowSystemParams& WindowsWindowSystemFactory::SystemParams() const noexcept
	{
		return windowParams;
	}

	std::string_view WindowsWindowSystemFactory::SystemName() const noexcept
	{
		return WindowsWindowSystem::StaticName;
	}

	std::string_view WindowsWindowSystemFactory::Name() const noexcept
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
