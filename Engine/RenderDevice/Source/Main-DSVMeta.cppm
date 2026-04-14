/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DSVMeta;

import std;

import :DSVParams;
import :ITexture;

export namespace PonyEngine::RenderDevice
{
	/// @brief Empty depth stencil view meta. It means that no view was created.
	struct EmptyDSVMeta final
	{
	};

	/// @brief Depth stencil view to a texture meta.
	struct TextureDSVMeta final
	{
		const ITexture* texture = nullptr; ///< Target texture. May be nullptr.
		DSVParams params; ///< Depth stencil view parameters.
	};

	using DSVMeta = std::variant<EmptyDSVMeta, TextureDSVMeta>; ///< Depth stencil view meta.
}
