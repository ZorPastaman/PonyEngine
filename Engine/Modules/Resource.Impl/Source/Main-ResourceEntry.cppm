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
	struct ResourceEntry final
	{
		ResourceID id;
		ResourceType type;
		ResourceAvailability availability = ResourceAvailability::None;
		std::size_t index = 0uz;
		IResourceProvider* provider = nullptr;
	};
}
