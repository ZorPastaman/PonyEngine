/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#define VERTEX_COUNT 4
#define TRIANGLE_COUNT 2
#define THREAD_COUNT_X VERTEX_COUNT
#define THREAD_COUNT_Y 1
#define THREAD_COUNT_Z 1

struct Vertex
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

static const float4 QuadVertices[] =
{
	float4(-1.f, -1.f, 0.f, 1.f),
	float4(1.f, -1.f, 0.f, 1.f),
	float4(1.f, 1.f, 0.f, 1.f),
	float4(-1.f, 1.f, 0.f, 1.f)
};

static const float2 QuadUvs[] =
{
	float2(0.f, 1.f),
	float2(1.f, 1.f),
	float2(1.f, 0.f),
	float2(0.f, 0.f)
};

static const uint3 QuadTriangles[] =
{
	uint3(0u, 1u, 2u),
	uint3(0u, 2u, 3u)
};

[OutputTopology("triangle")]
[NumThreads(THREAD_COUNT_X, THREAD_COUNT_Y, THREAD_COUNT_Z)]
void main(in uint groupThreadId : SV_GROUPTHREADID, 
	out vertices Vertex outVertices[VERTEX_COUNT],
	out indices uint3 outTriangles[TRIANGLE_COUNT])
{
	SetMeshOutputCounts(VERTEX_COUNT, TRIANGLE_COUNT);

	Vertex vertex;
	vertex.position = QuadVertices[groupThreadId];
	vertex.uv = QuadUvs[groupThreadId];
	outVertices[groupThreadId] = vertex;

	if (groupThreadId < TRIANGLE_COUNT)
	{
		outTriangles[groupThreadId] = QuadTriangles[groupThreadId];
	}
}
