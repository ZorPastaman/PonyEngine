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
import <format>;
import <iostream>;

import PonyEngine.Log;

import Application.Windows;

constexpr int InternalExceptionCode = -1;
constexpr int ExternalExceptionCode = -2;

int APIENTRY wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPWSTR lpCmdLine, const int nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	try
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Create logger provider");
		const auto loggerProvider = Application::WindowsLoggerProvider();
		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Logger provider created");

		try
		{
			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows system factories provider.");
			const auto windowsSystemFactoriesProvider = Application::WindowsSystemFactoriesProvider(loggerProvider.Logger());
			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows system factories provider created.");

			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create engine loop.");
			auto engineLoop = Application::EngineLoop(loggerProvider.Logger(), windowsSystemFactoriesProvider);
			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Engine loop created.");

			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Create Windows loop.");
			auto windowsLoop = Application::WindowsEndLoop(loggerProvider.Logger());
			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Windows loop created.");

			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Run main loop.");
			const int exitCode = Application::RunLoop({&engineLoop, &windowsLoop});
			PONY_LOG_GENERAL(&loggerProvider.Logger(), PonyEngine::Log::LogType::Info, "Main loop ran with the exit code '{}'.", exitCode);

			return exitCode;
		}
		catch (const std::exception& e)
		{
			PONY_LOG_E_GENERAL(&loggerProvider.Logger(), e, "On internal main.");
			return InternalExceptionCode;
		}
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On external main.");
		return ExternalExceptionCode;
	}
}
