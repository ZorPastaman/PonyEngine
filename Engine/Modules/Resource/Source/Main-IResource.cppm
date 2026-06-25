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

export module PonyEngine.Resource:IResource;

import std;

import :ResourceID;
import :ResourceType;

export namespace PonyEngine::Resource
{
	class IResource
	{
		PONY_INTERFACE_BODY(IResource)

		[[nodiscard("Pure function")]]
		virtual ResourceID ResourceID() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept = 0;
	};
}
