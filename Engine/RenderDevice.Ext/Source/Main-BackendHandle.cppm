/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Ext:BackendHandle;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Backend handle.
	struct BackendHandle final
	{
		std::uint32_t id = 0u; ///< ID. It's used only by the owner.

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsValid() const noexcept;

		/// @brief Checks if the handle is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure operator")]]
		explicit constexpr operator bool() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr auto operator <=>(const BackendHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::RenderDevice::BackendHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::RenderDevice::BackendHandle handle) const noexcept
	{
		return std::hash<std::uint32_t>()(handle.id);
	}
};

namespace PonyEngine::RenderDevice
{
	constexpr bool BackendHandle::IsValid() const noexcept
	{
		return id;
	}

	constexpr BackendHandle::operator bool() const noexcept
	{
		return IsValid();
	}
}
