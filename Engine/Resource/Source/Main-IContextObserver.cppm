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

export module PonyEngine.Resource:IContextObserver;

import std;

import :ContextKey;
import :ResourceID;

export namespace PonyEngine::Resource
{
	class IContextObserver
	{
		PONY_INTERFACE_BODY(IContextObserver)

		virtual void OnContextChanged(std::span<const ContextKey> changedKeys) {}
		virtual void OnResourceChanged(std::span<const ResourceID> resourceIds) {}
	};
}
