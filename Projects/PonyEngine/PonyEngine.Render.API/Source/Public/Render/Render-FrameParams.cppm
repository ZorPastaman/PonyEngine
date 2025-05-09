/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:FrameParams;

import <cstdint>;
import <optional>;

import PonyMath.Color;
import PonyMath.Utility;

import :MSAA;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Frame parameters.
	struct FrameParams final
	{
		std::optional<PonyMath::Utility::Resolution<std::uint32_t>> resolution = std::nullopt; ///< Resolution. If it's std::nullopt, uses the swap chain's resolution.
		MSAA msaa = MSAA{.sampleCount = 1u, .sampleQuality = 1.f}; ///< Multi-sample anti-aliasing parameters.
		PonyMath::Color::RGBA<float> clearColor = PonyMath::Color::RGBA<float>::Predefined::Black; ///< Clear color.
		float clearDepth = 1.f; ///< Clear depth.
		std::uint8_t clearStencil = 0u; ///< Clear stencil.
		TextureFormat rtvFormat = TextureFormat::R8G8B8A8_Unorm; ///< Render target view format. If it's unknown, the render target won't be created.
		TextureFormat dsvFormat = TextureFormat::D32_Float_S8X24_Uint; ///< Depth stencil view format. Must be a depth stencil format. If it's unknown, the depth stencil won't be created.
	};
}
