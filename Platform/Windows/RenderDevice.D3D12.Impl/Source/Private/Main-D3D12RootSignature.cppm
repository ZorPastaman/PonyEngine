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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12RootSignature;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12ObjectUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12RootSignature final : public IPipelineLayout
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12RootSignature(ID3D12RootSignature& rootSignature, const PipelineLayoutParams& params);
		[[nodiscard("Pure constructor")]]
		D3D12RootSignature(Platform::Windows::ComPtr<ID3D12RootSignature>&& rootSignature, const PipelineLayoutParams& params);
		D3D12RootSignature(const D3D12RootSignature&) = delete;
		D3D12RootSignature(D3D12RootSignature&&) = delete;

		~D3D12RootSignature() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::span<const DescriptorRangeMeta> Ranges() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const StaticSamplerMeta> StaticSamplers() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual PipelineLayoutFlag Flags() const noexcept override;

		virtual void SetName(std::string_view name) noexcept override;

		D3D12RootSignature& operator =(const D3D12RootSignature&) = delete;
		D3D12RootSignature& operator =(D3D12RootSignature&&) = delete;

	private:
		void SetMetas(const PipelineLayoutParams& params);

		Platform::Windows::ComPtr<ID3D12RootSignature> rootSignature;
		
		std::size_t rangeMetaCount;
		std::unique_ptr<DescriptorRangeMeta[]> rangeMetas;
		std::size_t staticSamplerCount;
		std::unique_ptr<StaticSamplerMeta[]> staticSamplerMetas;

		PipelineLayoutFlag flags;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12RootSignature::D3D12RootSignature(ID3D12RootSignature& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(&rootSignature),
		rangeMetaCount{0uz},
		staticSamplerCount{0uz},
		flags{params.flags}
	{
		SetMetas(params);
	}

	D3D12RootSignature::D3D12RootSignature(Platform::Windows::ComPtr<ID3D12RootSignature>&& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(std::move(rootSignature)),
		rangeMetaCount{0uz},
		staticSamplerCount{0uz},
		flags{params.flags}
	{
		assert(this->rootSignature && "The root signature is nullptr.");
		SetMetas(params);
	}

	std::span<const DescriptorRangeMeta> D3D12RootSignature::Ranges() const noexcept
	{
		return rangeMetaCount > 0uz ? std::span<const DescriptorRangeMeta>(rangeMetas.get(), rangeMetaCount) : std::span<const DescriptorRangeMeta>();
	}

	std::span<const StaticSamplerMeta> D3D12RootSignature::StaticSamplers() const noexcept
	{
		return staticSamplerCount > 0uz ? std::span<const StaticSamplerMeta>(staticSamplerMetas.get(), staticSamplerCount) : std::span<const StaticSamplerMeta>();
	}

	PipelineLayoutFlag D3D12RootSignature::Flags() const noexcept
	{
		return flags;
	}

	void D3D12RootSignature::SetName(const std::string_view name) noexcept
	{
		SetObjectName(*rootSignature, name);
	}

	void D3D12RootSignature::SetMetas(const PipelineLayoutParams& params)
	{
		for (const DescriptorSet& set : params.descriptorSets)
		{
			rangeMetaCount += set.ranges.size();
			staticSamplerCount += set.staticSamplers.size();
		}

		if (rangeMetaCount > 0uz)
		{
			rangeMetas = std::make_unique<DescriptorRangeMeta[]>(rangeMetaCount);
		}
		if (staticSamplerCount > 0uz)
		{
			staticSamplerMetas = std::make_unique<StaticSamplerMeta[]>(staticSamplerCount);
		}

		for (std::size_t setIndex = 0uz, rangeIndex = 0uz, staticSamplerIndex = 0uz; setIndex < params.descriptorSets.size(); ++setIndex)
		{
			const DescriptorSet& set = params.descriptorSets[setIndex];
			
			for (const DescriptorRange& range : set.ranges)
			{
				rangeMetas[rangeIndex++] = DescriptorRangeMeta
				{
					.range = range,
					.descriptorSetIndex = setIndex
				};
			}

			for (const StaticSamplerParams& samplerParams : set.staticSamplers)
			{
				staticSamplerMetas[staticSamplerIndex++] = StaticSamplerMeta
				{
					.samplerParams = samplerParams,
					.descriptorSetIndex = setIndex
				};
			}
		}
	}
}
