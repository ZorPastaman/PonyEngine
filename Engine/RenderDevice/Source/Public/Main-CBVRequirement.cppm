/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CBVRequirement;

import std;

export namespace PonyEngine::RenderDevice
{
	struct CBVRequirement final
	{
		std::uint32_t offsetAlignment = 0ull;
		std::uint32_t sizeAlignment = 0u;
	};
}
