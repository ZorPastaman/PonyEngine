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

	/// @brief Object handle. Can be used in components to reference objects.
	template<typename>
	struct ObjectHandle final
	{
		HandleID id = std::numeric_limits<HandleID>::max(); ///< Handle ID.
		HandleVersion version = 0u; ///< Handle version.

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ObjectHandle& other) const noexcept = default;
	};
}

export template<typename T>
struct std::hash<PonyEngine::World::ObjectHandle<T>> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::World::ObjectHandle<T>& handle) const noexcept
	{
		return std::hash<std::uint64_t>()(*reinterpret_cast<const std::uint64_t*>(&handle));
	}
};
