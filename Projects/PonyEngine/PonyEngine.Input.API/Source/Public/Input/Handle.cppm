/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Handle;

import <cstddef>;
import <unordered_map>;

export namespace PonyEngine::Input
{
	/// @brief Registered input event handle.
	struct Handle final
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const Handle& other) const noexcept = default;

		std::size_t id; ///< Unique event ID.
	};

	/// @brief Handle hash struct.
	struct HandleHash final
	{
		[[nodiscard("Pure operator")]]
		std::size_t operator ()(const Handle& handle) const noexcept;
	};
}

namespace PonyEngine::Input
{
	std::size_t HandleHash::operator ()(const Handle& handle) const noexcept
	{
		return handle.id;
	}
}
