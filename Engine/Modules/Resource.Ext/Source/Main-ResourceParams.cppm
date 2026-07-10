/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceParams;

import std;

import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	/// @brief Resource parameters.
	struct ResourceParams final
	{
		ResourceID id; ///< Resource ID. Must be valid.
		ResourceType type; ///< Resource type. Must be valid.
		ResourceAvailability availability = ResourceAvailability::None; ///< Resource availability. Must have at least one flag set.
		std::size_t index = 0uz; ///< Resource index.
	};
}
