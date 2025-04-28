/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Render.Direct3D12.Detail:View;

import <array>;
import <cstdint>;
import <string_view>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief View type.
	enum class View : std::uint8_t
	{
		RenderTarget,
		Output,
		DepthStencil
	};

	/// @brief Creates a string representing the @p view.
	/// @param view View type.
	/// @return String representing the @p view.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ToString(View view) noexcept;
}

namespace PonyEngine::Render::Direct3D12
{
	/// @brief View names.
	constexpr std::array<std::string_view, 3> ViewNames
	{
		"RenderTarget",
		"Output",
		"DepthStencil"
	};

	constexpr std::string_view ToString(const View view) noexcept
	{
		if (const std::size_t index = static_cast<std::size_t>(view); index < ViewNames.size()) [[likely]]
		{
			return ViewNames[index];
		}

		assert(false && "Invalid view.");
		return "Unknown";
	}
}
