/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:VariantParams;

import std;

import PonyEngine.Resource;

import :ResourceReference;

export namespace PonyEngine::Resource
{
	struct VariantParams final
	{
		std::span<const std::pair<ContextKey, ContextValue>> requiredContext;
		std::uint32_t priority = 0uz;
		std::size_t index = 0uz;
		ResourceReference resourceReference;
	};
}
