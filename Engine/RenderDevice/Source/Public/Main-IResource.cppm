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

export module PonyEngine.RenderDevice:IResource;

import std;

export namespace PonyEngine::RenderDevice
{
	class IResource
	{
		PONY_INTERFACE_BODY(IResource)

		virtual void SetName(std::string_view name) = 0;
	};
}
