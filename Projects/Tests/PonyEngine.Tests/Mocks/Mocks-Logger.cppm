/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:Logger;

import <exception>;

import PonyDebug.Log;

export namespace Mocks
{
	class Logger final : public PonyDebug::Log::ILogger
	{
	public:
		virtual void Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) const noexcept override;
		virtual void LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) const noexcept override;
	};
}

namespace Mocks
{
	void Logger::Log(PonyDebug::Log::LogType, const PonyDebug::Log::LogInput&) const noexcept
	{
	}

	void Logger::LogException(const std::exception&, const PonyDebug::Log::LogInput&) const noexcept
	{
	}
}
