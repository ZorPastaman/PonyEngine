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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"
#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:EngineUtility;

import std;

import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :D3D12Utility;

export namespace PonyEngine::RenderDevice::Windows
{
	[[nodiscard("Pure function")]]
	constexpr bool IsValidUsage(TextureUsage usage) noexcept;
	[[nodiscard("Pure function")]]
	constexpr bool CheckColorSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	[[nodiscard("Pure function")]]
	constexpr bool CheckDepthSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_FORMAT_SUPPORT1 ToFormatSupport(TextureDimension dimension) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_FORMAT_SUPPORT1 ToFormatSupport(TextureUsage usage) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_PROPERTIES ToHeapProperties(HeapType heapType) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_FLAGS ToHeapFlags(BufferUsage usage) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_FLAGS ToHeapFlags(TextureUsage usage) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const BufferParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const TextureParams& params, DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DIMENSION ToResourceDimension(TextureDimension dimension) noexcept;
	[[nodiscard("Pure function")]]
	constexpr UINT16 ToDepthArraySize(const TextureParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(BufferUsage usage) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(TextureUsage usage) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_BARRIER_LAYOUT ToLayout(Layout layout) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_CLEAR_VALUE ToClearValue(const ClearValue& clearValue, DXGI_FORMAT format) noexcept;

	[[nodiscard("Pure function")]]
	constexpr TextureFormatFeature ToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;

	[[nodiscard("Pure function")]]
	constexpr DXGI_SWAP_CHAIN_DESC1 ToSwapChainDesc(const SwapChainParams& params, DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_USAGE ToUsage(TextureUsage usage) noexcept;
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
	constexpr bool IsValidUsage(const TextureUsage usage) noexcept
	{
		if (Any(TextureUsage::DepthStencil, usage) && Any(TextureUsage::RenderTarget | TextureUsage::UnorderedAccess, usage))
		{
			return false;
		}

		return true;
	}

	constexpr bool CheckColorSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::DepthStencil, request.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = ToFormatSupport(request.dimension) | ToFormatSupport(request.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	constexpr bool CheckDepthSupport(const TextureSupportRequest& request, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::RenderTarget, request.usage))
		{
			return false;
		}
		if (Any(TextureUsage::UnorderedAccess, request.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = ToFormatSupport(request.dimension) | ToFormatSupport(request.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	constexpr D3D12_FORMAT_SUPPORT1 ToFormatSupport(const TextureDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureDimension::Texture1D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE1D;
		case TextureDimension::Texture2D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE2D;
		case TextureDimension::Texture3D:
			return D3D12_FORMAT_SUPPORT1_TEXTURE3D;
		case TextureDimension::TextureCube:
			return D3D12_FORMAT_SUPPORT1_TEXTURECUBE;
		default:
			return D3D12_FORMAT_SUPPORT1_NONE;
		}
	}

	constexpr D3D12_FORMAT_SUPPORT1 ToFormatSupport(const TextureUsage usage) noexcept
	{
		D3D12_FORMAT_SUPPORT1 support = D3D12_FORMAT_SUPPORT1_NONE;
		if (Any(TextureUsage::RenderTarget, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_RENDER_TARGET;
		}
		if (Any(TextureUsage::DepthStencil, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL;
		}
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			support |= D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW;
		}

		return support;
	}

	constexpr D3D12_HEAP_PROPERTIES ToHeapProperties(const HeapType heapType) noexcept
	{
		auto properties = D3D12_HEAP_PROPERTIES
		{
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};

		switch (heapType)
		{
		case HeapType::Default:
			properties.Type = D3D12_HEAP_TYPE_DEFAULT;
			break;
		case HeapType::Upload:
			properties.Type = D3D12_HEAP_TYPE_UPLOAD;
			break;
		case HeapType::Download:
			properties.Type = D3D12_HEAP_TYPE_READBACK;
			break;
		default: [[unlikely]]
			assert(false && "Invalid heap type.");
			properties.Type = D3D12_HEAP_TYPE_CUSTOM;
		}

		return properties;
	}

	constexpr D3D12_HEAP_FLAGS ToHeapFlags(const BufferUsage usage) noexcept
	{
		auto flags = D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
		if (Any(BufferUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
		}

		return flags;
	}

	constexpr D3D12_HEAP_FLAGS ToHeapFlags(const TextureUsage usage) noexcept
	{
		auto flags = D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
		}

		return flags;
	}

	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const BufferParams& params) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0ull,
			.Width = static_cast<UINT64>(params.size),
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = ToResourceFlags(params.usage),
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	constexpr D3D12_RESOURCE_DESC1 ToResourceDesc(const TextureParams& params, const DXGI_FORMAT format) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = ToResourceDimension(params.dimension),
			.Alignment = 0ull,
			.Width = static_cast<UINT64>(params.size.X()),
			.Height = static_cast<UINT>(params.size.Y()),
			.DepthOrArraySize = ToDepthArraySize(params),
			.MipLevels = static_cast<UINT16>(params.mipCount),
			.Format = format,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = static_cast<UINT>(ToNumber(params.sampleCount)), .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
			.Flags = ToResourceFlags(params.usage),
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	constexpr D3D12_RESOURCE_DIMENSION ToResourceDimension(const TextureDimension dimension) noexcept
	{
		switch (dimension)
		{
		case TextureDimension::Texture1D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case TextureDimension::Texture2D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		case TextureDimension::Texture3D:
			return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
		case TextureDimension::TextureCube:
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		default: [[unlikely]]
			assert(false && "Invalid dimension.");
			return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		}
	}

	constexpr UINT16 ToDepthArraySize(const TextureParams& params) noexcept
	{
		switch (params.dimension)
		{
		case TextureDimension::Texture3D:
			return static_cast<UINT16>(params.size.Z());
		case TextureDimension::TextureCube:
			return static_cast<UINT16>(params.arraySize * std::to_underlying(Face::Count));
		default:
			return static_cast<UINT16>(params.arraySize);
		}
	}

	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(const BufferUsage usage) noexcept
	{
		return Any(BufferUsage::UnorderedAccess, usage) ? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS : D3D12_RESOURCE_FLAG_NONE;
	}

	constexpr D3D12_RESOURCE_FLAGS ToResourceFlags(const TextureUsage usage) noexcept
	{
		auto flags = D3D12_RESOURCE_FLAG_NONE;
		if (Any(TextureUsage::RenderTarget, usage))
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		}
		if (Any(TextureUsage::DepthStencil, usage))
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		}
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		}
		if (usage == TextureUsage::DepthStencil)
		{
			flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
		}

		return flags;
	}

	constexpr D3D12_BARRIER_LAYOUT ToLayout(const Layout layout) noexcept
	{
		switch (layout)
		{
		case Layout::Common:
			return D3D12_BARRIER_LAYOUT_COMMON;
		case Layout::Present:
			return D3D12_BARRIER_LAYOUT_PRESENT;
		case Layout::ShaderResource:
			return D3D12_BARRIER_LAYOUT_SHADER_RESOURCE;
		case Layout::RenderTarget:
			return D3D12_BARRIER_LAYOUT_RENDER_TARGET;
		case Layout::DepthStencilRead:
			return D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_READ;
		case Layout::DepthStencilWrite:
			return D3D12_BARRIER_LAYOUT_DEPTH_STENCIL_WRITE;
		case Layout::UnorderedAccess:
			return D3D12_BARRIER_LAYOUT_UNORDERED_ACCESS;
		case Layout::CopySource:
			return D3D12_BARRIER_LAYOUT_COPY_SOURCE;
		case Layout::CopyDestination:
			return D3D12_BARRIER_LAYOUT_COPY_DEST;
		case Layout::ResolveSource:
			return D3D12_BARRIER_LAYOUT_RESOLVE_SOURCE;
		case Layout::ResolveDestination:
			return D3D12_BARRIER_LAYOUT_RESOLVE_DEST;
		default: [[unlikely]]
			assert(false && "Invalid layout");
			return D3D12_BARRIER_LAYOUT_COMMON;
		}
	}

	constexpr D3D12_CLEAR_VALUE ToClearValue(const ClearValue& clearValue, const DXGI_FORMAT format) noexcept
	{
		auto clear = D3D12_CLEAR_VALUE
		{
			.Format = format,
		};
		std::visit(Type::Overload
		{
			[&](const NoClear) noexcept
			{
				clear.Format = DXGI_FORMAT_UNKNOWN;
			},
			[&](const Math::ColorRGBA<float>& color) noexcept
			{
				for (std::size_t i = 0uz; i < color.ChannelCount; ++i)
				{
					clear.Color[i] = static_cast<FLOAT>(color[i]);
				}
			},
			[&](const DepthStencil& depthStencil) noexcept
			{
				clear.DepthStencil.Depth = static_cast<FLOAT>(depthStencil.depth);
				clear.DepthStencil.Stencil = static_cast<UINT8>(depthStencil.stencil);
			}
		}, clearValue);

		return clear;
	}

	constexpr TextureFormatFeature ToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto features = TextureFormatFeature::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_LOAD)
		{
			features |= TextureFormatFeature::ShaderLoad;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE)
		{
			features |= TextureFormatFeature::ShaderSample;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON)
		{
			features |= TextureFormatFeature::ShaderSampleComparison;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER)
		{
			features |= TextureFormatFeature::ShaderGather;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON)
		{
			features |= TextureFormatFeature::ShaderGatherComparison;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET)
		{
			features |= TextureFormatFeature::RenderTarget;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_BLENDABLE)
		{
			features |= TextureFormatFeature::Blendable;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP)
		{
			features |= TextureFormatFeature::LogicBlendable;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL)
		{
			features |= TextureFormatFeature::DepthStencil;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW)
		{
			features |= TextureFormatFeature::UnorderedAccess;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicAdd;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicBitwise;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicExchange;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicExchangeComparison;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicSignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicUnsignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD)
		{
			features |= TextureFormatFeature::UnorderedAccessLoad;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE)
		{
			features |= TextureFormatFeature::UnorderedAccessStore;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_DISPLAY)
		{
			features |= TextureFormatFeature::SwapChain;
		}
		if (GetSrgbFormat(support.Format) != DXGI_FORMAT_UNKNOWN)
		{
			features |= TextureFormatFeature::SRGB;
		}

		return features;
	}

	constexpr DXGI_SWAP_CHAIN_DESC1 ToSwapChainDesc(const SwapChainParams& params, const DXGI_FORMAT format) noexcept
	{
		return DXGI_SWAP_CHAIN_DESC1
		{
			.Width = params.size ? static_cast<UINT>(params.size->X()) : 0u,
			.Height = params.size ? static_cast<UINT>(params.size->Y()) : 0u,
			.Format = format,
			.Stereo = FALSE,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.BufferUsage = ToUsage(params.usage),
			.BufferCount = static_cast<UINT>(params.bufferCount),
			.Scaling = ToScaling(params.scalingMode),
			.SwapEffect = ToSwapEffect(params.swapEffect),
			.AlphaMode = ToAlphaMode(params.alphaMode),
			.Flags = ToSwapChainFlags(params.syncMode)
		};
	}

	constexpr DXGI_USAGE ToUsage(const TextureUsage usage) noexcept
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
