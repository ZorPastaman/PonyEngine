/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:Entity;

import std;

export namespace PonyEngine::World
{
	using EntityID = std::uint32_t; ///< Entity ID type.
	using EntityGeneration = std::uint32_t; ///< Entity generation type.

	/// @brief Entity.
	struct Entity final
	{
		EntityID id = 0u; ///< Entity ID.
		EntityGeneration generation = 0u; ///< Entity generation.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const Entity& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::World::Entity> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::Entity& entity) const noexcept
	{
		return std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(&entity));
	}
};
