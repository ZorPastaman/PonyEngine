/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DSVDimension;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class DSVDimension : std::uint8_t
	{
		Texture1D,
		Texture2D
	};
}
