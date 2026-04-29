/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Job:JobStatus;

import std;

export namespace PonyEngine::Job
{
	enum class JobStatus : std::uint8_t
	{
		Waiting,
		Pending,
		Running,
		Completed,
		Failed,
		DependencyFailed
	};
}

namespace PonyEngine::Job
{
	constexpr std::array<std::string_view, 8> JobStatusNames
	{
		"Waiting",
		"Pending",
		"Running",
		"Completed",
		"Failed",
		"DependencyFailed"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Job::JobStatus, PonyEngine::Job::JobStatusNames)
}
