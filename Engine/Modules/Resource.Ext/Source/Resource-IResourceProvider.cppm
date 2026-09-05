/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.Ext:IResourceProvider;

import std;

import PonyEngine.Resource;

import :ResourceCollection;

export namespace PonyEngine::Resource
{
	/// @brief Resource provider.
	class IResourceProvider
	{
		PONY_INTERFACE_BODY(IResourceProvider)

		/// @brief Gets a resource data.
		/// @param index Resource index.
		/// @param accessType Access type.
		/// @return Access of the requested type.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<void> GetResourceData(std::size_t index, std::type_index accessType) = 0;
	};
}
