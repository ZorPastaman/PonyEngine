/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:ClearValue;

import <cstdint>;
import <optional>;

import PonyMath.Color;

import :Common;

export namespace PonyEngine::Render
{
	/// @brief Clear value.
	struct ClearValue final
	{
		std::optional<PonyMath::Color::RGBA<float>> color = PonyMath::Color::RGBA<float>::Predefined::Black; ///< Clear color. std::nullopt means no color clearing.
		std::optional<float> depth = MaxDepth; ///< Clear depth. std::nullopt means no depth clearing.
		std::optional<std::uint8_t> stencil = 0u; ///< Clear stencil. std::nullopt means no stencil clearing.
	};
}
