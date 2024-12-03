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

import :Utility;
import :WindowProc;

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
		Core::IApplicationContext* application; ///< Application.
		HINSTANCE hInstance; ///< Module instance.
		ATOM classAtom; /// Registered class.
	};
}

namespace PonyEngine::Window
{
	WindowsClassImpl::WindowsClassImpl(Core::IApplicationContext& application, const WindowsClassParams& params) :
		application{&application}
	{
		if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&DefaultCursor), &hInstance) || !hInstance)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to find dll module to create window. Error code: '0x{:X}'.", GetLastError()));
		}

		const auto wc = WNDCLASSEXW
		{
			.cbSize = sizeof(WNDCLASSEXW),
			.style = params.style,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = hInstance,
			.hIcon = params.icon,
			.hCursor = params.cursor ? params.cursor : DefaultCursor(),
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = params.name.c_str(),
			.hIconSm = params.smallIcon
		};

		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Register window class '{}'. HInstance: '0x{:X}'; Style: '0x{:X}'; Icon: '0x{:X}'; Cursor: '0x{:X}'; Small icon: '0x{:X}'.",
			PonyBase::Utility::ConvertToString(wc.lpszClassName), reinterpret_cast<std::uintptr_t>(wc.hInstance), wc.style, reinterpret_cast<std::uintptr_t>(wc.hIcon),
			reinterpret_cast<std::uintptr_t>(wc.hCursor), reinterpret_cast<std::uintptr_t>(wc.hIconSm));
		classAtom = RegisterClassExW(&wc);
		if (!classAtom)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register class. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Window class '0x{:X}' registered.", classAtom);
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
}
