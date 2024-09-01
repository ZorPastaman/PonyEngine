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
import PonyEngine.Log;

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

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Log::ILogger& Logger() const noexcept override;

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

	PonyEngine::Log::ILogger& WindowsApplication::Logger() const noexcept
	{
		return logger.Logger();
	}

	int WindowsApplication::Run() const
	{
		int exitCode = 0;
		bool running;

		do
		{
			running = engine.Tick(exitCode) && quitChecker.Check(exitCode);
		} while (running);

		return exitCode;
	}

	const char* WindowsApplication::Name() const noexcept
	{
		return StaticName;
	}
}
