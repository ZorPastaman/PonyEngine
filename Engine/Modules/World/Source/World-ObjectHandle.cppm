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
	using ObjectHandleID = std::uint32_t; ///< Object handle ID.
	using ObjectHandleVersion = std::uint32_t; ///< Handle version.

	/// @brief Typeless object handle. Don't use them directly. Use the @p ObjectHandle.
	struct TypelessObjectHandle final
	{
		ObjectHandleID id = std::numeric_limits<ObjectHandleID>::max(); ///< Handle ID.
		ObjectHandleVersion version = 0u; ///< Handle version.

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
		using Hash = std::uint64_t;
		static_assert(sizeof(Hash) == sizeof(handle), "Invalid hash type.");

		Hash hash;
		std::memcpy(&hash, &handle, sizeof(Hash));
		return std::hash<Hash>()(hash);
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
