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

export module PonyEngine.Render.Direct3D12.Detail:Attachment;

import <array>;
import <cstdint>;
import <string_view>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Attachment types.
	enum class Attachment : std::uint8_t
	{
		RenderTarget,
		Resolve,
		DepthStencil
	};

	/// @brief Gets a string representation of the @p attachment.
	/// @param attachment Attachment.
	/// @return String representation of the @p attachment.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ToString(Attachment attachment) noexcept;
}

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Attachment names.
	constexpr std::array<std::string_view, 3> AttachmentNames
	{
		"RenderTarget",
		"Resolve",
		"DepthStencil"
	};

	constexpr std::string_view ToString(const Attachment attachment) noexcept
	{
		if (const std::size_t index = static_cast<std::size_t>(attachment); index < AttachmentNames.size()) [[likely]]
		{
			return AttachmentNames[index];
		}

		assert(false && "Invalid attachment.");
		return "Unknown";
	}
}
