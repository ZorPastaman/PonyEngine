/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// CPU:
// 0: Context, Transform
// 1: Meshlets, Vertex indices and Primitives
// 2: Positions
// 3: Color

// GPU:
// b0: Context
// b1: Transform
// t0: Meshlets
// t1: Vertex indices
// t2: Primitives
// t3: Positions
// t4: Color

#define ROOT_SIG \
	"DescriptorTable(CBV(b0, numDescriptors = 2)), " \
	"DescriptorTable(SRV(t0, numDescriptors = 3)), " \
	"DescriptorTable(SRV(t3, numDescriptors = 1)), " \
	"DescriptorTable(SRV(t4, numDescriptors = 1))"
