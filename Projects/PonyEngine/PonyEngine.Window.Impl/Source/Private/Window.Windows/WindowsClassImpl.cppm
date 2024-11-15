/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Window.Windows.Detail:WindowsClassImpl;

import <cstdint>;
import <stdexcept>;

import PonyBase.StringUtility;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import :WindowProcFunction;

export namespace PonyEngine::Window
{
	/// @brief Windows class wrapper.
	class WindowsClassImpl final : public WindowsClass
	{
	public:
		/// @brief Creates a Windows class.
		/// @param application Application context.
		/// @param params Windows class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsClassImpl(Core::IApplicationContext& application, const WindowsClassParams& params);
		WindowsClassImpl(const WindowsClassImpl&) = delete;
		WindowsClassImpl(WindowsClassImpl&&) = delete;

		virtual ~WindowsClassImpl() noexcept override;

		[[nodiscard("Pure function")]]
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ATOM Class() const noexcept override;

		WindowsClassImpl& operator =(const WindowsClassImpl&) = delete;
		WindowsClassImpl& operator =(WindowsClassImpl&&) = delete;

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

		Core::IApplicationContext* application; ///< Application.
		HINSTANCE hInstance; ///< Module instance.
		ATOM classAtom; /// Registered class.
	};
}

namespace PonyEngine::Window
{
	/// @brief Gets a default cursor.
	/// @return Default cursor.
	[[nodiscard("Pure function")]]
	HCURSOR DefaultCursor();

	WindowsClassImpl::WindowsClassImpl(Core::IApplicationContext& application, const WindowsClassParams& params) :
		application{&application},
		hInstance{GetInstance()},
		classAtom{CreateClass(params)}
	{
	}

	WindowsClassImpl::~WindowsClassImpl() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Unregister window class '0x{:X}'.", classAtom);
		if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classAtom), hInstance))
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Error, "Couldn't unregister class. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window class unregistered.");
	}

	HINSTANCE WindowsClassImpl::Instance() const noexcept
	{
		return hInstance;
	}

	ATOM WindowsClassImpl::Class() const noexcept
	{
		return classAtom;
	}

	HINSTANCE WindowsClassImpl::GetInstance()
	{
		HINSTANCE hInstance = nullptr;
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&DefaultCursor), &hInstance) || !hInstance)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to find dll module to create window. Error code: '0x{:X}'.", GetLastError()));
		}

		return hInstance;
	}

	ATOM WindowsClassImpl::CreateClass(const WindowsClassParams& classParams) const
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

		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Register window class '{}'. HInstance: '0x{:X}'; Style: '0x{:X}'; Icon: '0x{:X}'; Cursor: '0x{:X}'; Small icon: '0x{:X}'.",
			PonyBase::Utility::ConvertToString(wc.lpszClassName), reinterpret_cast<std::uintptr_t>(wc.hInstance), wc.style, reinterpret_cast<std::uintptr_t>(wc.hIcon),
			reinterpret_cast<std::uintptr_t>(wc.hCursor), reinterpret_cast<std::uintptr_t>(wc.hIconSm));
		const ATOM atom = RegisterClassExW(&wc);
		if (!atom)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register class. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window class '0x{:X}' registered.", atom);

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
