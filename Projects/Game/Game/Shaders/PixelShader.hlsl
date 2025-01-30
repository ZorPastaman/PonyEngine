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
	float4 color : COLOR;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

PixelOutput main(PixelInput input)
{
	PixelOutput output;
	output.color = input.color;

	return output;
}
