/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Logger.h"

namespace Mocks
{
	void Logger::Log(PonyDebug::Log::LogType, const PonyDebug::Log::LogInput&) const noexcept
	{
	}

	void Logger::LogException(const std::exception&, const PonyDebug::Log::LogInput&) const noexcept
	{
	}
}
