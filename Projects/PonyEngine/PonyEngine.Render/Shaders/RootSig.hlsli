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
// 1: Meshlets
// 2: Vertex indices
// 3: Triangles
// 4: Positions
// 5: Colors

// GPU:
// b0: MVP matrix
// t0: Meshlets
// t1: Vertex indices
// t2: Triangles
// t3: Positions
// t4: Colors

#define ROOT_SIG \
	"RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT), " \
	"RootConstants(num32BitConstants=16, b0), " \
	"DescriptorTable(SRV(t0, numDescriptors = 1)) , " \
	"DescriptorTable(SRV(t1, numDescriptors = 1)) , " \
	"DescriptorTable(SRV(t2, numDescriptors = 1)) , " \
	"DescriptorTable(SRV(t3, numDescriptors = 1)), " \
	"DescriptorTable(SRV(t4, numDescriptors = 1))"
