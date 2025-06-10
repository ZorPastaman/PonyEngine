/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Core:Logger;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Log::Core
{
	/// @brief Logger.
	class Logger final : public ILogger
	{
	public:
		virtual void Log(LogType logType, const LogInput& logInput) const noexcept override;
		virtual void LogException(const std::exception& exception, const LogInput& logInput) const noexcept override;
	};
}

namespace PonyEngine::Log::Core
{
	void Logger::Log(LogType logType, const LogInput& logInput) const noexcept
	{
		std::cout << logInput.message << "From custom!" << "\n";
	}

	void Logger::LogException(const std::exception& exception, const LogInput& logInput) const noexcept
	{
	}
}
