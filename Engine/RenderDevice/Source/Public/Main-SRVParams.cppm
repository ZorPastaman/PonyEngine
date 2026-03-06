/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SRVParams;

import std;

import :Aspect;
import :ComponentMapping;
import :SRVLayout;
import :TextureFormatId;
import :TextureViewDimension;

export namespace PonyEngine::RenderDevice
{
	/// @brief Buffer shader resource view parameters.
	struct BufferSRVParams final
	{
		std::uint64_t firstElementIndex = 0ull; ///< First element index.
		std::uint32_t elementCount = 0u; ///< Element count.
		std::uint32_t stride = 0u; ///< Element stride in bytes.
	};

	/// @brief Texture shader resource view parameters.
	struct TextureSRVParams final
	{
		TextureFormatId format; ///< Texture format. Must be compatible with a texture.
		bool srgb = false; ///< Is it srgb view? If @a true, a texture must be srgb-compatible.
		TextureViewDimension dimension = TextureViewDimension::Texture2D; ///< Texture view dimension.
		Aspect aspect = Aspect::Color; ///< Target aspect. A texture must have this aspect.
		ComponentMapping mapping; ///< Component mapping.
		SRVLayout layout; ///< Shader resource view layout.
	};
}
