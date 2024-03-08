/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Core.Implementation:EngineFeatures;

import <cassert>;
import <exception>;
import <iostream>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Implementation;
import PonyEngine.Window.Factories;

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
		PONY_COUT("Create logger.");
		answer.logger = Debug::Log::CreateLogger(engine);
		PONY_COUT("Logger created.");

		if (params.addConsoleSubLogger)
		{
			try
			{
				PONY_COUT("Create a console sub-logger.");
				Debug::Log::IEngineSubLogger* const consoleSubLogger = Debug::Log::CreateConsoleSubLogger();
				answer.subLoggers.push_back(consoleSubLogger);
				answer.logger->AddSubLogger(consoleSubLogger);
				PONY_COUT("Console sub-logger created.");
			}
			catch (const std::exception& e)
			{
				PONY_CEXC(e, "On create a console sub-logger.");
			}
		}

		if (params.addLogFileSubLogger)
		{
			try
			{
				PONY_COUT("Create a file sub-logger.");
				Debug::Log::IEngineSubLogger* const fileSubLogger = Debug::Log::CreateFileSubLogger(params.logFilePath);
				answer.subLoggers.push_back(fileSubLogger);
				answer.logger->AddSubLogger(fileSubLogger);
				PONY_COUT("File sub-logger created.");
			}
			catch (const std::exception& e)
			{
				PONY_CEXC(e, "On create a log file sub-logger.");
			}
		}

		PONY_COUT("Add custom sub-loggers.");
		for (Debug::Log::ISubLogger* const subLogger : params.subLoggers)
		{
			assert((subLogger != nullptr));

			try
			{
				answer.logger->AddSubLogger(subLogger);
			}
			catch (const std::exception& e)
			{
				PONY_CEXC(e, "On adding a sub-logger.");
			}
		}
		PONY_COUT("Custom sub-loggers added.");

		return answer;
	}

	Window::IEngineWindow* CreateWindow(const WindowParams& params, IEngine& engine)
	{
		if (params.createWindow)
		{
			PONY_LOG(engine.GetLogger(), Debug::Log::LogType::Info, "Create an engine window");
			Window::IEngineWindow* const window = Window::CreateEngineWindow(params.title, engine);
			PONY_LOG(engine.GetLogger(), Debug::Log::LogType::Info, "Engine window created");
			return window;
		}

		PONY_LOG(engine.GetLogger(), Debug::Log::LogType::Info, "Skip creating a window");

		return nullptr;
	}
}
