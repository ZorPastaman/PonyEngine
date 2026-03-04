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
	struct DSVTextureMeta final
	{
		const ITexture* texture = nullptr; ///< Target texture of a view.
		DSVParams params; ///< View parameters.
	};

	using DSVMeta = std::variant<EmptyDSVMeta, DSVTextureMeta>; ///< Depth stencil view meta.
}
