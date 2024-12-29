/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Primitive;

import <array>;
import <cstdint>;

export namespace PonyEngine::Render
{
	struct Primitive final
	{
		std::array<std::uint8_t, 4> indices;
	};
}

