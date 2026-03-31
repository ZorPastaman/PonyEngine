/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DSVParams;

import :DSVFlag;
import :DSVLayout;
import :TextureDimension;
import :TextureFormatID;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil view parameters.
	struct DSVParams final
	{
		TextureFormatID format; ///< Texture format. Must be compatible with a pointed texture format.
		TextureDimension dimension = TextureDimension::Texture2D; ///< Texture view dimension. Must be the same as a texture dimension.
		DSVFlag flags = DSVFlag::None; ///< Depth stencil view flags.
		DSVLayout layout; ///< Depth stencil view layout.
	};
}
