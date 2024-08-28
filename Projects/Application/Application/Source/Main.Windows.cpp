/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import <exception>;

import PonyEngine.Common;
import PonyEngine.Log;

import Application.Windows;

int APIENTRY wWinMain(const HINSTANCE, const HINSTANCE, const LPWSTR, const int)
{
	try
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger provider");
		const auto loggerProvider = Application::WindowsLoggerProvider();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger provider created");

		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows system factories provider.");
		const auto windowsSystemFactoriesProvider = Application::WindowsEngineConfigProvider(loggerProvider.Logger());
		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows system factories provider created.");

		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create engine loop.");
		auto engineLoop = Application::EngineLoop(loggerProvider.Logger(), windowsSystemFactoriesProvider);
		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Engine loop created.");

		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows loop.");
		auto windowsLoop = Application::WindowsEndLoop(loggerProvider.Logger());
		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows loop created.");

		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Run main loop.");
		const int exitCode = Application::RunLoop({&engineLoop, &windowsLoop});
		PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Main loop finished with exit code '{}'.", exitCode);

		return exitCode;
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main().");
		return static_cast<int>(PonyEngine::Common::ExitCodes::ApplicationException);
	}
}
