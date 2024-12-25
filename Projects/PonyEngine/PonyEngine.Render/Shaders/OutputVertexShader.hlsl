/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

struct VertexInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.position = float4(input.position, 1.f);
	output.uv = input.uv;

	return output;
}
