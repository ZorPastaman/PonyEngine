/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LogMacro.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import <array>;
import <format>;
import <iostream>;

import PonyEngine.Log;

import Launcher;
import Launcher.Windows;

int APIENTRY wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPWSTR lpCmdLine, const int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create a logger provider");
	const Launcher::LoggerProvider loggerProvider;
	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger provider created");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Create Windows system factories provider.");
	const Launcher::SystemFactoriesProvider windowsEngineParamsProvider(loggerProvider.GetLogger());
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Windows system factories provider created.");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Create engine loop.");
	Launcher::EngineLoop engineLoop(loggerProvider.GetLogger(), windowsEngineParamsProvider);
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Engine loop created.");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Create Windows loop.");
	Launcher::WindowsLoop windowsLoop(loggerProvider.GetLogger());
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Windows loop created.");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Create main loop.");
	auto loop = Launcher::Loop(std::array<Launcher::ILoopElement*, 2>{static_cast<Launcher::ILoopElement*>(&engineLoop), static_cast<Launcher::ILoopElement*>(&windowsLoop)});
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Main loop created.");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, "Run main loop.");
	int exitCode = loop.Run();
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), PonyEngine::Log::LogType::Info, std::format("Main loop ran with the exit code '{}'.", exitCode).c_str());

	return exitCode;
}
