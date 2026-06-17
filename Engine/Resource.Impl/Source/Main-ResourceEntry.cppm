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

import PonyEngine.Resource;

import :VariantEntry;

export namespace PonyEngine::Resource
{
	struct ResourceEntry final
	{
		ResourceID id;
		ResourceType type;
		std::vector<VariantEntry> variants;
	};
}
