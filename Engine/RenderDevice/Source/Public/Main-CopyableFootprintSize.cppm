/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CopyableFootprintSize;

import std;

export namespace PonyEngine::RenderDevice
{
	struct CopyableFootprintSize final
	{
		std::uint64_t sourceTotalSize;
		std::uint64_t destinationTotalSize;
	};
}
