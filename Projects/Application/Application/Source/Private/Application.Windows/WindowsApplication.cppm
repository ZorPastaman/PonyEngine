/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

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
}
