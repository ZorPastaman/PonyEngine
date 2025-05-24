/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyShader/Core/Context.hlsli"
#include "PonyShader/Mesh/Meshlet.hlsli"
#include "PonyShader/Mesh/Primitive.hlsli"
#include "PonyShader/Space/Transform.hlsli"

#define TRIANGLE_MULTIPLIER 2
#define VERTEX_COUNT 64
#define TRIANGLE_COUNT VERTEX_COUNT * TRIANGLE_MULTIPLIER
#define THREAD_COUNT_X VERTEX_COUNT
#define THREAD_COUNT_Y 1
#define THREAD_COUNT_Z 1

struct Vertex
{
	float4 clipPosition : SV_POSITION;
	float3 position : TEXCOORD0;
};

ConstantBuffer<Pony_Context> Context : register(b0);
ConstantBuffer<Pony_Transform> Transform : register(b1);

StructuredBuffer<Pony_Meshlet> Meshlets : register(t0);
StructuredBuffer<uint> VertexIndices : register(t1);
StructuredBuffer<Pony_Primitive> Primitives : register(t2);
StructuredBuffer<float3> Positions : register(t3);

Vertex CreateVertex(in uint index)
{
	Vertex vertex;
	vertex.clipPosition = mul(Transform.mvp, float4(Positions[index], 1.f));
	vertex.position = vertex.clipPosition.xyz / vertex.clipPosition.w;

	return vertex;
}

[OutputTopology("triangle")]
[NumThreads(THREAD_COUNT_X, THREAD_COUNT_Y, THREAD_COUNT_Z)]
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
			outTriangles[groupThreadSubId] = UnpackTriangle(Primitives[primitiveIndex], Context.isFlipped);
		}
	}
}
