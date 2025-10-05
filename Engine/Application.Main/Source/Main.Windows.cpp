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

 /// @brief Logs to console.
 /// @param type Log type.
 /// @param message Message.
#define PONY_APP_CONSOLE(type, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_MASK)) \
	{ \
		if constexpr (PonyEngine::Log::IsInMask(type, PONY_LOG_STACKTRACE_MASK)) \
		{ \
			const auto stacktrace = std::stacktrace::current(); \
			LogToConsole(type, PonyEngine::Log::LogFormat(type, PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__), stacktrace)); \
		} \
		else \
		{ \
			LogToConsole(type, PonyEngine::Log::LogFormat(type, PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__))); \
		} \
	} \

 /// @brief Logs to console.
 /// @param exception Exception.
 /// @param message Message.
#define PONY_APP_CONSOLE_E(exception, message, ...) \
	if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_MASK)) \
	{ \
		if constexpr (PonyEngine::Log::IsInMask(PonyEngine::Log::LogType::Exception, PONY_LOG_STACKTRACE_MASK)) \
		{ \
			const auto stacktrace = std::stacktrace::current(); \
			LogToConsole(PonyEngine::Log::LogType::Exception, PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what(), PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__), stacktrace)); \
		} \
		else \
		{ \
			LogToConsole(PonyEngine::Log::LogType::Exception, PonyEngine::Log::LogFormat(PonyEngine::Log::LogType::Exception, exception.what(), PonyEngine::Log::LogString(message __VA_OPT__(,) __VA_ARGS__))); \
		} \
	} \

import std;

import PonyEngine.Application.Main.Windows;
import PonyEngine.Log;
import PonyEngine.Text;

PonyEngine::Application::Windows::MainDataServiceModule MainDataModule; ///< Main data service module.
PonyEngine::Application::Windows::MessageLoopServiceModule MessageLoopModule; ///< Message loop module.

/// @brief Logs to console.
/// @param logType Log type.
/// @param message Message.
void LogToConsole(PonyEngine::Log::LogType logType, std::string_view message) noexcept;

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
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application...");
			auto app = std::make_unique<PonyEngine::Application::App>(
				PonyEngine::Application::Windows::ExecutableFile(), 
				PonyEngine::Application::Windows::LocalDataDirectory(),
				PonyEngine::Application::Windows::UserDataDirectory(),
				PonyEngine::Application::Windows::TempDataDirectory(),
				&LogToConsole);
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application done.");

			try
			{
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Running application...");
				exitCode = app->Run();
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Running application done. Exit code: '{}'.", exitCode);
			}
			catch (const std::exception& e)
			{
				PONY_APP_CONSOLE_E(e, "On application tick.");
				MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on application tick: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}
			catch (...)
			{
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application tick.");
				MessageBoxA(nullptr, "Exception on application tick.", "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}

			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application...");
			app.reset();
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application done.");
		}
		catch (const std::exception& e)
		{
			PONY_APP_CONSOLE_E(e, "On application.");
			MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on application: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application.");
			MessageBoxA(nullptr, "Exception on application.", "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}

#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_APP_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}

	return exitCode;
}

void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view message) noexcept
{
#if PONY_CONSOLE_LOG
	PonyEngine::Application::LogToConsole(logType, message);
#endif

#if PONY_PLATFORM_CONSOLE_LOG
	PonyEngine::Application::WinCore::LogToConsole(message);
#endif
}

PonyEngine::Application::IModule* GetMainDataModule()
{
	return &MainDataModule;
}

PonyEngine::Application::IModule* GetMessageLoopModule()
{
	return &MessageLoopModule;
}
