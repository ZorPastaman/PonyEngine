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

import <format>;
import <iostream>;

import PonyEngine.Log;

import Launcher.Windows;

int APIENTRY wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPWSTR lpCmdLine, const int nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger provider");
	const auto loggerProvider = Launcher::WindowsLoggerProvider();
	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger provider created");

	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows system factories provider.");
	const auto windowsSystemFactoriesProvider = Launcher::WindowsSystemFactoriesProvider(loggerProvider.Logger());
	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows system factories provider created.");

	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create engine loop.");
	auto engineLoop = Launcher::EngineLoop(loggerProvider.Logger(), windowsSystemFactoriesProvider);
	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Engine loop created.");

	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows loop.");
	auto windowsLoop = Launcher::WindowsEndLoop(loggerProvider.Logger());
	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows loop created.");

	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Run main loop.");
	const int exitCode = Launcher::RunLoop({&engineLoop, &windowsLoop});
	PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Main loop ran with the exit code '{}'.", exitCode);

	return exitCode;
}
