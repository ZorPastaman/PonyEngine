/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Macro/Text.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:Process;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Log;

import :ThreadControl;

export namespace PonyEngine::Application
{
	/// @brief Sets this process default priority.
	/// @param application Application.
	void SetProcessPriority(const App& application) noexcept;
	/// @brief Sets a thread default main priority.
	/// @param application Application.
	/// @param threadControl Thread control.
	void SetMainThreadRole(const App& application, ThreadControl& threadControl) noexcept;

	/// @brief Logs basic info.
	/// @param application Application
	void LogProcessBasicInfo(const App& application) noexcept;
}

namespace PonyEngine::Application
{
	void SetProcessPriority(const App& application) noexcept
	{
		PONY_LOG(application.LogService(), Log::LogType::Info, "Setting process priority. Priority: '{}'.", PONY_ENGINE_APPLICATION_PROCESS_PRIORITY);
		if (!SetPriorityClass(GetCurrentProcess(), PONY_ENGINE_APPLICATION_PROCESS_PRIORITY)) [[unlikely]]
		{
			PONY_LOG(application.LogService(), Log::LogType::Error, std::current_exception(), "Failed to set process priority. ErrorCode: '0x{:X}'.", GetLastError());
		}
	}

	void SetMainThreadRole(const App& application, ThreadControl& threadControl) noexcept
	{
#ifdef PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE
		try
		{
			threadControl.Role(PONY_STRINGIFY_VALUE(PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE));
		}
		catch (...)
		{
			PONY_LOG(application.LogService(), Log::LogType::Error, std::current_exception(), "Failed to set main thread role.");
		}
#endif
	}

	void LogProcessBasicInfo(const App& application) noexcept
	{
		PONY_LOG(application.LogService(), Log::LogType::Info, "PID: '{}'.", GetCurrentProcessId());
	}
}
