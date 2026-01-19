/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureIndex;

import std;

export namespace PonyEngine::RenderDevice
{
	struct SubTextureIndex final
	{
		std::uint32_t mipIndex = 0u;
		std::uint32_t arrayIndex = 0u;
		std::uint8_t planeIndex = 0u;
	};
}
