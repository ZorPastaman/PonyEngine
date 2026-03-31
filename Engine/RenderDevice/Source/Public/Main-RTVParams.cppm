/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RTVParams;

import :RTVLayout;
import :TextureDimension;
import :TextureFormatID;

export namespace PonyEngine::RenderDevice
{
	/// @brief Render target view parameters.
	struct RTVParams final
	{
		TextureFormatID format; ///< Texture format. Must be compatible with a pointed texture format.
		bool srgb = false; ///< Is srgb view? A pointed texture must be srgb-compatible.
		TextureDimension dimension = TextureDimension::Texture2D; ///< Texture dimension.
		RTVLayout layout; ///< Render target view layout.
	};
}
