/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Job:IJob;

import :JobStatus;

export namespace PonyEngine::Job
{
	class IJob
	{
		PONY_INTERFACE_BODY(IJob)

		[[nodiscard("Pure function")]]
		virtual JobStatus Status() const noexcept = 0;
	};
}
