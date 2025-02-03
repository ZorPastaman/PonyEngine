/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyShader/Core/Context.hlsli"
#include "PonyShader/Space/Transform.hlsli"

#include "Payload.hlsli"

ConstantBuffer<Pony_Context> Context : register(b0);
ConstantBuffer<Pony_Transform> Transform : register(b1);

[numthreads(1, 1, 1)]
void main()
{
	Payload payload;
	payload.isFlipped = determinant(Transform.mvpMatrix) < 0.f;

	DispatchMesh(Context.meshThreadGroupCounts.counts[0], Context.meshThreadGroupCounts.counts[1], Context.meshThreadGroupCounts.counts[2], payload);
}
