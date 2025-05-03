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
	float3 position : TEXCOORD0;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

StructuredBuffer<float4> Color : register(t4);

Texture1D Filter : register(t5);
sampler FilterSampler : register(s0);

PixelOutput main(PixelInput input)
{
	PixelOutput output;
	output.color = Color[0] * Filter.Sample(FilterSampler, input.position.x * 0.5f + 0.5f);

	return output;
}
