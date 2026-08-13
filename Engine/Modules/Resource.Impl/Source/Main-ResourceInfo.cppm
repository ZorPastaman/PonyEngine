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
	struct ResourceInfo final
	{
		ResourceID id;
		ResourceType type;

		std::vector<ResourceID> dependencies;

		ResourceCollectionID collection;
		std::size_t collectionResourceIndex;
		std::type_index dataAccessType;

		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData;

		std::vector<std::type_index> outputTypes;
	};
}
