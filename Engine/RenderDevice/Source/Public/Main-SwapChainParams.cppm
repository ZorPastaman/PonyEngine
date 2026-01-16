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
	struct SwapChainParams final
	{
		TextureFormatId format;
		std::optional<Math::Vector2<std::uint32_t>> size;
		std::uint8_t bufferCount = 3;
		SwapChainAlphaMode alphaMode = SwapChainAlphaMode::Ignore;
		SwapChainScaling scalingMode = SwapChainScaling::NoScaling;
		SwapChainEffect swapEffect = SwapChainEffect::FlipSequential;
		SwapChainSync syncMode = SwapChainSync::FullSync;
		SwapChainFlag flags = SwapChainFlag::None;
		TextureUsage usage = TextureUsage::RenderTarget;
	};
}
