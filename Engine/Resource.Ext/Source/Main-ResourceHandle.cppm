/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceHandle;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource handle.
	struct ResourceHandle final
	{
		std::uint64_t id = 0ull; ///< ID. It's used only by the owner.

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsValid() const noexcept;

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const ResourceHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Resource::ResourceHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Resource::ResourceHandle handle) const noexcept
	{
		return std::hash<std::uint64_t>()(handle.id);
	}
};

namespace PonyEngine::Resource
{
	constexpr bool ResourceHandle::IsValid() const noexcept
	{
		return id;
	}

	constexpr ResourceHandle::operator bool() const noexcept
	{
		return IsValid();
	}
}
