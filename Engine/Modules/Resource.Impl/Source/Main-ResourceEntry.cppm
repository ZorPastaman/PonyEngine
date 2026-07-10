/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:ResourceEntry;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Resource entry.
	struct ResourceEntry final
	{
		ResourceID id; ///< Resource ID.
		ResourceType type; ///< Resource type.
		ResourceAvailability availability = ResourceAvailability::None; ///< Resource availability.
		std::size_t index = 0uz; ///< Resource index.
		IResourceProvider* provider = nullptr; ///< Resource provider.
	};
}
