/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Implementation:EngineFeatures;

import <cassert>;
import <exception>;
import <iostream>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Window.Implementation;

import :LoggerOwnerKit;

namespace PonyEngine::Core
{
	/// @brief Creates a logger and its sub-loggers.
	/// @param params Logger parameters.
	/// @param engine Engine that is an owner of the created logger.
	/// @return Struct that holds pointers to a created logger and its sub-loggers.
	export [[nodiscard("Pure function")]] 
	LoggerOwnerKit CreateLogger(const LoggerParams& params, const IEngine& engine);

	/// @brief Creates a window.
	/// @param params Window parameters.
	/// @param engine Engine that owns the window.
	/// @return Engine window.
	export [[nodiscard("Pure function")]]
	Window::IEngineWindow* CreateWindow(const WindowParams& params, IEngine& engine);

	LoggerOwnerKit CreateLogger(const LoggerParams& params, const IEngine& engine)
	{
		LoggerOwnerKit answer;
		answer.logger = Debug::Log::CreateLogger(engine);

		if (params.addConsoleSubLogger)
		{
			try
			{
				Debug::Log::IEngineSubLogger* const consoleSubLogger = Debug::Log::CreateConsoleSubLogger();
				answer.subLoggers.push_back(consoleSubLogger);
				answer.logger->AddSubLogger(consoleSubLogger);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << " on create a console sub-logger." << std::endl;
			}
		}

		if (params.addLogFileSubLogger)
		{
			try
			{
				Debug::Log::IEngineSubLogger* const fileSubLogger = Debug::Log::CreateFileSubLogger(params.logFilePath);
				answer.subLoggers.push_back(fileSubLogger);
				answer.logger->AddSubLogger(fileSubLogger);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << " on create a log file sub-logger." << std::endl;
			}
		}

		for (Debug::Log::ISubLogger* const subLogger : params.subLoggers)
		{
			assert((subLogger != nullptr));

			try
			{
				answer.logger->AddSubLogger(subLogger);
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << " on adding a sub-logger." << std::endl;
			}
		}

		return answer;
	}

	Window::IEngineWindow* CreateWindow(const WindowParams& params, IEngine& engine)
	{
		if (params.createWindow)
		{
			engine.GetLogger().Log(Debug::Log::LogType::Info, "Create a window");

			return Window::CreateEngineWindow(params.title, engine);
		}

		engine.GetLogger().Log(Debug::Log::LogType::Info, "Skip creating a window");

		return nullptr;
	}
}
