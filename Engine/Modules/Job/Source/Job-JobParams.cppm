/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job:JobParams;

import std;

import :JobHandle;
import :JobPriority;

export namespace PonyEngine::Job
{
	/// @brief Job parameters.
	struct JobParams final
	{
		std::span<const JobHandle> dependencies; ///< Job dependencies.
		JobPriority priority = JobPriority::Normal; ///< Job priority.
	};
}
