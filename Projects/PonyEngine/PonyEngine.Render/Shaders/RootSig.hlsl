/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// CPU:
// 0: MVP matrix
// 1: Meshlets, Vertex indices and Triangles
// 2: Positions
// 3: Colors

// GPU:
// b0: MVP matrix
// t0: Meshlets
// t1: Vertex indices
// t2: Triangles
// t3: Positions
// t4: Colors

#define ROOT_SIG \
	"RootConstants(num32BitConstants=16, b0), " \
	"DescriptorTable(SRV(t0, numDescriptors = 3)) , " \
	"DescriptorTable(SRV(t3, numDescriptors = 1)), " \
	"DescriptorTable(SRV(t4, numDescriptors = 1))"
