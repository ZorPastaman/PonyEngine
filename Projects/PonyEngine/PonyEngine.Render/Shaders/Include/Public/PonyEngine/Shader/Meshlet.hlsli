/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

struct Meshlet
{
	uint vertexOffset;
	uint primitiveOffset;
	uint packedCounts;
};

void UnpackMeshletCounts(in Meshlet meshlet, out uint vertexCount, out uint primitiveCount)
{
	vertexCount = meshlet.packedCounts & 0xFF;
	primitiveCount = meshlet.packedCounts >> 8 & 0xFF;
}
