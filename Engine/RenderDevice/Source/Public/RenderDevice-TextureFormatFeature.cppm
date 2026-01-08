/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.RenderDevice:TextureFormatFeature;

import std;

export namespace PonyEngine::Render
{
	enum class TextureFormatFeature : std::uint32_t
	{
		None = 0,
		ShaderLoad = 1 << 0,
		ShaderSample = 1 << 1,
		ShaderSampleComparison = 1 << 2,
		ShaderGather = 1 << 3,
		ShaderGatherComparison = 1 << 4,
		RenderTarget = 1 << 5,
		Blendable = 1 << 6,
		LogicBlendable = 1 << 7,
		DepthStencil = 1 << 8,
		UnorderedAccess = 1 << 9,
		UnorderedAccessAtomicAdd = 1 << 10,
		UnorderedAccessAtomicBitwise = 1 << 11,
		UnorderedAccessAtomicExchange = 1 << 12,
		UnorderedAccessAtomicExchangeComparison = 1 << 13,
		UnorderedAccessAtomicSignedMinMax = 1 << 14,
		UnorderedAccessAtomicUnsignedMinMax = 1 << 15,
		UnorderedAccessLoad = 1 << 16,
		UnorderedAccessStore = 1 << 17,
		SwapChain = 1 << 18,
		SRGB = 1 << 19,
		All = (1 << 20) - 1
	};

	PONY_ENUM_MASK_FEATURES(TextureFormatFeature)
}
