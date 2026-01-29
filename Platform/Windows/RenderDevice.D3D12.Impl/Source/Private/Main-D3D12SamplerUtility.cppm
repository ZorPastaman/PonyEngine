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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12SamplerUtility;

import std;

import PonyEngine.Math;
import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :D3D12Utility;

export namespace PonyEngine::RenderDevice::Windows
{
	[[nodiscard("Pure function")]]
	constexpr D3D12_SAMPLER_DESC2 ToSamplerDesc(const SamplerParams& params) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_FILTER_TYPE ToFilterType(Filter filter) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_TEXTURE_ADDRESS_MODE ToAddressMode(SamplerAddressMode mode) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_FILTER_REDUCTION_TYPE ToReduction(const Reduction& reduction, D3D12_COMPARISON_FUNC& comparisonFunc) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
{
	constexpr D3D12_SAMPLER_DESC2 ToSamplerDesc(const SamplerParams& params) noexcept
	{
		auto desc = D3D12_SAMPLER_DESC2
		{
			.AddressU = ToAddressMode(params.addressU),
			.AddressV = ToAddressMode(params.addressV),
			.AddressW = ToAddressMode(params.addressW),
			.MipLODBias = static_cast<FLOAT>(params.mipLodBias),
			.MinLOD = static_cast<FLOAT>(params.minLod),
			.MaxLOD = static_cast<FLOAT>(params.maxLod),
			.Flags = D3D12_SAMPLER_FLAG_NONE
		};

		std::visit(Type::Overload
		{
			[&](const BasicSamplerFilter& f) noexcept
			{
				const D3D12_FILTER_TYPE min = ToFilterType(f.min);
				const D3D12_FILTER_TYPE mag = ToFilterType(f.mag);
				const D3D12_FILTER_TYPE mip = ToFilterType(f.mip);
				const D3D12_FILTER_REDUCTION_TYPE reduction = ToReduction(f.reduction, desc.ComparisonFunc);
				desc.Filter = D3D12_ENCODE_BASIC_FILTER(min, mag, mip, reduction);
			},
			[&](const AnisotropicSamplerFilter& f) noexcept
			{
				const D3D12_FILTER_REDUCTION_TYPE reduction = ToReduction(f.reduction, desc.ComparisonFunc);
				desc.Filter = D3D12_ENCODE_ANISOTROPIC_FILTER(reduction);
				desc.MaxAnisotropy = std::clamp(Math::RoundToIntegral<UINT>(f.maxAnisotropy), UINT{1u}, UINT{D3D12_DEFAULT_MAX_ANISOTROPY});
			}
		}, params.filter);

		return desc;
	}

	constexpr D3D12_FILTER_TYPE ToFilterType(const Filter filter) noexcept
	{
		switch (filter)
		{
		case Filter::Nearest:
			return D3D12_FILTER_TYPE_POINT;
		case Filter::Linear:
			return D3D12_FILTER_TYPE_LINEAR;
		default: [[unlikely]]
			assert(false && "Invalid filter.");
			return D3D12_FILTER_TYPE_POINT;
		}
	}

	constexpr D3D12_TEXTURE_ADDRESS_MODE ToAddressMode(const SamplerAddressMode mode) noexcept
	{
		switch (mode)
		{
		case SamplerAddressMode::Wrap:
			return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		case SamplerAddressMode::Mirror:
			return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
		case SamplerAddressMode::Clamp:
			return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		default: [[unlikely]]
			assert(false && "Invalid sampler address mode.");
			return D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		}
	}

	constexpr D3D12_FILTER_REDUCTION_TYPE ToReduction(const Reduction& reduction, D3D12_COMPARISON_FUNC& comparisonFunc) noexcept
	{
		return std::visit(Type::Overload
		{
			[](const StandardReduction) noexcept
			{
				return D3D12_FILTER_REDUCTION_TYPE_STANDARD;
			},
			[&](const ComparisonReduction& r) noexcept
			{
				comparisonFunc = ToComparisonFunc(r.func);
				return D3D12_FILTER_REDUCTION_TYPE_COMPARISON;
			},
			[](const MinimumReduction) noexcept
			{
				return D3D12_FILTER_REDUCTION_TYPE_MINIMUM;
			},
			[](const MaximumReduction) noexcept
			{
				return D3D12_FILTER_REDUCTION_TYPE_MAXIMUM;
			}
		}, reduction);
	}
}
