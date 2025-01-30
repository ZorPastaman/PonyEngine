/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Shader/Types.hlsli"

#define TRIANGLE_MULTIPLIER 2
#define VERTEX_COUNT 64
#define TRIANGLE_COUNT VERTEX_COUNT * TRIANGLE_MULTIPLIER
#define THREAD_COUNT_X VERTEX_COUNT
#define THREAD_COUNT_Y 1
#define THREAD_COUNT_Z 1

struct Vertex
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

Pony_Transform Transform : register(b0);

StructuredBuffer<Pony_Meshlet> Meshlets : register(t0);
StructuredBuffer<uint> VertexIndices : register(t1);
StructuredBuffer<Pony_Primitive> Primitives : register(t2);
StructuredBuffer<float3> Positions : register(t3);
StructuredBuffer<float4> Colors : register(t4);

Vertex CreateVertex(in uint index)
{
	Vertex vertex;
	vertex.position = mul(Transform.mvpMatrix, float4(Positions[index], 1.f));
	vertex.color = Colors[index];

	return vertex;
}

uint3 CreateTriangle(in uint index)
{
	return UnpackTriangle(Primitives[index]);
}

[outputtopology("triangle")]
[numthreads(THREAD_COUNT_X, THREAD_COUNT_Y, THREAD_COUNT_Z)]
void main(in uint groupId : SV_GROUPID,
	in uint groupThreadId : SV_GROUPTHREADID,
	out vertices Vertex outVertices[VERTEX_COUNT],
	out indices uint3 outTriangles[TRIANGLE_COUNT])
{
	Pony_Meshlet meshlet = Meshlets[groupId];
	uint vertexCount = 0;
	uint primitiveCount = 0;
	UnpackMeshletCounts(meshlet, vertexCount, primitiveCount);
	SetMeshOutputCounts(vertexCount, primitiveCount);

	if (groupThreadId < vertexCount)
	{
		uint vertexIndex = VertexIndices[meshlet.vertexOffset + groupThreadId];
		outVertices[groupThreadId] = CreateVertex(vertexIndex);
	}

	[unroll]
	for (uint i = 0; i < TRIANGLE_MULTIPLIER; ++i)
	{
		uint groupThreadSubId = groupThreadId + i * VERTEX_COUNT;
		if (groupThreadSubId < primitiveCount)
		{
			uint primitiveIndex = meshlet.primitiveOffset + groupThreadSubId;
			outTriangles[groupThreadSubId] = CreateTriangle(primitiveIndex);
		}
	}
}
