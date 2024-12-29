/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

Texture2D RenderTargetTexture : register(t0);
sampler RenderTargetSampler : register(s0);

PixelOutput main(PixelInput input)
{
	PixelOutput output;
	output.color = RenderTargetTexture.Sample(RenderTargetSampler, input.uv);

	return output;
}
