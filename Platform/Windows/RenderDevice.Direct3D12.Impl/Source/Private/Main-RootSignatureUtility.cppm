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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:RootSignatureUtility;

import std;

import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :SamplerUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
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
	constexpr D3D12_ROOT_SIGNATURE_DESC1 ToRootSignatureDesc(const PipelineLayoutParams& params, std::span<D3D12_ROOT_PARAMETER1> parameters,
		std::span<D3D12_DESCRIPTOR_RANGE1> ranges, std::span<D3D12_STATIC_SAMPLER_DESC> staticSamplers) noexcept;
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_RANGE_TYPE ToDescriptorRangeType(ShaderDataDescriptorType descriptorType) noexcept;

	[[nodiscard("Pure function")]]
	constexpr std::size_t GetRangeCount(const std::variant<std::span<const ShaderDataDescriptorRange>, std::span<const SamplerDescriptorRange>>& ranges) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr RootSignatureDescCounts GetRootSignatureCounts(const std::span<const DescriptorSet> descriptorSets) noexcept
	{
		auto counts = RootSignatureDescCounts{};
		for (const DescriptorSet& set : descriptorSets)
		{
			const std::size_t rangeCount = GetRangeCount(set.ranges);
			counts.tableCount += rangeCount > 0uz;
			counts.rangeCount += static_cast<UINT>(rangeCount);
			counts.staticSamplerCount += static_cast<UINT>(set.staticSamplers.size());
		}

		return counts;
	}

	constexpr D3D12_ROOT_SIGNATURE_DESC1 ToRootSignatureDesc(const PipelineLayoutParams& params, const std::span<D3D12_ROOT_PARAMETER1> parameters, 
		const std::span<D3D12_DESCRIPTOR_RANGE1> ranges, const std::span<D3D12_STATIC_SAMPLER_DESC> staticSamplers) noexcept
	{
		for (std::size_t setIndex = 0uz, parameterIndex = 0uz, rangeIndex = 0uz, staticSamplerIndex = 0uz; 
			setIndex < params.descriptorSets.size(); ++setIndex)
		{
			const DescriptorSet& set = params.descriptorSets[setIndex];
			const UINT registerSpace = set.setIndex;
			
			if (const std::size_t rangeCount = GetRangeCount(set.ranges); rangeCount > 0uz)
			{
				parameters[parameterIndex++] = D3D12_ROOT_PARAMETER1
				{
					.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,
					.DescriptorTable = D3D12_ROOT_DESCRIPTOR_TABLE1
					{
						.NumDescriptorRanges = static_cast<UINT>(rangeCount),
						.pDescriptorRanges = &ranges[rangeIndex]
					},
					.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL
				};

				std::visit(Type::Overload
				{
					[&](const std::span<const ShaderDataDescriptorRange> r) noexcept
					{
						for (const ShaderDataDescriptorRange& range : r)
						{
							ranges[rangeIndex++] = D3D12_DESCRIPTOR_RANGE1
							{
								.RangeType = ToDescriptorRangeType(range.type),
								.NumDescriptors = range.shaderRegisterCount,
								.BaseShaderRegister = range.firstShaderRegister,
								.RegisterSpace = registerSpace,
								.Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
								.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND
							};
						}
					},
					[&](const std::span<const SamplerDescriptorRange> r) noexcept
					{
						for (const SamplerDescriptorRange& range : r)
						{
							ranges[rangeIndex++] = D3D12_DESCRIPTOR_RANGE1
							{
								.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER,
								.NumDescriptors = range.shaderRegisterCount,
								.BaseShaderRegister = range.firstShaderRegister,
								.RegisterSpace = registerSpace,
								.Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE,
								.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND
							};
						}
					},
				}, set.ranges);
			}

			for (const StaticSamplerParams& staticSamplerParams : set.staticSamplers)
			{
				const D3D12_SAMPLER_DESC2 samplerDesc = ToSamplerDesc(staticSamplerParams.samplerParams);
				staticSamplers[staticSamplerIndex++] = D3D12_STATIC_SAMPLER_DESC
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
					.ShaderRegister = staticSamplerParams.shaderRegister,
					.RegisterSpace = registerSpace,
					.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL
				};
			}
		}

		return D3D12_ROOT_SIGNATURE_DESC1
		{
			.NumParameters = static_cast<UINT>(parameters.size()), 
			.pParameters = parameters.data(),
			.NumStaticSamplers = static_cast<UINT>(staticSamplers.size()),
			.pStaticSamplers = staticSamplers.data(),
			.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE
		};
	}

	constexpr D3D12_DESCRIPTOR_RANGE_TYPE ToDescriptorRangeType(const ShaderDataDescriptorType descriptorType) noexcept
	{
		switch (descriptorType)
		{
		case ShaderDataDescriptorType::ConstantBuffer:
			return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		case ShaderDataDescriptorType::BufferShaderResource:
		case ShaderDataDescriptorType::TextureShaderResource:
			return D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		case ShaderDataDescriptorType::BufferUnorderedAccess:
		case ShaderDataDescriptorType::TextureUnorderedAccess:
			return D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		default: [[unlikely]]
			assert(false && "Invalid descriptor type.");
			return D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		}
	}

	constexpr std::size_t GetRangeCount(const std::variant<std::span<const ShaderDataDescriptorRange>, std::span<const SamplerDescriptorRange>>& ranges) noexcept
	{
		return std::visit(Type::Overload
		{
			[](const std::span<const ShaderDataDescriptorRange> r) noexcept
			{
				return r.size();
			},
			[](const std::span<const SamplerDescriptorRange> r) noexcept
			{
				return r.size();
			},
		}, ranges);
	}
}
