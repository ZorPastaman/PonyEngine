/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RenderTargetMeta;

import std;

import :ITexture;
import :RTVParams;

export namespace PonyEngine::RenderDevice
{
	struct EmptyRenderTargetMeta final
	{
	};

	struct RenderTargetTextureMeta final
	{
		const ITexture* texture = nullptr;
		RTVParams params;
	};

	using RenderTargetMeta = std::variant<EmptyRenderTargetMeta, RenderTargetTextureMeta>;
}
