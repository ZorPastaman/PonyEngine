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

export module PonyEngine.Window.Windows.Detail:ClassImpl;

import <cstdint>;
import <stdexcept>;

import PonyBase.Utility.Windows;

import PonyDebug.Log;

import PonyEngine.Core;
import PonyEngine.Window.Windows;

import :Utility;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows class wrapper.
	class ClassImpl final : public Class
	{
	public:
		/// @brief Creates a Windows class.
		/// @param application Application context.
		/// @param params Windows class parameters.
		[[nodiscard("Pure constructor")]]
		ClassImpl(Core::IApplicationContext& application, const ClassParams& params);
		ClassImpl(const ClassImpl&) = delete;
		ClassImpl(ClassImpl&&) = delete;

		virtual ~ClassImpl() noexcept override;

		[[nodiscard("Pure function")]]
		virtual HMODULE ModuleHandle() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual ATOM ClassHandle() const noexcept override;

		ClassImpl& operator =(const ClassImpl&) = delete;
		ClassImpl& operator =(ClassImpl&&) = delete;

	private:
		Core::IApplicationContext* application; ///< Application.
		HMODULE moduleHandle; ///< Module instance handle.
		ATOM classHandle; /// Registered class handle.
	};
}

namespace PonyEngine::Window::Windows
{
	ClassImpl::ClassImpl(Core::IApplicationContext& application, const ClassParams& params) :
		application{&application},
		moduleHandle{PonyBase::Utility::Windows::GetModule()}
	{
		const auto wc = WNDCLASSEXW
		{
			.cbSize = sizeof(WNDCLASSEXW),
			.style = params.style,
			.lpfnWndProc = &WindowProc,
			.cbClsExtra = 0,
			.cbWndExtra = 0,
			.hInstance = moduleHandle,
			.hIcon = params.icon,
			.hCursor = params.cursor ? params.cursor : PonyBase::Utility::Windows::DefaultCursor(),
			.hbrBackground = nullptr,
			.lpszMenuName = nullptr,
			.lpszClassName = params.name.c_str(),
			.hIconSm = params.smallIcon
		};

		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Register window class '{}'. HInstance: '0x{:X}'; Style: '0x{:X}'; Icon: '0x{:X}'; Cursor: '0x{:X}'; Small icon: '0x{:X}'.",
			PonyBase::Utility::ConvertToString(wc.lpszClassName), reinterpret_cast<std::uintptr_t>(wc.hInstance), wc.style, reinterpret_cast<std::uintptr_t>(wc.hIcon),
			reinterpret_cast<std::uintptr_t>(wc.hCursor), reinterpret_cast<std::uintptr_t>(wc.hIconSm));
		classHandle = RegisterClassExW(&wc);
		if (!classHandle)
		{
			throw std::runtime_error(PonyBase::Utility::SafeFormat("Failed to register class. Error code: '0x{:X}'.", GetLastError()));
		}
		PONY_LOG(this->application->Logger(), PonyDebug::Log::LogType::Info, "Window class '0x{:X}' registered.", classHandle);
	}

	ClassImpl::~ClassImpl() noexcept
	{
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Unregister window class '0x{:X}'.", classHandle);
		if (!UnregisterClassW(reinterpret_cast<LPCWSTR>(classHandle), moduleHandle))
		{
			PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Error, "Failed to unregister class. Error code: '0x{:X}'.", GetLastError());
		}
		PONY_LOG(application->Logger(), PonyDebug::Log::LogType::Info, "Window class unregistered.");
	}

	HINSTANCE ClassImpl::ModuleHandle() const noexcept
	{
		return moduleHandle;
	}

	ATOM ClassImpl::ClassHandle() const noexcept
	{
		return classHandle;
	}
}
