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

import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;
import PonyEngine.Type;

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
		virtual std::span<const DescriptorSetMeta> Sets() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PipelineLayoutFlag Flags() const noexcept override;

		virtual void SetName(std::string_view name) noexcept override;

		D3D12RootSignature& operator =(const D3D12RootSignature&) = delete;
		D3D12RootSignature& operator =(D3D12RootSignature&&) = delete;

	private:
		static std::unique_ptr<std::byte[]> CreateMetas(std::span<const DescriptorSet> descriptorSets);

		Platform::Windows::ComPtr<ID3D12RootSignature> rootSignature;
		
		std::size_t setCount;
		std::unique_ptr<std::byte[]> metas;
		PipelineLayoutFlag flags;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12RootSignature::D3D12RootSignature(ID3D12RootSignature& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(&rootSignature),
		setCount{params.descriptorSets.size()},
		metas(setCount > 0uz ? CreateMetas(params.descriptorSets) : nullptr),
		flags{params.flags}
	{
	}

	D3D12RootSignature::D3D12RootSignature(Platform::Windows::ComPtr<ID3D12RootSignature>&& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(std::move(rootSignature)),
		setCount{params.descriptorSets.size()},
		metas(setCount > 0uz ? CreateMetas(params.descriptorSets) : nullptr),
		flags{params.flags}
	{
		assert(this->rootSignature && "The root signature is nullptr.");
	}

	std::span<const DescriptorSetMeta> D3D12RootSignature::Sets() const noexcept
	{
		return setCount > 0uz 
			? std::span<const DescriptorSetMeta>(reinterpret_cast<const DescriptorSetMeta*>(metas.get()), setCount) 
			: std::span<const DescriptorSetMeta>();
	}

	PipelineLayoutFlag D3D12RootSignature::Flags() const noexcept
	{
		return flags;
	}

	void D3D12RootSignature::SetName(const std::string_view name) noexcept
	{
		SetObjectName(*rootSignature, name);
	}

	std::unique_ptr<std::byte[]> D3D12RootSignature::CreateMetas(const std::span<const DescriptorSet> descriptorSets)
	{
		std::size_t shaderDataCount = 0uz;
		std::size_t samplerCount = 0uz;
		std::size_t staticSamplerCount = 0uz;
		for (const DescriptorSet& set : descriptorSets)
		{
			std::visit(Type::Overload
			{
				[&](const std::span<const ShaderDataDescriptorRange> r) noexcept
				{
					shaderDataCount += r.size();
				},
				[&](const std::span<const SamplerDescriptorRange> r) noexcept
				{
					samplerCount += r.size();
				}
			}, set.ranges);
			staticSamplerCount += set.staticSamplers.size();
		}

		const std::size_t setByteSize = descriptorSets.size() * sizeof(DescriptorSet);
		const std::size_t shaderDataByteOffset = (setByteSize / alignof(ShaderDataDescriptorRange) + (setByteSize % alignof(ShaderDataDescriptorRange) != 0)) * alignof(ShaderDataDescriptorRange);
		const std::size_t shaderDataByteSize = shaderDataCount * sizeof(ShaderDataDescriptorRange);
		const std::size_t shaderDataByteEnd = shaderDataByteOffset + shaderDataByteSize;
		const std::size_t samplerByteOffset = (shaderDataByteEnd / alignof(SamplerDescriptorRange) + (shaderDataByteEnd % alignof(SamplerDescriptorRange) != 0)) * alignof(SamplerDescriptorRange);
		const std::size_t samplerByteSize = samplerCount * sizeof(SamplerDescriptorRange);
		const std::size_t samplerByteEnd = samplerByteOffset + samplerByteSize;
		const std::size_t staticSamplerByteOffset = (samplerByteEnd / alignof(StaticSamplerParams) + (samplerByteEnd % alignof(StaticSamplerParams) != 0)) * alignof(StaticSamplerParams);
		const std::size_t staticSamplerByteSize = staticSamplerCount * sizeof(StaticSamplerParams);
		const std::size_t staticSamplerByteEnd = staticSamplerByteOffset + staticSamplerByteSize;

		auto metas = std::make_unique<std::byte[]>(staticSamplerByteEnd);
		DescriptorSetMeta* setMeta = reinterpret_cast<DescriptorSetMeta*>(metas.get());
		ShaderDataDescriptorRange* shaderDataRange = reinterpret_cast<ShaderDataDescriptorRange*>(metas.get() + shaderDataByteOffset);
		SamplerDescriptorRange* samplerRange = reinterpret_cast<SamplerDescriptorRange*>(metas.get() + samplerByteOffset);
		StaticSamplerParams* staticSamplerParams = reinterpret_cast<StaticSamplerParams*>(metas.get() + staticSamplerByteOffset);
		for (const DescriptorSet& set : descriptorSets)
		{
			std::visit(Type::Overload
			{
				[&](const std::span<const ShaderDataDescriptorRange> r) noexcept
				{
					setMeta->shaderDataRanges = std::span<const ShaderDataDescriptorRange>(shaderDataRange, r.size());
					setMeta->samplerRanges = std::span<const SamplerDescriptorRange>();
					std::memcpy(shaderDataRange, r.data(), r.size() * sizeof(ShaderDataDescriptorRange));
					shaderDataRange += r.size();
				},
				[&](const std::span<const SamplerDescriptorRange> r) noexcept
				{
					setMeta->shaderDataRanges = std::span<const ShaderDataDescriptorRange>();
					setMeta->samplerRanges = std::span<const SamplerDescriptorRange>(samplerRange, r.size());
					std::memcpy(samplerRange, r.data(), r.size() * sizeof(SamplerDescriptorRange));
					samplerRange += r.size();
				}
			}, set.ranges);

			if (set.staticSamplers.size() > 0uz)
			{
				setMeta->staticSamplers = std::span<const StaticSamplerParams>(staticSamplerParams, set.staticSamplers.size());
				std::memcpy(staticSamplerParams, set.staticSamplers.data(), set.staticSamplers.size() * sizeof(StaticSamplerParams));
				staticSamplerParams += set.staticSamplers.size();
			}
			else
			{
				setMeta->staticSamplers = std::span<const StaticSamplerParams>();
			}

			++setMeta;
		}

		return metas;
	}
}
