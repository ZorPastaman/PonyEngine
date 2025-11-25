/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application.Ext:ServiceHandle;

import std;

export namespace PonyEngine::Application
{
	/// @brief Service handle.
	struct ServiceHandle final
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
		constexpr auto operator <=>(const ServiceHandle& other) const noexcept = default;
	};
}

export template<>
struct std::hash<PonyEngine::Application::ServiceHandle> final
{
	[[nodiscard("Pure function")]]
	size_t operator ()(const PonyEngine::Application::ServiceHandle handle) const noexcept
	{
		return std::hash<std::uint32_t>()(handle.id);
	}
};

namespace PonyEngine::Application
{
	constexpr bool ServiceHandle::IsValid() const noexcept
	{
		return id;
	}

	constexpr ServiceHandle::operator bool() const noexcept
	{
		return IsValid();
	}
}
