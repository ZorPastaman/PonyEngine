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
	void Logger::Log(PonyDebug::Log::LogType, const PonyDebug::Log::LogInput&) noexcept
	{
	}

	void Logger::LogException(const std::exception&, const PonyDebug::Log::LogInput&) noexcept
	{
	}

	void Logger::AddSubLogger(PonyDebug::Log::ISubLogger&)
	{
	}

	void Logger::RemoveSubLogger(PonyDebug::Log::ISubLogger&)
	{
	}

	std::string_view Logger::Name() const noexcept
	{
		return "TestLogger";
	}
}
