/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.World:ObjectHandle;

import std;

export namespace PonyEngine::World
{
	using HandleID = std::uint32_t; ///< Handle ID.
	using HandleVersion = std::uint32_t; ///< Handle version.

	/// @brief Typeless object handle. Don't use them directly. Use the @p ObjectHandle.
	struct TypelessObjectHandle final
	{
		HandleID id = std::numeric_limits<HandleID>::max(); ///< Handle ID.
		HandleVersion version = 0u; ///< Handle version.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const TypelessObjectHandle& other) const noexcept = default;
	};

	/// @brief Object handle. Can be used in components to reference objects.
	template<typename>
	struct ObjectHandle final
	{
		TypelessObjectHandle typeless; ///< Typeless handle.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ObjectHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::World::TypelessObjectHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::TypelessObjectHandle& handle) const noexcept
	{
		const std::uint64_t hash = static_cast<std::uint64_t>(handle.id) << 32 | handle.version;
		return std::hash<std::uint64_t>()(hash);
	}
};

export template<typename T>
struct std::hash<PonyEngine::World::ObjectHandle<T>> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::ObjectHandle<T>& handle) const noexcept
	{
		return std::hash<PonyEngine::World::TypelessObjectHandle>()(handle.typeless);
	}
};
