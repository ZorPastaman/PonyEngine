/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:Resource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	struct Resource final
	{
		ResourceID id;
		ResourceType type;
		std::vector<ResourceID> dependencies;
		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData;
		std::vector<std::type_index> outputTypes;
		ResourceCollectionID collection;
		std::size_t index = std::numeric_limits<std::size_t>::max();
		std::type_index dataAccessType;
	};
}
