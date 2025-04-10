/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderSystemParams;

import <optional>;

import PonyMath.Utility;

import :MSAAParams;

export namespace PonyEngine::Render
{
	/// @brief Render system parameters.
	struct RenderSystemParams
	{
		std::optional<PonyMath::Utility::Resolution<std::uint32_t>> resolution;
		std::uint32_t bufferCount = 3u; ///< Buffer count.
		MSAAParams msaaParams;
	};
}
