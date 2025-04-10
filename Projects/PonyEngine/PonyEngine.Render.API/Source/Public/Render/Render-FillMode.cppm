/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:FillMode;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Fill mode.
	enum class FillMode : std::uint8_t
	{
		Solid,
		Wireframe
	};
}
