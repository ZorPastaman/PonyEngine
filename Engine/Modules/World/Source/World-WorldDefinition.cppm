/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:WorldDefinition;

import std;

import :Entity;

export namespace PonyEngine::World
{
	/// @brief Component table definition.
	struct ComponentTableDefinition final
	{
		std::vector<std::size_t> entityBindings; ///< Entity bindings.
		std::vector<std::byte> data; ///< Component data.
	};

	/// @brief World definition.
	/// @details It's a serialized data of a world.
	struct WorldDefinition final
	{
		std::size_t entityCount = 0u; ///< Entity count.
		std::unordered_map<std::type_index, ComponentTableDefinition> components; ///< Components.
		std::vector<std::pair<std::type_index, std::shared_ptr<void>>> objects; ///< World objects.
	};
}
