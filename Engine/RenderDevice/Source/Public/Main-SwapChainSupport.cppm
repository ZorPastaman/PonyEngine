/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SwapChainSupport;

import std;

import PonyEngine.Math;

import :SwapChainAlphaMode;
import :SwapChainEffect;
import :SwapChainScaling;
import :SwapChainSync;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain support.
	struct SwapChainSupport final
	{
		Math::Vector2<std::uint32_t> maxSize = Math::Vector2<std::uint32_t>::Zero(); ///< Maximum swap chain buffer size.
		std::uint8_t minBufferCount = 0u; ///< Minimal buffer count.
		std::uint8_t maxBufferCount = 0u; ///< Maximal buffer count.
		SwapChainAlphaModeMask alphaModes = SwapChainAlphaModeMask::None; ///< Supported alpha modes.
		SwapChainScalingMask scalingModes = SwapChainScalingMask::None; ///< Supported scaling modes.
		SwapChainEffectMask swapEffects = SwapChainEffectMask::None; ///< Supported swap effects.
		SwapChainSyncMask syncModes = SwapChainSyncMask::None; ///< Supported sync modes.
		TextureUsage usage = TextureUsage::None; ///< Supported texture usages.
	};
}
