/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:ResourceInfo;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Resource info.
	struct ResourceInfo final
	{
		ResourceID id; ///< Resource ID.
		ResourceType type; ///< Resource type.

		ResourceCollectionID collection; ///< Collection ID that uses this resource.
		std::size_t collectionResourceIndex; ///< Collection resource index.
		std::type_index dataAccessType; ///< Data access type.

		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Load data.

		std::vector<std::type_index> outputTypes; ///< Output types.
	};
}
