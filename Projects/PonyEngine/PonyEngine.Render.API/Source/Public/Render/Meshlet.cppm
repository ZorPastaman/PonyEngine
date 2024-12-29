/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Meshlet;

import <cstdint>;

export namespace PonyEngine::Render
{
	struct Meshlet final
	{
		std::uint32_t vertexOffset;
		std::uint32_t vertexCount;
		std::uint32_t primitiveOffset;
		std::uint32_t primitiveCount;
	};
}
