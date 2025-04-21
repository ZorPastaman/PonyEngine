/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderQueue;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Render queue default values.
	enum class RenderQueue : std::int32_t
	{
		Opaque = 0 * 100000,
		Skybox = 1 * 100000,
		Transparent = 2 * 100000,
		Overlay = 5 * 100000
	};
}
