/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceLoadData;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource load data.
	struct ResourceLoadData final
	{
		std::size_t dataAccessTypeIndex = std::numeric_limits<std::size_t>::max(); ///< Data access type index that will be used on a resource load.
		std::vector<std::type_index> outputTypes; ///< Resource output types.
		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Load data that will be passed on a resource load.
	};
}
