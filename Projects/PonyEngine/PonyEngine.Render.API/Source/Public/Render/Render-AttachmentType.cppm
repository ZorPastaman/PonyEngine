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

export module PonyEngine.Render:AttachmentType;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Attachment type names.
	constexpr std::array<std::string_view, 4> AttachmentTypeNames
	{
		"RenderTarget",
		"Resolve"
		"DepthStencil",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Attachment type.
	enum class AttachmentType : std::uint8_t
	{
		/// @brief An attachment that is used as a render target.
		RenderTarget,
		/// @brief An attachment that is used as a resolve in an msaa context. A frame doesn't have such an attachment in a non-msaa context.
		Resolve,
		/// @brief An attachment that is used as a depth stencil.
		DepthStencil
	};

	ENUM_VALUE_FEATURES(AttachmentType, AttachmentTypeNames)
}