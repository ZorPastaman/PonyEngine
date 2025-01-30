/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

struct Pony_Primitive
{
	uint indices;
};

uint2 UnpackLineFirst(in Pony_Primitive primitive)
{
	return uint2(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF);
}

uint2 UnpackLineSecond(in Pony_Primitive primitive)
{
	return uint2(primitive.indices >> 16 & 0xFF, primitive.indices >> 24 & 0xFF);
}

uint2 UnpackLine(in Pony_Primitive primitive, in uint offset)
{
	return uint2(primitive.indices >> (8 * offset) & 0xFF, primitive.indices >> (8 * (offset + 1)) & 0xFF);
}

uint3 UnpackTriangle(in Pony_Primitive primitive)
{
	return uint3(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF, primitive.indices >> 16 & 0xFF);
}

uint4 UnpackQuad(in Pony_Primitive primitive)
{
	return uint4(primitive.indices & 0xFF, primitive.indices >> 8 & 0xFF, primitive.indices >> 16 & 0xFF, primitive.indices >> 24 & 0xFF);
}
