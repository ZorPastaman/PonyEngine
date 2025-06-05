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

export module PonyEngine.Render.Direct3D12.Detail:Attachment;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Attachment names.
	constexpr std::array<std::string_view, 4> AttachmentNames
	{
		"RenderTarget",
		"Resolve",
		"DepthStencil",
		"Unknown"
	};
}

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Attachment types.
	enum class Attachment : std::uint8_t
	{
		RenderTarget,
		Resolve,
		DepthStencil
	};

	ENUM_VALUE_FEATURES(Attachment, AttachmentNames)
}
