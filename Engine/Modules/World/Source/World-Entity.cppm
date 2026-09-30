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
	struct alignas(std::uint64_t) Entity final
	{
		EntityID id = std::numeric_limits<EntityID>::max(); ///< Entity ID.
		EntityGeneration generation = 0u; ///< Entity generation.

		/// @brief Returns the entity as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		std::uint64_t& AsRawData() noexcept;
		/// @brief Returns the entity as std::uint64_t.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		const std::uint64_t& AsRawData() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const Entity& other) const noexcept = default;
	};

	static_assert(sizeof(Entity) == sizeof(std::uint64_t) && alignof(Entity) == alignof(std::uint64_t), "Entity is invalid");

	/// @brief Returns the entity as std::uint64_t.
	/// @param entity Entity.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::uint64_t& AsRawData(Entity& entity) noexcept;
	/// @brief Returns the entity as std::uint64_t.
	/// @param entity Entity.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	const std::uint64_t& AsRawData(const Entity& entity) noexcept;

	/// @brief Returns the span of entities as a span of std::uint64_t.
	/// @param entities Entities.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<std::uint64_t> AsRawData(std::span<Entity> entities) noexcept;
	/// @brief Returns the span of entities as a span of std::uint64_t.
	/// @param entities Entities.
	/// @return Raw data.
	[[nodiscard("Pure function")]]
	std::span<const std::uint64_t> AsRawData(std::span<const Entity> entities) noexcept;
}

namespace PonyEngine::World
{
	std::uint64_t& Entity::AsRawData() noexcept
	{
		return World::AsRawData(*this);
	}

	const std::uint64_t& Entity::AsRawData() const noexcept
	{
		return World::AsRawData(*this);
	}

	std::uint64_t& AsRawData(Entity& entity) noexcept
	{
		return reinterpret_cast<std::uint64_t&>(entity);
	}

	const std::uint64_t& AsRawData(const Entity& entity) noexcept
	{
		return reinterpret_cast<const std::uint64_t&>(entity);
	}

	std::span<std::uint64_t> AsRawData(const std::span<Entity> entities) noexcept
	{
		return std::span(reinterpret_cast<std::uint64_t*>(entities.data()), entities.size());
	}

	std::span<const std::uint64_t> AsRawData(const std::span<const Entity> entities) noexcept
	{
		return std::span(reinterpret_cast<const std::uint64_t*>(entities.data()), entities.size());
	}
}

export template<>
struct std::hash<PonyEngine::World::Entity> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::Entity& entity) const noexcept
	{
		return std::hash<std::uint64_t>()(entity.AsRawData());
	}
};
