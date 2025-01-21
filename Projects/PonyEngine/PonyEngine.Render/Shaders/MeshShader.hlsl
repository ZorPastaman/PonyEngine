/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#define TRIANGLE_MULTIPLIER 2
#define VERTEX_COUNT 64
#define TRIANGLE_COUNT VERTEX_COUNT * TRIANGLE_MULTIPLIER
#define THREAD_COUNT_X VERTEX_COUNT
#define THREAD_COUNT_Y 1
#define THREAD_COUNT_Z 1

struct PonyTransform
{
	float4x4 modelMatrix;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float4x4 mvpMatrix;
};

struct Meshlet
{
	uint vertexOffset;
	uint primitiveOffset;
	uint packedCounts;
};

struct Vertex
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PonyTransform Transform : register(b0);

StructuredBuffer<Meshlet> Meshlets : register(t0);
StructuredBuffer<uint> VertexIndices : register(t1);
StructuredBuffer<uint> Triangles : register(t2);
StructuredBuffer<float3> Positions : register(t3);
StructuredBuffer<float4> Colors : register(t4);

[outputtopology("triangle")]
[numthreads(THREAD_COUNT_X, THREAD_COUNT_Y, THREAD_COUNT_Z)]
void main(in uint groupId : SV_GROUPID,
	in uint groupThreadId : SV_GROUPTHREADID,
	out vertices Vertex outVertices[VERTEX_COUNT],
	out indices uint3 outTriangles[TRIANGLE_COUNT])
{
	Meshlet meshlet = Meshlets[groupId];
	uint vertexCount = meshlet.packedCounts & 0xFF;
	uint primitiveCount = meshlet.packedCounts >> 8 & 0xFF;
	SetMeshOutputCounts(vertexCount, primitiveCount);

	if (groupThreadId < vertexCount)
	{
		uint vertexIndex = VertexIndices[meshlet.vertexOffset + groupThreadId];
		outVertices[groupThreadId].position = mul(Transform.mvpMatrix, float4(Positions[vertexIndex], 1.f));
		outVertices[groupThreadId].color = Colors[vertexIndex];
	}

	[unroll]
	for (uint i = 0; i < TRIANGLE_MULTIPLIER; ++i)
	{
		uint primitiveIndex = groupThreadId + i * VERTEX_COUNT;
		if (primitiveIndex < primitiveCount)
		{
			uint packedTriangle = Triangles[meshlet.primitiveOffset + primitiveIndex];
			outTriangles[primitiveIndex] = uint3(packedTriangle & 0xFF, packedTriangle >> 8 & 0xFF, packedTriangle >> 16 & 0xFF);
		}
	}
}
