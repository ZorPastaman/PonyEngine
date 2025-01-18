/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:ResourcePlacement;

import <cstdint>;

export namespace PonyEngine::Render::Direct3D12
{
	enum class ResourcePlacement : std::uint8_t
	{
		CPU,
		GPU
	};
}
