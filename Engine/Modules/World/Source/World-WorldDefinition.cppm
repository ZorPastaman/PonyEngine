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
	/// @brief World definition.
	/// @details It's a serialized data of a world.
	struct WorldDefinition final
	{
		EntityID entityCount = 0u; ///< Entity count.
		std::unordered_map<std::type_index, std::size_t> componentIndices; ///< Component indices. Point to the @p componentBindings and @p componentData.
		std::vector<std::vector<EntityID>> componentBindings; ///< Component to entity bindings.
		std::vector<std::vector<std::byte>> componentData; ///< Component data. Synced with the @p componentBindings by index. The object handles must contain std::uint64_t indices to the @p objects. The entity references must contain std::uint64_t indices to the entities.
		std::vector<std::pair<std::type_index, std::shared_ptr<void>>> objects; ///< World objects.
		std::unordered_map<std::type_index, std::shared_ptr<void>> worldData; ///< World data.
	};
}
