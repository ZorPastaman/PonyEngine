/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Job:JobPriority;

import std;

export namespace PonyEngine::Job
{
	/// @brief Job priority.
	enum class JobPriority : std::uint8_t
	{
		Low,
		Normal,
		High
	};
}

namespace PonyEngine::Job
{
	/// @brief Job priority names.
	constexpr std::array<std::string_view, 3> JobPriorityNames
	{
		"Low",
		"Normal",
		"High"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Job::JobPriority, PonyEngine::Job::JobPriorityNames)
}
