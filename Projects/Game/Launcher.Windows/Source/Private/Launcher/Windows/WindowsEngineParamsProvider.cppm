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

#include "Debug/Log/LogMacro.h"

export module Launcher.Windows:WindowsEngineParamsProvider;

import <iostream>;

import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;
import PonyEngine.Window.Factories;
import PonyEngine.Window.Windows.Factories;
import PonyEngine.Window.Windows.Implementation;

import Launcher;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Launcher
{
	/// @brief Windows engine params provider.
	export class WindowsEngineParamsProvider final : public IPlatformEngineParamsProvider
	{
	public:
		/// @brief Creates WindowsEngineParamsProvider.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEngineParamsProvider(PonyEngine::Debug::Log::ILogger& logger);
		WindowsEngineParamsProvider(const WindowsEngineParamsProvider&) = delete;
		WindowsEngineParamsProvider(WindowsEngineParamsProvider&&) = delete;

		virtual ~WindowsEngineParamsProvider() noexcept;

		virtual void Modify(PonyEngine::Core::EngineParams& engineParams) const override;

		WindowsEngineParamsProvider& operator =(const WindowsEngineParamsProvider&) = delete;
		WindowsEngineParamsProvider& operator =(WindowsEngineParamsProvider&&) = delete;

	private:
		PonyEngine::Debug::Log::ILogger& m_logger; /// @brief Logger.

		// Set all platform-dependent factories here.
		PonyEngine::Window::IWindowsWindowFactory* m_windowsWindowFactory;
	};

	WindowsEngineParamsProvider::WindowsEngineParamsProvider(PonyEngine::Debug::Log::ILogger& logger) :
		m_logger{logger}
	{
		// Create all platform-dependent factories here.
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Create a Windows window factory.");
		PonyEngine::Window::WindowClassParams windowClassParams(L"Pony Engine Game");
		m_windowsWindowFactory = PonyEngine::Window::CreateWindowsWindowFactory(m_logger, windowClassParams);
		assert((m_windowsWindowFactory != nullptr));
		m_windowsWindowFactory->SetTitle(L"Pony Engine Game");
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Windows window factory created.");
	}

	WindowsEngineParamsProvider::~WindowsEngineParamsProvider() noexcept
	{
		// Destroy all platform-dependent factories here.
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Destroy a Windows window factory.");
		PonyEngine::Window::DestroyWindowsWindowFactory(m_windowsWindowFactory);
		PONY_LOG_GENERAL(m_logger, LogType::Info, "Windows window factory destroyed.");
	}

	void WindowsEngineParamsProvider::Modify(PonyEngine::Core::EngineParams& engineParams) const
	{
		// Set platform-dependent engine parameters here.
		PONY_LOG_GENERAL(m_logger, LogType::Debug, "Push a Windows window factory.");
		engineParams.SetWindowFactory(m_windowsWindowFactory);
	}
}