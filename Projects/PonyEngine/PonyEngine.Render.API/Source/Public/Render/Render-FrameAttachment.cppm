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

export module PonyEngine.Render:FrameAttachment;

import <algorithm>;
import <array>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Frame attachment names.
	constexpr std::array<std::string_view, 4> FrameAttachmentNames
	{
		"RenderTarget",
		"Resolve",
		"DepthStencil",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Frame attachments.
	enum class FrameAttachment : std::uint8_t
	{
		/// @brief Render target is presented if a frame has a color output.
		RenderTarget,
		/// @brief Resolve target is presented if a frame has a color output and its sample count > 1. In a msaa scenario, the render target is multi-sampled and the resolve isn't. In a non-msaa scenario, the resolve doesn't exist.
		Resolve,
		/// @brief Depth stencil is presented if a frame has a depth output.
		DepthStencil
	};

	ENUM_VALUE_FEATURES(FrameAttachment, FrameAttachmentNames)
}
