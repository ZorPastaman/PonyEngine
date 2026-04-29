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

export module PonyEngine.Job:ITask;

export namespace PonyEngine::Job
{
	class ITask
	{
		PONY_INTERFACE_BODY(ITask)

		virtual void Execute() = 0;
	};
}
