/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <exception>
#include <string_view>

import PonyDebug.Log;

namespace Core
{
	class Logger final : public PonyDebug::Log::ILogger
	{
	public:
		virtual void Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept override;
		virtual void LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept override;

		virtual void AddSubLogger(PonyDebug::Log::ISubLogger& subLogger) override;
		virtual void RemoveSubLogger(PonyDebug::Log::ISubLogger& subLogger) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
	};
}
