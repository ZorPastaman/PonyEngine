/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:VariantEntry;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	struct VariantEntry final
	{
		std::vector<std::pair<ContextKey, ContextValue>> requiredContext;
		IResourceProvider* provider = nullptr;
		std::size_t index = 0uz;
		ResourceHandle handle;
		std::uint32_t priority = 0u;
		ResourceAvailability availability = ResourceAvailability::None;
	};
}
