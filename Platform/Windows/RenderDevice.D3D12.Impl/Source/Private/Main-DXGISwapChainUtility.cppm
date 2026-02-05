/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:DXGISwapChainUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Windows
{
	[[nodiscard("Pure function")]]
	constexpr DXGI_SWAP_CHAIN_DESC1 ToSwapChainDesc(const SwapChainParams& params, DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_USAGE ToDXGIUsage(TextureUsage usage) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_SCALING ToScaling(SwapChainScaling scaling) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_SWAP_EFFECT ToSwapEffect(SwapChainEffect effect) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_ALPHA_MODE ToAlphaMode(SwapChainAlphaMode alphaMode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr UINT ToSwapChainFlags(SwapChainSync syncMode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr UINT ToSyncInterval(SwapChainSync syncMode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr UINT ToPresentFlags(SwapChainSync syncMode) noexcept;

	[[nodiscard("Pure function")]]
	constexpr SwapChainSyncMask ToSyncMode(BOOL tearingSupported) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
{
	constexpr DXGI_SWAP_CHAIN_DESC1 ToSwapChainDesc(const SwapChainParams& params, const DXGI_FORMAT format) noexcept
	{
		return DXGI_SWAP_CHAIN_DESC1
		{
			.Width = params.size ? static_cast<UINT>(params.size->X()) : 0u,
			.Height = params.size ? static_cast<UINT>(params.size->Y()) : 0u,
			.Format = format,
			.Stereo = false,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.BufferUsage = ToDXGIUsage(params.usage),
			.BufferCount = static_cast<UINT>(params.bufferCount),
			.Scaling = ToScaling(params.scalingMode),
			.SwapEffect = ToSwapEffect(params.swapEffect),
			.AlphaMode = ToAlphaMode(params.alphaMode),
			.Flags = ToSwapChainFlags(params.syncMode)
		};
	}

	constexpr DXGI_USAGE ToDXGIUsage(const TextureUsage usage) noexcept
	{
		DXGI_USAGE answer = 0;
		if (Any(TextureUsage::ShaderResource, usage))
		{
			answer |= DXGI_USAGE_SHADER_INPUT;
		}
		if (Any(TextureUsage::RenderTarget, usage))
		{
			answer |= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		}
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			answer |= DXGI_USAGE_UNORDERED_ACCESS;
		}

		return answer;
	}

	constexpr DXGI_SCALING ToScaling(const SwapChainScaling scaling) noexcept
	{
		switch (scaling)
		{
		case SwapChainScaling::NoScaling:
			return DXGI_SCALING_NONE;
		case SwapChainScaling::Stretch:
			return DXGI_SCALING_STRETCH;
		case SwapChainScaling::StretchAspectRatio:
			return DXGI_SCALING_ASPECT_RATIO_STRETCH;
		default: [[unlikely]]
			assert(false && "Invalid scaling.");
			return DXGI_SCALING_NONE;
		}
	}

	constexpr DXGI_SWAP_EFFECT ToSwapEffect(const SwapChainEffect effect) noexcept
	{
		switch (effect)
		{
		case SwapChainEffect::FlipDiscard:
			return DXGI_SWAP_EFFECT_FLIP_DISCARD;
		case SwapChainEffect::FlipSequential:
			return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		default: [[unlikely]]
			assert(false && "Invalid effect.");
			return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		}
	}

	constexpr DXGI_ALPHA_MODE ToAlphaMode(const SwapChainAlphaMode alphaMode) noexcept
	{
		switch (alphaMode)
		{
		case SwapChainAlphaMode::Ignore:
			return DXGI_ALPHA_MODE_IGNORE;
		case SwapChainAlphaMode::Straight:
			return DXGI_ALPHA_MODE_STRAIGHT;
		case SwapChainAlphaMode::Premultiplied:
			return DXGI_ALPHA_MODE_PREMULTIPLIED;
		default: [[unlikely]]
			assert(false && "Invalid alpha mode.");
			return DXGI_ALPHA_MODE_IGNORE;
		}
	}

	constexpr UINT ToSwapChainFlags(const SwapChainSync syncMode) noexcept
	{
		return syncMode == SwapChainSync::NoSync
			? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
			: 0u;
	}

	constexpr UINT ToSyncInterval(const SwapChainSync syncMode) noexcept
	{
		switch (syncMode)
		{
		case SwapChainSync::NoSync:
		case SwapChainSync::FastSync:
			return 0u;
		case SwapChainSync::FullSync:
			return 1u;
		case SwapChainSync::FullSyncHalf:
			return 2u;
		case SwapChainSync::FullSyncThird:
			return 3u;
		case SwapChainSync::FullSyncFourth:
			return 4u;
		default: [[unlikely]]
			assert(false && "Invalid sync mode");
			return 1u;
		}
	}

	constexpr UINT ToPresentFlags(const SwapChainSync syncMode) noexcept
	{
		return syncMode == SwapChainSync::NoSync
			? DXGI_PRESENT_ALLOW_TEARING
			: 0u;
	}

	constexpr SwapChainSyncMask ToSyncMode(const BOOL tearingSupported) noexcept
	{
		auto syncMode = SwapChainSyncMask::FastSync | SwapChainSyncMask::FullSync | 
			SwapChainSyncMask::FullSyncHalf | SwapChainSyncMask::FullSyncThird | SwapChainSyncMask::FullSyncFourth;
		if (tearingSupported)
		{
			syncMode |= SwapChainSyncMask::NoSync;
		}

		return syncMode;
	}
}
