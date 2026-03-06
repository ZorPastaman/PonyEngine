/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:UAVParams;

import std;

import :Aspect;
import :TextureDimension;
import :TextureFormatId;
import :UAVLayout;

export namespace PonyEngine::RenderDevice
{
	/// @brief Buffer unordered access view parameters.
	struct BufferUAVParams final
	{
		std::uint64_t firstElementIndex = 0ull; ///< First element index.
		std::uint32_t elementCount = 0u; ///< Element count.
		std::uint32_t stride = 0u; ///< Element stride in bytes.
	};

	/// @brief Texture unordered access view parameters.
	struct TextureUAVParams final
	{
		TextureFormatId format; ///< Texture format.
		TextureDimension dimension = TextureDimension::Texture2D; ///< Texture dimension.
		Aspect aspect = Aspect::Color; ///< Aspect.
		UAVLayout layout; ///< Layout.
	};
}
