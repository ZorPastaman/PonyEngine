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
import :SubTextureRange;
import :TextureFormatId;

export namespace PonyEngine::RenderDevice
{
	struct BufferSRVParams final
	{
		std::uint64_t firstElementIndex = 0ull;
		std::uint32_t elementCount = 0u;
		std::uint32_t stride = 0u;
		bool raw = false;
	};

	struct TextureSRVParams
	{
		TextureFormatId format;
		Aspect aspect;
		ComponentMapping mapping;
	};

	struct Texture1DSRVParams : TextureSRVParams
	{
		MipRange mipRange;
	};

	struct Texture1DArraySRVParams final : Texture1DSRVParams
	{
		ArrayRange arrayRange;
	};

	struct Texture2DSRVParams : TextureSRVParams
	{
		MipRange mipRange;
	};

	struct Texture2DArraySRVParams final : Texture2DSRVParams
	{
		ArrayRange arrayRange;
	};

	struct Texture2DMSSRVParams : TextureSRVParams
	{
	};

	struct Texture2DMSArraySRVParams final : Texture2DMSSRVParams
	{
		ArrayRange arrayRange;
	};

	struct Texture3DSRVParams final : TextureSRVParams
	{
		MipRange mipRange;
	};

	struct TextureCubeSRVParams : TextureSRVParams
	{
		MipRange mipRange;
	};

	struct TextureCubeArraySRVParams final : TextureCubeSRVParams
	{
		ArrayRange arrayRange;
	};
}
