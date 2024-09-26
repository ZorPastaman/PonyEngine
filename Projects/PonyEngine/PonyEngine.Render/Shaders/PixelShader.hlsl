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

float4 main(PixelInput input) : SV_TARGET
{
	return input.color;
}