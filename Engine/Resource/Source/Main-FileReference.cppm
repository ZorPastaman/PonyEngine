/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource:FileReference;

import std;

export namespace PonyEngine::Resource
{
	struct FileReference final
	{
		std::filesystem::path path;
		std::size_t offset;
		std::size_t size;
	};
}
