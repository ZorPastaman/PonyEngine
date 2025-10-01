/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import std;

import PonyEngine.Application.Main.Windows;
import PonyEngine.Log;
import PonyEngine.Utility;

PonyEngine::Application::Windows::MainDataServiceModule MainDataModule; ///< Main data service module.
PonyEngine::Application::Windows::MessageLoopServiceModule MessageLoopModule; ///< Message loop module.

/// @brief Gets the main data module.
/// @return Main data module.
[[nodiscard("Pure function")]]
PonyEngine::Application::IModule* GetMainDataModule();
/// @brief Gets the message loop module.
/// @return Message loop module.
[[nodiscard("Pure function")]]
PonyEngine::Application::IModule* GetMessageLoopModule();

PONY_MODULE(GetMainDataModule, PonyEngineMainDataService, PONY_ENGINE_MAIN_DATA_ORDER);
PONY_MODULE(GetMessageLoopModule, PonyEngineMessageLoopService, PONY_ENGINE_MESSAGE_LOOP_ORDER);

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;

	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		PonyEngine::Application::Windows::MainDataServiceModule::Setup(hInstance, hPrevInstance, lpCmdLine, nShowCmd);

		try
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application...");
			auto app = std::make_unique<PonyEngine::Application::App>();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application done.");

			try
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Running application...");
				exitCode = app->Run();
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Running application done. Exit code: '{}'.", exitCode);
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

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application...");
			app.reset();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application done.");
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

PonyEngine::Application::IModule* GetMainDataModule()
{
	return &MainDataModule;
}

PonyEngine::Application::IModule* GetMessageLoopModule()
{
	return &MessageLoopModule;
}
