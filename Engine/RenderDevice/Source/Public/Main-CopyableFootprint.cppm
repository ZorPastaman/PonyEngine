/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CopyableFootprint;

import std;

import PonyEngine.Math;

export namespace PonyEngine::RenderDevice
{
	struct CopyableFootprint final
	{
		std::uint64_t offset;
		std::uint64_t rowSize;
		std::uint64_t rowPitch;
		std::uint32_t rowCount;
		std::uint32_t sliceCount;
	};
}
