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

import PonyEngine.Application.Main.Windows;
import PonyEngine.Log;
import PonyEngine.Utility;

int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;

	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		try
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application...");
			auto app = std::make_unique<PonyEngine::Application::App>();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application done.");

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing loop.");
			bool shouldExit = false;
			auto loop = std::make_unique<PonyEngine::Application::Loop<2>>(
				std::function<void()>([&]()
				{
					PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Ticking application.");
					shouldExit = app->Tick(exitCode);
				}),
				std::function<void()>([&]()
				{
					PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Checking for quit message.");
					shouldExit = PonyEngine::Application::Windows::CheckForQuit(exitCode);
				})
			);

			try
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop start.");
				while (!shouldExit)
				{
					loop->Next();
				}
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop finish. Exit code: '{}'.", exitCode);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On application tick.");
				MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on application tick: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}
			catch (...)
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application tick.");
				MessageBoxA(nullptr, "Exception on application tick.", "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Releasing loop.");
			loop.reset();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Releasing application.");
			app.reset();
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On application.");
			MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on application: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application.");
			MessageBoxA(nullptr, "Exception on application.", "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}

#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}

	return exitCode;
}
