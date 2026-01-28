/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencilMeta;

import std;

import :DSVParams;
import :ITexture;

export namespace PonyEngine::RenderDevice
{
	struct EmptyDepthStencilMeta final
	{
	};

	struct DepthStencilTextureMeta final
	{
		const ITexture* texture = nullptr;
		DSVParams params;
	};

	using DepthStencilMeta = std::variant<EmptyDepthStencilMeta, DepthStencilTextureMeta>;
}
