/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderObjectHandle;

import <cstddef>;

export namespace PonyEngine::Render
{
	/// @brief Render object handle.
	struct RenderObjectHandle final
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const RenderObjectHandle& other) const noexcept = default;

		std::size_t id; ///< Render object id.
	};

	/// @brief Render object handle hash function.
	struct RenderObjectHandleHash final
	{
		/// @brief Computes a render object handle hash.
		/// @param handle Render object handle.
		/// @return Hash.
		[[nodiscard("Pure operator")]]
		std::size_t operator ()(const RenderObjectHandle& handle) const noexcept;
	};
}

namespace PonyEngine::Render
{
	std::size_t RenderObjectHandleHash::operator ()(const RenderObjectHandle& handle) const noexcept
	{
		return handle.id;
	}
}
