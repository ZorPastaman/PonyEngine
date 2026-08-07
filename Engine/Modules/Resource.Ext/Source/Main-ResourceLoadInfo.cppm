/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceLoadInfo;

import std;

import :ResourceType;

export namespace PonyEngine::Resource
{
	/// @brief Resource load info.
	struct ResourceLoadInfo final
	{
		ResourceType type; ///< Resource type.
		std::span<const std::byte> dataMeta; ///< Resource data meta.
		std::span<const std::byte> loadMeta; ///< Resource load meta.
		std::span<const std::type_index> dataAccessTypes; ///< Resource access types.
	};
}
