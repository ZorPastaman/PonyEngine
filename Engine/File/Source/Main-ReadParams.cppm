/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File:ReadParams;

import std;

export namespace PonyEngine::File
{
	struct ReadParams final
	{
		std::span<std::byte> buffer;
		std::size_t offset = 0uz;
	};
}
