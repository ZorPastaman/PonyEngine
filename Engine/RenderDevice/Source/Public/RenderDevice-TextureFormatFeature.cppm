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

namespace PonyEngine::Render
{
	constexpr std::array<std::string_view, 30> TextureFormatFeatureNames
	{
		"Texture1D",
		"Texture2D",
		"Texture3D",
		"TextureCube",
		"ShaderLoad",
		"ShaderSample",
		"ShaderSampleComparison",
		"ShaderGather",
		"ShaderGatherComparison",
		"RenderTarget",
		"DepthStencil",
		"SwapChain",
		"Blendable",
		"LogicBlendable",
		"Mip",
		"MSResolve",
		"MSRenderTarget",
		"MSLoad",
		"CastWithinBitLayout",
		"BackBufferCast",
		"Tiled",
		"Uav",
		"UavAtomicAdd",
		"UavAtomicBitwise",
		"UavAtomicExchange",
		"UavAtomicCompareStoreCompareExchange",
		"UavAtomicSignedMixMax",
		"UavAtomicUnsignedMixMax",
		"UavTypedLoad",
		"UavTypedStore"
	};
}

export namespace PonyEngine::Render
{
	enum class TextureFormatFeature : std::uint32_t
	{
		None = 0,
		Texture1D = 1 << 0,
		Texture2D = 1 << 1,
		Texture3D = 1 << 2,
		TextureCube = 1 << 3,
		ShaderLoad = 1 << 4,
		ShaderSample = 1 << 5,
		ShaderSampleComparison = 1 << 6,
		ShaderGather = 1 << 7,
		ShaderGatherComparison = 1 << 8,
		RenderTarget = 1 << 9,
		DepthStencil = 1 << 10,
		SwapChain = 1 << 11,
		Blendable = 1 << 12,
		LogicBlendable = 1 << 13,
		Mip = 1 << 14,
		MSResolve = 1 << 15,
		MSRenderTarget = 1 << 16,
		MSLoad = 1 << 17,
		CastWithinBitLayout = 1 << 18,
		BackBufferCast = 1 << 19,
		Tiled = 1 << 20,
		Uav = 1 << 21,
		UavAtomicAdd = 1 << 22,
		UavAtomicBitwise = 1 << 23,
		UavAtomicExchange = 1 << 24,
		UavAtomicCompareStoreCompareExchange = 1 << 25,
		UavAtomicSignedMixMax = 1 << 26,
		UavAtomicUnsignedMixMax = 1 << 27,
		UavTypedLoad = 1 << 28,
		UavTypedStore = 1 << 29,
		All = (1 << 30) - 1
	};

	PONY_ENUM_MASK_FEATURES(TextureFormatFeature)
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::Render::TextureFormatFeature, PonyEngine::Render::TextureFormatFeatureNames)
}
