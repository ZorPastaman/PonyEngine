/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Core:Context;

import <cstdint>;

import :ThreadGroupCounts;

export namespace PonyShader::Core
{
	struct Context final
	{
		ThreadGroupCounts dispatchThreadGroupCounts;
		ThreadGroupCounts materialThreadGroupCounts;
		ThreadGroupCounts meshThreadGroupCounts;
		std::int32_t renderQueue;
		std::uint32_t isTransparent;
		std::uint32_t isFlipped;
	};;
}
