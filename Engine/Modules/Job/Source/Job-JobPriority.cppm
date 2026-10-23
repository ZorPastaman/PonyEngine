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
		Low, ///< Low priority is recommended to use if it's ok if the job takes several frames to finish.
		Normal, ///< Normal priority is recommended to use when you're going to wait for the job to finish within a frame.
		High ///< High priority is recommended to use when you're going to wait for the job to finish within some narrow scope.
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
