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

export module PonyEngine.Resource.Impl:IResourceLoadObserver;

export namespace PonyEngine::Resource
{
	class IResourceLoadObserver
	{
		PONY_INTERFACE_BODY(IResourceLoadObserver)

		virtual void OnStatusChanged() noexcept = 0;
	};
}
