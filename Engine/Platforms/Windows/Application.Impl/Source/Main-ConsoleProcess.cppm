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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:ConsoleProcess;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Log;

import :Process;

export namespace PonyEngine::Application
{
	/// @brief Console process.
	class ConsoleProcess final : public Process
	{
	public:
		/// @brief Creates a console process.
		/// @param commandLine Command line.
		[[nodiscard("Pure constructor")]]
		explicit ConsoleProcess(std::span<const std::string_view> commandLine);
		ConsoleProcess(const ConsoleProcess&) = delete;
		ConsoleProcess(ConsoleProcess&&) = delete;

		virtual ~ConsoleProcess() noexcept override = default;

		ConsoleProcess& operator =(const ConsoleProcess&) = delete;
		ConsoleProcess& operator =(ConsoleProcess&&) = delete;

	protected:
		virtual void CreateConsole() noexcept override;

		[[nodiscard("Must be used")]] 
		virtual void TickPlatform() override;
	};
}

namespace PonyEngine::Application
{
	std::atomic_bool CtrlExit = false; ///< Is CTRL+C received?
	BOOL WINAPI CtrlHandler(DWORD ctrlType);

	static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");

	ConsoleProcess::ConsoleProcess(const std::span<const std::string_view> commandLine) :
		Process(commandLine)
	{
		PONY_LOG(Application().LogService(), Log::LogType::Info, "Setting console ctrl handler.");
		if (!SetConsoleCtrlHandler(&CtrlHandler, TRUE)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to set console ctrl handler.");
		}
	}

	void ConsoleProcess::CreateConsole() noexcept
	{
		PONY_LOG(Application().LogService(), Log::LogType::Info, "Setting console cp to UTF-8.");

		if (!SetConsoleCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to set console CP. ErrorCode: '0x{:X}'.", GetLastError());
		}
		if (!SetConsoleOutputCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Error, "Failed to set output console CP. ErrorCode: '0x{:X}'.", GetLastError());
		}
	}

	void ConsoleProcess::TickPlatform()
	{
		if (CtrlExit.load(std::memory_order::relaxed)) [[unlikely]]
		{
			PONY_LOG(Application().LogService(), Log::LogType::Info, "Stop command received.");
			Application().Stop();
		}
	}

	BOOL CtrlHandler(const DWORD ctrlType)
	{
		switch (ctrlType)
		{
		case CTRL_C_EVENT:
			CtrlExit.store(true, std::memory_order::relaxed);
			return TRUE;
		default:
			return FALSE;
		}
	}
}
