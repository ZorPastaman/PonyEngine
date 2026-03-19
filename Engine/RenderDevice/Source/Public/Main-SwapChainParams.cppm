/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SwapChainParams;

import std;

import PonyEngine.Math;

import :SwapChainAlphaMode;
import :SwapChainEffect;
import :SwapChainFlag;
import :SwapChainScaling;
import :SwapChainSync;
import :TextureFormatId;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain parameters.
	struct SwapChainParams final
	{
		TextureFormatId format; ///< Texture format.
		std::optional<Math::Vector2<std::uint32_t>> size; ///< Swap chain size. Nullopt means to take a surface size.
		std::uint8_t bufferCount = 3; ///< Swap chain buffer count.
		SwapChainAlphaMode alphaMode = SwapChainAlphaMode::Ignore; ///< Alpha mode.
		SwapChainScaling scalingMode = SwapChainScaling::NoScaling; ///< Scaling mode.
		SwapChainEffect swapEffect = SwapChainEffect::FlipSequential; ///< Swap effect.
		SwapChainSync syncMode = SwapChainSync::FullSync; ///< Sync mode.
		SwapChainFlag flags = SwapChainFlag::None; ///< Swap chain flags.
		TextureUsage usage = TextureUsage::RenderTarget; ///< Swap chain buffer usage.
	};
}
