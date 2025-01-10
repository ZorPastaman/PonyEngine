/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Application.Windows:Application;

import PonyEngine.Core;

import :Logger;
import :Engine;
import :QuitChecker;

export namespace Application::Windows
{
	/// @brief Application for Windows.
	class Application final : private PonyEngine::Core::IApplicationContext
	{
	public:
		/// @brief Creates a @p Application.
		[[nodiscard("Pure constructor")]]
		Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;

		~Application() noexcept = default;

		/// @brief Runs the engine.
		/// @return Exit code.
		int Run();

		Application& operator =(const Application&) = delete;
		Application& operator =(Application&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual PonyDebug::Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyDebug::Log::ILogger& Logger() const noexcept override;

		class Logger logger; ///< Logger for Windows.
		Engine engine; ///< Engine for Windows.
		QuitChecker quitChecker; /// Quit checker for Windows.
	};
}

namespace Application::Windows
{
	Application::Application() :
		engine(*this),
		quitChecker(*this)
	{
	}

	int Application::Run()
	{
		int exitCode = 0;
		bool isRunning;

		do
		{
			isRunning = engine.Tick(exitCode) && quitChecker.Check(exitCode);
		} while (isRunning);

		return exitCode;
	}

	PonyDebug::Log::ILogger& Application::Logger() noexcept
	{
		return logger.AppLogger();
	}

	const PonyDebug::Log::ILogger& Application::Logger() const noexcept
	{
		return logger.AppLogger();
	}
}
