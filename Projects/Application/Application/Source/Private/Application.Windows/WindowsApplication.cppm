/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Application.Windows:WindowsApplication;

import PonyEngine.Core;

import :WindowsLogger;
import :WindowsEngine;
import :WindowsQuitChecker;

export namespace Application
{
	/// @brief Application for Windows.
	class WindowsApplication final : private PonyEngine::Core::IApplicationContext
	{
	public:
		/// @brief Creates a @p WindowsApplication.
		[[nodiscard("Pure constructor")]]
		WindowsApplication();
		WindowsApplication(const WindowsApplication&) = delete;
		WindowsApplication(WindowsApplication&&) = delete;

		~WindowsApplication() noexcept = default;

		/// @brief Runs the engine.
		/// @return Exit code.
		int Run();

		WindowsApplication& operator =(const WindowsApplication&) = delete;
		WindowsApplication& operator =(WindowsApplication&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

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

	int WindowsApplication::Run()
	{
		int exitCode = 0;
		bool isRunning;

		do
		{
			isRunning = engine.Tick(exitCode) && quitChecker.Check(exitCode);
		} while (isRunning);

		return exitCode;
	}

	PonyDebug::Log::ILogger& WindowsApplication::Logger() noexcept
	{
		return logger.Logger();
	}

	const PonyDebug::Log::ILogger& WindowsApplication::Logger() const noexcept
	{
		return logger.Logger();
	}
}
