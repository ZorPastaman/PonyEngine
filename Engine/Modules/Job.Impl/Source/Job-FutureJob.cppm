/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job.Impl:FutureJob;

import PonyEngine.Job;

import :JobID;

export namespace PonyEngine::Job
{
	/// @brief Info about a created but not scheduled job.
	struct FutureJob final
	{
		JobID jobId; ///< Job ID.
		JobPriority priority = JobPriority::Normal; ///< Job priority.
	};
}
