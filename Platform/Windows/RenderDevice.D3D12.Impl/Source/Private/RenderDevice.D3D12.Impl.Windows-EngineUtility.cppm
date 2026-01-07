/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"
#include "PonyEngine/Render/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:EngineUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::Render::Windows
{
	[[nodiscard("Pure function")]]
	bool IsValidUsage(TextureUsage usage) noexcept;
	[[nodiscard("Pure function")]]
	bool CheckColorSupport(const TextureSupportRequest& supportRequest, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	[[nodiscard("Pure function")]]
	bool CheckDepthSupport(const TextureSupportRequest& supportRequest, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;

	[[nodiscard("Pure function")]]
	D3D12_FORMAT_SUPPORT1 TextureDimensionToFormatSupport(TextureDimension dimension) noexcept;
	[[nodiscard("Pure function")]]
	D3D12_FORMAT_SUPPORT1 TextureUsageToFormatSupport(TextureUsage usage) noexcept;

	[[nodiscard("Pure function")]]
	TextureFormatFeature FormatSupportToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
}

namespace PonyEngine::Render::Windows
{
	bool IsValidUsage(const TextureUsage usage) noexcept
	{
		if (Any(TextureUsage::DepthStencil, usage) && Any(TextureUsage::RenderTarget | TextureUsage::UnorderedAccess, usage))
		{
			return false;
		}

		return true;
	}

	bool CheckColorSupport(const TextureSupportRequest& supportRequest, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::DepthStencil, supportRequest.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = TextureDimensionToFormatSupport(supportRequest.dimension) | TextureUsageToFormatSupport(supportRequest.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	bool CheckDepthSupport(const TextureSupportRequest& supportRequest, const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		if (Any(TextureUsage::RenderTarget, supportRequest.usage))
		{
			return false;
		}
		if (Any(TextureUsage::UnorderedAccess, supportRequest.usage))
		{
			return false;
		}
		const D3D12_FORMAT_SUPPORT1 requiredSupport = TextureDimensionToFormatSupport(supportRequest.dimension) | TextureUsageToFormatSupport(supportRequest.usage);
		if ((requiredSupport & support.Support1) != requiredSupport)
		{
			return false;
		}

		return true;
	}

	D3D12_FORMAT_SUPPORT1 TextureDimensionToFormatSupport(const TextureDimension dimension) noexcept
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

	D3D12_FORMAT_SUPPORT1 TextureUsageToFormatSupport(const TextureUsage usage) noexcept
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

	TextureFormatFeature FormatSupportToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
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

		return features;
	}
}
