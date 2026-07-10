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
	/// @brief Resource.
	class IResource
	{
		PONY_INTERFACE_BODY(IResource)

		/// @brief Gets a resource ID.
		/// @return Resource ID.
		[[nodiscard("Pure function")]]
		virtual ResourceID ResourceID() const noexcept = 0;
		/// @brief Gets a resource type.
		/// @return Resource type.
		[[nodiscard("Pure function")]]
		virtual ResourceType Type() const noexcept = 0;
	};
}
