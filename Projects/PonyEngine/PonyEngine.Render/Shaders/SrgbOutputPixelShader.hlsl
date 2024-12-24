/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "SrgbOutputRootSignature.hlsli"

Texture2D RenderTargetTexture : register(t0);
sampler RenderTargetSampler : register(s0);

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

[RootSignature(SRGB_OUTPUT_ROOT_SIGNATURE)]
float4 main(PixelInput input) : SV_TARGET
{
	return RenderTargetTexture.Sample(RenderTargetSampler, input.uv);
}
