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
	struct SwapChainSupport final
	{
		Math::Vector2<std::uint32_t> maxSize = Math::Vector2<std::uint32_t>::Zero();
		std::uint8_t minBufferCount = 0u;
		std::uint8_t maxBufferCount = 0u;
		SwapChainAlphaModeMask alphaModes = SwapChainAlphaModeMask::None;
		SwapChainScalingMask scalingModes = SwapChainScalingMask::None;
		SwapChainEffectMask swapEffects = SwapChainEffectMask::None;
		SwapChainSyncMask syncModes = SwapChainSyncMask::None;
		TextureUsage usage = TextureUsage::None;
	};
}
