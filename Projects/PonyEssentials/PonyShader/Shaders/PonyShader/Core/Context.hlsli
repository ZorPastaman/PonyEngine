/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "ThreadGroupCounts.hlsli"

struct Pony_Context
{
	Pony_ThreadGroupCounts dispatchThreadGroupCounts;
	Pony_ThreadGroupCounts materialThreadGroupCounts;
	Pony_ThreadGroupCounts meshThreadGroupCounts;
	int renderQueue;
	bool isTransparent;
	bool isFlipped;
};
