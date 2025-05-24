/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:TextureParams;

import <cstdint>;
import <string>;

import :ClearValue;
import :TextureDimension;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Texture parameters.
	struct TextureParams final
	{
		TextureDimension dimension = TextureDimension::Texture2D; ///< Texture dimension.
		TextureFormat format = TextureFormat::R8G8B8A8_Unorm; ///< Texture format. Can't be a depth stencil format.

		std::uint32_t width = 1u; ///< Width in pixels.
		std::uint32_t height = 1u; ///< Height in pixels.
		std::uint32_t depth = 1u; ///< Depth in pixels. It's an array size for array dimensions. For TextureCube it must be 6.

		std::string name; ///< Texture name.
	};
}
