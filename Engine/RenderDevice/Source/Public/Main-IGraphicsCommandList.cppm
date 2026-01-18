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

export module PonyEngine.RenderDevice:IGraphicsCommandList;

import std;

import :ICommandList;

export namespace PonyEngine::RenderDevice
{
	class IGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IGraphicsCommandList)
	};
}
