/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderTargetParams;

import <cstdint>;
import <optional>;

import PonyMath.Color;
import PonyMath.Utility;

import :MSAAParams;

export namespace PonyEngine::Render
{
	/// @brief Render target parameters.
	struct RenderTargetParams final
	{
		std::optional<PonyMath::Utility::Resolution<std::uint32_t>> resolution = {}; ///< Render resolution. If it's @a nullopt, the render resolution will be the same as a window resolution.
		PonyMath::Color::RGBA<float> clearColor = PonyMath::Color::RGBA<float>::Predefined::Black; ///< Clear color.
		MSAAParams msaaParams = MSAAParams{.sampleCount = 1u, .sampleQuality = 0.f}; ///< MSAA parameters.
	};
}
