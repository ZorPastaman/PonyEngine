/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.Log.PlatformConsole.Impl.Windows:PlatformConsoleLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::PlatformConsole
{
	/// @brief Logger that logs to the @p OutputDebugStringA().
	class PlatformConsoleLogger final : public ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleLogger() noexcept = default;
		PlatformConsoleLogger(const PlatformConsoleLogger&) = delete;
		PlatformConsoleLogger(PlatformConsoleLogger&&) = delete;

		~PlatformConsoleLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept override;

		PlatformConsoleLogger& operator =(const PlatformConsoleLogger&) = delete;
		PlatformConsoleLogger& operator =(PlatformConsoleLogger&&) = delete;
	};
}

namespace PonyEngine::Log::PlatformConsole
{
	void PlatformConsoleLogger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) noexcept
	{
		OutputDebugStringA(formattedMessage.data());
	}
}
