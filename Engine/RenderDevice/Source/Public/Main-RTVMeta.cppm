/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RTVMeta;

import std;

import :ITexture;
import :RTVParams;

export namespace PonyEngine::RenderDevice
{
	/// @brief Empty render target meta. It means no view was created.
	struct EmptyRenderTargetMeta final
	{
	};

	/// @brief Render target view to a texture meta.
	struct RenderTargetTextureMeta final
	{
		const ITexture* texture = nullptr; ///< Target texture. May be nullptr.
		RTVParams params; ///< Render target view parameters.
	};

	using RenderTargetMeta = std::variant<EmptyRenderTargetMeta, RenderTargetTextureMeta>; ///< Render target view meta.
}
