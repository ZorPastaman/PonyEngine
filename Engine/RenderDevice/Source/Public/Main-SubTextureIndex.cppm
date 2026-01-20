/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureIndex;

import std;

export namespace PonyEngine::RenderDevice
{
	struct SubTextureIndex final
	{
		std::uint32_t mipIndex = 0u;
		std::uint32_t arrayIndex = 0u;
		std::uint8_t planeIndex = 0u;
	};

	struct TextureMipRange final
	{
		std::uint32_t mipOffset = 0u;
		std::uint32_t mipLength = 1u;
		std::uint32_t arrayIndex = 0u;
		std::uint8_t planeIndex = 0u;
	};

	struct TextureArrayRange final
	{
		std::uint32_t arrayOffset = 0u;
		std::uint32_t arrayLength = 1u;
		std::uint8_t planeIndex = 0u;
	};

	struct TexturePlaneRange final
	{
		std::uint8_t planeOffset = 0u;
		std::uint8_t planeLength = 1u;
	};

	struct TextureAllRange final
	{
	};

	using SubTextureRange = std::variant<TextureAllRange, SubTextureIndex, TextureMipRange, TextureArrayRange, TexturePlaneRange>;
}
