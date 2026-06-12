/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Ext:ResourceReference;

import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	struct ResourceReference final
	{
		const FileReference* fileReference = nullptr;
		const MemoryReference* memoryReference = nullptr;
	};
}
