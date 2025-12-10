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

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Log;

/// @brief Executes the main.
/// @param hInstance Instance.
/// @param hPrevInstance Previous instance.
/// @param lpCmdLine Command line.
/// @param nShowCmd Show command.
/// @return Exit code and error message. The latter is empty if the former is Success.
std::pair<int, std::string> Execute(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd) noexcept;

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	try
	{
		const auto [exitCode, exceptionInfo] = Execute(hInstance, hPrevInstance, lpCmdLine, nShowCmd);

		if (exitCode != PonyEngine::Application::ExitCodes::Success) [[unlikely]]
		{
			const std::string text = exceptionInfo.empty()
				? std::format("Error code: '{}'.", exitCode)
				: std::format("Error code: '{}'.\n{}", exitCode, exceptionInfo);
			MessageBoxA(nullptr, text.c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
		}

		return exitCode;
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Unexpected exception", "PonyEngine exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
		return PonyEngine::Application::ExitCodes::UnexpectedException;
	}
}

std::pair<int, std::string> Execute(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd) noexcept
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;

	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
	}
	catch (const std::exception& e)
	{
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, std::format("Exception on setting process priority: {}", e.what()));
	}

#if PONY_ENGINE_CREATE_CONSOLE
	try
	{
		PonyEngine::Application::Windows::CreateConsole();
	}
	catch (const std::exception& e)
	{
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, std::format("Exception on creating console: {}", e.what()));
	}
#endif

	std::shared_ptr<PonyEngine::Application::DefaultLogger> logger;
	try
	{
		logger = std::make_shared<PonyEngine::Application::Windows::DefaultLogger>();
	}
	catch (const std::exception& e)
	{
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, std::format("Exception on creating default logger: {}", e.what()));
	}
	catch (...)
	{
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, "Unknown exception on creating default logger.");
	}

	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Constructing application...");
	std::unique_ptr<PonyEngine::Application::Windows::App> application;
	try
	{
		application = std::make_unique<PonyEngine::Application::Windows::App>(hInstance, hPrevInstance, lpCmdLine, nShowCmd, logger);
	}
	catch (const std::exception& e)
	{
		PONY_LOG_X(*logger, std::current_exception(), "On creating application.");
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, std::format("Exception on creating application: {}", e.what()));
	}
	catch (...)
	{
		PONY_LOG_X(*logger, std::current_exception(), "On creating application.");
		return std::pair(PonyEngine::Application::ExitCodes::InitializationException, "Unknown exception on creating application.");
	}
	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Constructing application done.");

	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Running application...");
	try
	{
		exitCode = application->Run();
	}
	catch (const std::exception& e)
	{
		PONY_LOG_X(*logger, std::current_exception(), "On application running.");
		return std::pair(PonyEngine::Application::ExitCodes::RunningException, std::format("Exception on application running: {}", e.what()));
	}
	catch (...)
	{
		PONY_LOG_X(*logger, std::current_exception(), "On application running.");
		return std::pair(PonyEngine::Application::ExitCodes::RunningException, "Unknown exception on application running.");
	}
	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Running application done. Exit code: '{}'.", exitCode);

	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Destructing application...");
	application.reset();
	PONY_LOG(*logger, PonyEngine::Log::LogType::Info, "Destructing application done.");
	logger.reset();

#if PONY_ENGINE_CREATE_CONSOLE
	try
	{
		PonyEngine::Application::Windows::DestroyConsole();
	}
	catch (const std::exception& e)
	{
		return std::pair(PonyEngine::Application::ExitCodes::DeinitializationException, std::format("Exception on destroying console: {}", e.what()));
	}
#endif

	return std::pair(exitCode, std::string());
}
