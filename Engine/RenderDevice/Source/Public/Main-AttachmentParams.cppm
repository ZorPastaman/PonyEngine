/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:AttachmentParams;

import std;

import :TextureFormatId;

export namespace PonyEngine::RenderDevice
{
	/// @brief Render target attachment format.
	struct RenderTargetAttachmentFormat final
	{
		TextureFormatId format; ///< Render target format. Must be render target compatible.
		bool srgb = false; ///< Is it srgb-variant of the format. The format must be srgb-compatible to set it to true.
	};

	/// @brief Attachment parameters.
	struct AttachmentParams final
	{
		std::span<const RenderTargetAttachmentFormat> renderTargetFormats; ///< Render target formats. Its count must be synced with blend target count and can't exceed max simultaneous target count. If its count is 0, no color rendering is done.
		std::optional<TextureFormatId> depthStencilFormat; ///< Depth stencil format. If nullopt, no depth stencil texture is used.
	};
}
