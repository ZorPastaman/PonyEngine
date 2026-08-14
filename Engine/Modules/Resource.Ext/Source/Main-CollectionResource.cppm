/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:CollectionResource;

import std;

import PonyEngine.Resource;

import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Collection resource info.
	struct CollectionResource final
	{
		ResourceID id; ///< Resource ID. Must be valid.
		ResourceType type; ///< Resource type. Must be valid.
		std::span<const std::byte> dataMeta; ///< Resource data meta. It's used by a loader.
		std::span<const std::byte> loadMeta; ///< Resource load meta. It's used by a loader.
		std::size_t dataIndex = 0uz; ///< Resource data index.
	};
}
