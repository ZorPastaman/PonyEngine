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

export module PonyEngine.Resource:IResourceRequestObserver;

import :ResourceID;

export namespace PonyEngine::Resource
{
	/// @brief Resource request observer.
	class IResourceRequestObserver
	{
		PONY_INTERFACE_BODY(IResourceRequestObserver)

		/// @brief Invoked on request status change.
		/// @param resourceId Resource ID.
		virtual void OnStatusChanged(ResourceID resourceId) = 0;
	};
}
