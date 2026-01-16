/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:HeapType;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class HeapType : std::uint8_t
	{
		Default,
		Upload,
		Download
	};
}
