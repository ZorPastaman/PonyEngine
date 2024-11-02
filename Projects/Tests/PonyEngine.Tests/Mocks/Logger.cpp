/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Logger.h"

namespace Core
{
	void Logger::Log(PonyDebug::Log::LogType logType, const PonyDebug::Log::LogInput& logInput) noexcept
	{
	}

	void Logger::LogException(const std::exception& exception, const PonyDebug::Log::LogInput& logInput) noexcept
	{
	}

	void Logger::AddSubLogger(PonyDebug::Log::ISubLogger& subLogger)
	{
	}

	void Logger::RemoveSubLogger(PonyDebug::Log::ISubLogger& subLogger)
	{
	}

	std::string_view Logger::Name() const noexcept
	{
		return "TestLogger";
	}
}
