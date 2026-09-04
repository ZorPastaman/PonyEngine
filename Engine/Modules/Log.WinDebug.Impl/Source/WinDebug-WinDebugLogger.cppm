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

export module PonyEngine.Log.WinDebug.Impl:WinDebugLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::WinDebug
{
	/// @brief Logger that logs to the @p OutputDebugStringA().
	class WinDebugLogger final : public ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		WinDebugLogger() noexcept = default;
		WinDebugLogger(const WinDebugLogger&) = delete;
		WinDebugLogger(WinDebugLogger&&) = delete;

		~WinDebugLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept override;

		WinDebugLogger& operator =(const WinDebugLogger&) = delete;
		WinDebugLogger& operator =(WinDebugLogger&&) = delete;
	};
}

namespace PonyEngine::Log::WinDebug
{
	void WinDebugLogger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) noexcept
	{
		OutputDebugStringA(formattedMessage.data());
	}
}
