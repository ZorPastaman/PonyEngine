/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "RootSignature.hlsli"

float4x4 ModelViewProjection : register(b0);

struct VertexInput
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

[RootSignature(ROOT_SIGNATURE)]
VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.position = mul(ModelViewProjection, float4(input.position, 1.f));
	output.color = input.color;

	return output;
}
