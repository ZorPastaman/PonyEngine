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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12RootSignatureUtility;

import std;

import PonyEngine.RenderDevice;

import :D3D12SamplerUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	struct RootSignatureDescCounts final
	{
		UINT tableCount = 0u;
		UINT rangeCount = 0u;
		UINT staticSamplerCount = 0u;
	};

	[[nodiscard("Pure function")]]
	constexpr RootSignatureDescCounts GetRootSignatureCounts(std::span<const DescriptorSet> descriptorSets) noexcept;

	[[nodiscard("Pure function")]]
	constexpr D3D12_ROOT_SIGNATURE_DESC2 ToRootSignatureDesc(const PipelineLayoutParams& params, std::span<D3D12_ROOT_PARAMETER1> parameters,
		std::span<D3D12_DESCRIPTOR_RANGE1> ranges, std::span<D3D12_STATIC_SAMPLER_DESC1> staticSamplers) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_RANGE_TYPE ToDescriptorRangeType(DescriptorType descriptorType) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_ROOT_SIGNATURE_FLAGS ToRootSignatureFlags(PipelineLayoutFlag flags) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
{
	constexpr RootSignatureDescCounts GetRootSignatureCounts(const std::span<const DescriptorSet> descriptorSets) noexcept
	{
		RootSignatureDescCounts counts;
		for (const DescriptorSet& set : descriptorSets)
		{
			counts.tableCount += set.ranges.size() > 0uz;
			counts.rangeCount += static_cast<UINT>(set.ranges.size());
			counts.staticSamplerCount += static_cast<UINT>(set.staticSamplers.size());
		}

		return counts;
	}

	constexpr D3D12_ROOT_SIGNATURE_DESC2 ToRootSignatureDesc(const PipelineLayoutParams& params, const std::span<D3D12_ROOT_PARAMETER1> parameters, 
		const std::span<D3D12_DESCRIPTOR_RANGE1> ranges, const std::span<D3D12_STATIC_SAMPLER_DESC1> staticSamplers) noexcept
	{
		for (std::size_t setIndex = 0uz, parameterIndex = 0uz, rangeIndex = 0uz, staticSamplerIndex = 0uz; 
			setIndex < params.descriptorSets.size(); ++setIndex)
		{
			const DescriptorSet& set = params.descriptorSets[setIndex];
			const UINT registerSpace = static_cast<UINT>(setIndex);
			
			if (set.ranges.size() > 0uz)
			{
				parameters[parameterIndex++] = D3D12_ROOT_PARAMETER1
				{
					.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
					.DescriptorTable = D3D12_ROOT_DESCRIPTOR_TABLE1
					{
						.NumDescriptorRanges = static_cast<UINT>(set.ranges.size()),
						.pDescriptorRanges = &ranges[rangeIndex]
					},
					.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL
				};

				for (const DescriptorRange& range : set.ranges)
				{
					ranges[rangeIndex++] = D3D12_DESCRIPTOR_RANGE1
					{
						.RangeType = ToDescriptorRangeType(range.type),
						.NumDescriptors = static_cast<UINT>(range.count),
						.BaseShaderRegister = static_cast<UINT>(range.baseShaderRegister),
						.RegisterSpace = registerSpace,
						.Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
						.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND
					};
				}
			}

			for (const StaticSamplerParams& staticSamplerParams : set.staticSamplers)
			{
				const D3D12_SAMPLER_DESC2 samplerDesc = ToSamplerDesc(staticSamplerParams.samplerParams);
				staticSamplers[staticSamplerIndex++] = D3D12_STATIC_SAMPLER_DESC1
				{
					.Filter = samplerDesc.Filter,
					.AddressU = samplerDesc.AddressU,
					.AddressV = samplerDesc.AddressV,
					.AddressW = samplerDesc.AddressW,
					.MipLODBias = samplerDesc.MipLODBias,
					.MaxAnisotropy = samplerDesc.MaxAnisotropy,
					.ComparisonFunc = samplerDesc.ComparisonFunc,
					.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,
					.MinLOD = samplerDesc.MinLOD,
					.MaxLOD = samplerDesc.MaxLOD,
					.ShaderRegister = static_cast<UINT>(staticSamplerParams.shaderRegister),
					.RegisterSpace = registerSpace,
					.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL,
					.Flags = samplerDesc.Flags
				};
			}
		}

		return D3D12_ROOT_SIGNATURE_DESC2
		{
			.NumParameters = static_cast<UINT>(parameters.size()), 
			.pParameters = parameters.data(),
			.NumStaticSamplers = static_cast<UINT>(staticSamplers.size()),
			.pStaticSamplers = staticSamplers.data(),
			.Flags = ToRootSignatureFlags(params.flags)
		};
	}

	constexpr D3D12_DESCRIPTOR_RANGE_TYPE ToDescriptorRangeType(const DescriptorType descriptorType) noexcept
	{
		switch (descriptorType)
		{
		case DescriptorType::ConstantBuffer:
			return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		case DescriptorType::BufferShaderResource:
		case DescriptorType::TextureShaderResource:
			return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		case DescriptorType::BufferUnorderedAccess:
		case DescriptorType::TextureUnorderedAccess:
			return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		case DescriptorType::Sampler:
			return D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
		default: [[unlikely]]
			assert(false && "Invalid descriptor type.");
			return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		}
	}

	constexpr D3D12_ROOT_SIGNATURE_FLAGS ToRootSignatureFlags(const PipelineLayoutFlag flags) noexcept
	{
		auto rootSigFlags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
		if (Any(PipelineLayoutFlag::DirectlyIndexed, flags))
		{
			rootSigFlags |= D3D12_ROOT_SIGNATURE_FLAG_CBV_SRV_UAV_HEAP_DIRECTLY_INDEXED | D3D12_ROOT_SIGNATURE_FLAG_SAMPLER_HEAP_DIRECTLY_INDEXED;
		}

		return rootSigFlags;
	}
}
