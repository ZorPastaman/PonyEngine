/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:CullMode;

import <cstdint>;

export namespace PonyEngine::Render
{
	enum class CullMode : std::uint8_t
	{
		None,
		Front,
		Back
	};
}
