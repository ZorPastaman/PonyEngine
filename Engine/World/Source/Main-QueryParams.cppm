/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:QueryParams;

import std;

import :Component;
import :Entity;

export namespace PonyEngine::World
{
	struct QueryParams final
	{
		std::span<const std::type_index> requiredComponentTypes;
		std::span<const std::type_index> excludedComponentTypes;
		std::span<const std::type_index> optionalComponentTypes;
	};

	struct QueryItem final
	{
		std::span<void* const> requiredComponents;
		std::span<void* const> optionalComponents;
		Entity entity;
		bool terminate = false;
	};
}
