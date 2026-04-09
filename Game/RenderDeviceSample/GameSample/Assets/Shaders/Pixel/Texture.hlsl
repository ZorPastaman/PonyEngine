#include "PonyEngine/Core.hlsli"

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

struct PixelOutput
{
	float4 color : SV_TARGET;
};

Texture2D Texture : PONY_SRV_REGISTER(0, 0);
sampler Sampler : PONY_SAMPLER_REGISTER(0, 1);

PixelOutput main(in const PixelInput input)
{
	PixelOutput output;
	output.color = Texture.Sample(Sampler, input.uv);

	return output;
}
