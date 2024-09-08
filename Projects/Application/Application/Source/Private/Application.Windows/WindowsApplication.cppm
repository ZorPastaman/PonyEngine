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

export module Application.Windows:WindowsApplication;

import PonyDebug.Log;

import PonyEngine.Core.Factory;

import :WindowsLogger;
import :WindowsEngine;
import :WindowsQuitChecker;

export namespace Application
{
	/// @brief Application for Windows.
	class WindowsApplication final : PonyEngine::Core::IApplication
	{
	public:
		/// @brief Creates a @p WindowsApplication.
		[[nodiscard("Pure constructor")]]
		WindowsApplication();
		WindowsApplication(const WindowsApplication&) = delete;
		WindowsApplication(WindowsApplication&&) = delete;

		~WindowsApplication() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() const noexcept override;

		/// @brief Runs the engine.
		/// @return Exit code.
		int Run() const;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		WindowsApplication& operator =(const WindowsApplication&) = delete;
		WindowsApplication& operator =(WindowsApplication&&) = delete;

		static constexpr auto StaticName = "Application::WindowsApplication"; ///< Class name.

	private:
		/// @brief Sets the process priority.
		/// @param priority Priority to set.
		void SetProcessPriority(DWORD priority) const noexcept;

		WindowsLogger logger; ///< Logger for Windows.
		WindowsEngine engine; ///< Engine for Windows.
		WindowsQuitChecker quitChecker; /// Quit checker for Windows.
	};
}

namespace Application
{
	WindowsApplication::WindowsApplication() :
		engine(*this),
		quitChecker(*this)
	{
		SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
	}

	PonyDebug::Log::ILogger& WindowsApplication::Logger() const noexcept
	{
		return logger.Logger();
	}

	int WindowsApplication::Run() const
	{
		int exitCode = 0;
		bool isRunning;

		do
		{
			isRunning = engine.Tick(exitCode) && quitChecker.Check(exitCode);
		} while (isRunning);

		return exitCode;
	}

	const char* WindowsApplication::Name() const noexcept
	{
		return StaticName;
	}

	void WindowsApplication::SetProcessPriority(const DWORD priority) const noexcept
	{
		if (!SetPriorityClass(GetCurrentProcess(), priority))
		{
			PONY_LOG(logger.Logger(), PonyDebug::Log::LogType::Error, "Couldn't set current process priority to '0x{:X}'. Error code: '0x{:X}'.", priority, GetLastError());
		}

		PONY_LOG(logger.Logger(), PonyDebug::Log::LogType::Info, "Current process priority set to '0x{:X}'.", priority);
	}
}
