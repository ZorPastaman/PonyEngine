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
		std::uint32_t priority = 0uz;
		IResourceProvider* provider;
		std::size_t index;
		ResourceHandle handle;
	};
}
