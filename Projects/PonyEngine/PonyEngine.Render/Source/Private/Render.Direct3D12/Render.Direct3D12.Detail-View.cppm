/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyEngine.Render.Direct3D12.Detail:View;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render::Direct3D12
{
	/// @brief View names.
	constexpr std::array<std::string_view, 4> ViewNames
	{
		"RenderTarget",
		"Output",
		"DepthStencil",
		"Unknown"
	};
}

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief View type.
	enum class View : std::uint8_t
	{
		RenderTarget,
		Output,
		DepthStencil
	};

	ENUM_VALUE_FEATURES(View, ViewNames)
}
