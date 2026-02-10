/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Core.hlsli"
#include "Game/Material.hlsli"

#ifndef MATERIAL_SET
#define MATERIAL_SET 3
#endif

struct PixelInput
{
	float3 position : TEXCOORD0;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

ConstantBuffer<Game_Material> Material : PONY_CBV_REGISTER(MATERIAL_SET, 0);

PixelOutput main(in PixelInput input)
{
	PixelOutput output;
	output.color = Material.color;

	return output;
}
