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
	float4 color : COLOR;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.position = float4(input.position, 1.f);
	output.color = input.color;

	return output;
}
