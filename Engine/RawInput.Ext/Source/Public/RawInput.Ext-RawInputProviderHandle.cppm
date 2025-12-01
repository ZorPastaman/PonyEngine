/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Ext:RawInputProviderHandle;

import std;

export namespace PonyEngine::Input
{
	/// @brief Raw input provider handle.
	struct RawInputProviderHandle final
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
		constexpr auto operator <=>(const RawInputProviderHandle& other) const noexcept = default;
	};
}

export
{
	template<>
	struct std::hash<PonyEngine::Input::RawInputProviderHandle> final
	{
		[[nodiscard("Pure function")]]
		size_t operator ()(const PonyEngine::Input::RawInputProviderHandle handle) const noexcept
		{
			return std::hash<std::uint32_t>()(handle.id);
		}
	};
}

namespace PonyEngine::Input
{
	constexpr bool RawInputProviderHandle::IsValid() const noexcept
	{
		return id;
	}

	constexpr RawInputProviderHandle::operator bool() const noexcept
	{
		return IsValid();
	}
}
