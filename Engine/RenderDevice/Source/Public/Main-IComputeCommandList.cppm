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

export module PonyEngine.RenderDevice:IComputeCommandList;

import std;

import :ICommandList;

export namespace PonyEngine::RenderDevice
{
	class IComputeCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IComputeCommandList)
	};
}
