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

import <exception>;
import <format>;
import <iostream>;
import <stdexcept>;
import <string>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Utility;
import PonyEngine.Window;
import PonyEngine.Window.Windows;
import PonyEngine.Window.Windows.Factories;

import :WindowParams;
import :WindowProc;
import :WindowsWindow;

namespace PonyEngine::Window
{
	/// @brief Windows window factory.
	export class WindowsWindowFactory final : public IWindowsWindowFactory
	{
	public:
		/// @brief Creates a Windows window factory.
		/// @param classParams Window class parameters.
		[[nodiscard("Pure constructor")]]
		WindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams);
		WindowsWindowFactory(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory(WindowsWindowFactory&&) = delete;

		virtual ~WindowsWindowFactory() noexcept;

		[[nodiscard("Pure function")]]
		inline virtual IWindowsWindow* Create(Core::IEngine& engine) override;
		inline virtual void Destroy(IWindow* window) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual const std::wstring& GetTitle() const noexcept override;
		inline virtual void SetTitle(const std::wstring& title) noexcept override;

		[[nodiscard("Pure function")]]
		inline virtual int GetCmdShow() const noexcept override;
		inline virtual void SetCmdShow(int cmdShow) noexcept override;

		WindowsWindowFactory& operator =(const WindowsWindowFactory&) = delete;
		WindowsWindowFactory& operator =(WindowsWindowFactory&&) = delete;

	private:
		WindowParams m_windowParams; /// @brief Window parameters.

		const std::wstring m_className; /// @brief Window class name.
		HINSTANCE m_hInstance; /// @brief This dll instance.

		Debug::Log::ILogger& m_logger;
	};

	/// @brief Empty function.
	void Dummy();

	WindowsWindowFactory::WindowsWindowFactory(Debug::Log::ILogger& logger, const WindowClassParams& classParams) :
		m_className(classParams.GetWindowClassName()),
		m_logger{logger}
	{
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&Dummy), &m_hInstance);
		if (m_hInstance == nullptr)
		{
			throw std::logic_error("Couldn't find a dll module to create a window.");
		}

		WNDCLASS wc{};
		wc.lpfnWndProc = &WindowProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = m_className.c_str();

		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Register a window class '{}'.", Utility::ConvertToString(m_className)).c_str());
		RegisterClass(&wc);
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window class '{}' registered.", Utility::ConvertToString(m_className)).c_str());
	}

	WindowsWindowFactory::~WindowsWindowFactory() noexcept
	{
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Unregister a window class '{}'.", Utility::ConvertToString(m_className)).c_str());
		try
		{
			UnregisterClass(m_className.c_str(), m_hInstance);
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E_GENERAL(m_logger, e, "On unregistering a window class");
		}
		PONY_LOG_GENERAL(m_logger, Debug::Log::LogType::Info, std::format("Window class '{}' unregistered.", Utility::ConvertToString(m_className)).c_str());
	}

	inline IWindowsWindow* WindowsWindowFactory::Create(Core::IEngine& engine)
	{
		return new WindowsWindow(engine, m_hInstance, m_className, m_windowParams);
	}

	inline void WindowsWindowFactory::Destroy(IWindow* const window) noexcept
	{
		assert((dynamic_cast<WindowsWindow*>(window) != nullptr));
		delete static_cast<WindowsWindow*>(window);
	}

	inline const std::wstring& WindowsWindowFactory::GetTitle() const noexcept
	{
		return m_windowParams.title;
	}

	inline void WindowsWindowFactory::SetTitle(const std::wstring& title) noexcept
	{
		m_windowParams.title = title;
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
