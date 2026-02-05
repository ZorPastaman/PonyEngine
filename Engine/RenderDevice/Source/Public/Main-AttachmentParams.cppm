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
	struct AttachmentParams final
	{
		std::span<const TextureFormatId> renderTargetFormats;
		std::optional<TextureFormatId> depthStencilFormat;
	};
}
