/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Core.hlsli"
#include "PonyEngine/Meshlet.hlsli"
#include "PonyEngine/Transform.hlsli"

#ifndef VERTEX_COUNT
#define VERTEX_COUNT 64
#endif
#ifndef TRIANGLE_MULTIPLIER
#define TRIANGLE_MULTIPLIER 2
#endif
#define TRIANGLE_COUNT VERTEX_COUNT * TRIANGLE_MULTIPLIER

#ifndef CONTEXT_SET
#define CONTEXT_SET 0
#endif
#ifndef MESHLET_SET
#define MESHLET_SET 1
#endif
#ifndef VERTEX_SET
#define VERTEX_SET 2
#endif

struct Vertex
{
	float4 clipPosition : SV_POSITION;
	float3 position : TEXCOORD0;
};

ConstantBuffer<Pony_Transform> Transform : PONY_CBV_REGISTER(CONTEXT_SET, 0);

StructuredBuffer<Pony_Meshlet> Meshlets : PONY_SRV_REGISTER(MESHLET_SET, 0);
StructuredBuffer<uint> VertexIndices : PONY_SRV_REGISTER(MESHLET_SET, 1);
ByteAddressBuffer Primitives : PONY_SRV_REGISTER(MESHLET_SET, 2);

StructuredBuffer<float3> Positions : PONY_SRV_REGISTER(VERTEX_SET, 0);

Vertex CreateVertex(in uint index)
{
	Vertex vertex;
	vertex.clipPosition = mul(Transform.mvp, float4(Positions[index], 1.f));
	vertex.position = vertex.clipPosition.xyz / vertex.clipPosition.w;

	return vertex;
}

[OutputTopology("triangle")]
[NumThreads(VERTEX_COUNT, 1, 1)]
void main(in uint groupId : SV_GROUPID,
	in uint groupThreadId : SV_GROUPTHREADID,
	out vertices Vertex outVertices[VERTEX_COUNT],
	out indices uint3 outTriangles[TRIANGLE_COUNT])
{
	Pony_Meshlet meshlet = Meshlets[groupId];
	uint vertexCount = UnpackVertexCount(meshlet);
	uint primitiveCount = UnpackPrimitiveCount(meshlet);
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
			outTriangles[groupThreadSubId] = UnpackTriangle(Primitives, primitiveIndex, Transform.mvpDet < 0.f);
		}
	}
}
