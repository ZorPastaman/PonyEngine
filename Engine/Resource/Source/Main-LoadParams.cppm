/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:LoadParams;

import std;

export namespace PonyEngine::Resource
{
	struct LoadParams final
	{
		std::span<std::byte> buffer;
		std::size_t offset;
	};
}
