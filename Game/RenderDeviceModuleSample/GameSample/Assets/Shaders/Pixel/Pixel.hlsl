#include "PonyEngine/Core.hlsli"

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

struct Material
{
	float4 color;
};

ConstantBuffer<Material> Material : PONY_CBV_REGISTER(MATERIAL_SET, 0);

PixelOutput main(in const PixelInput input)
{
	PixelOutput output;
	output.color = Material.color;

	return output;
}
