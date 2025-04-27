/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

struct PixelOutput
{
	float4 color : SV_TARGET;
};

StructuredBuffer<float4> Color : register(t4);

PixelOutput main()
{
	PixelOutput output;
	output.color = Color[0];

	return output;
}
