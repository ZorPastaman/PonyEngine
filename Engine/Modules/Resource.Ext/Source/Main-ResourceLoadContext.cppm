/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceLoadContext;

import std;

import PonyEngine.Resource;

import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Resource load context.
	struct ResourceLoadContext final
	{
		ResourceType resourceType; ///< Resource type.
		std::shared_ptr<void> resourceDataAccess; ///< Resource data access.
		std::type_index resourceDataAccessType; ///< Resource data access type.
		std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Resource load data.
		std::span<const std::shared_ptr<const IResourceRequest>> dependencies; ///< Resource dependencies. May be not loaded.
		std::span<const std::type_index> outputTypes; ///< Resource output types.
	};
}
