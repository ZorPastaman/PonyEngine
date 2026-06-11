/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:MemoryReference;

import std;

export namespace PonyEngine::Resource
{
	struct MemoryReference final
	{
		std::span<const std::byte> buffer;
	};
}
