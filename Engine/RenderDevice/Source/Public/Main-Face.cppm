/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:Face;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class Face : std::uint8_t
	{
		Right,
		Left,
		Up,
		Down,
		Forward,
		Back,
		Count
	};
}
