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
	struct ResourceParams final
	{
		ResourceID id;
		ResourceType type;
		std::span<const std::pair<ContextKey, ContextValue>> requiredContext;
		std::size_t index = 0uz;
		std::uint32_t priority = 0u;
		ResourceAvailability availability = ResourceAvailability::None;
	};
}
