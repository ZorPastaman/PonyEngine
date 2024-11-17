/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Application.h"

namespace Core
{
	PonyDebug::Log::ILogger& Application::Logger() noexcept
	{
		return *logger;
	}

	const PonyDebug::Log::ILogger& Application::Logger() const noexcept
	{
		return *logger;
	}
}
