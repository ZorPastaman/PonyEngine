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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:RootSignature;

import std;

import PonyEngine.Math;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;
import PonyEngine.Type;

import :ObjectUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Root signature wrapper.
	class RootSignature final : public IPipelineLayout
	{
	public:
		/// @brief Creates a root signature wrapper.
		/// @param rootSignature Root signature.
		/// @param params Pipeline layout parameters.
		[[nodiscard("Pure constructor")]]
		RootSignature(ID3D12RootSignature& rootSignature, const PipelineLayoutParams& params);
		/// @brief Creates a root signature wrapper.
		/// @param rootSignature Root signature.
		/// @param params Pipeline layout parameters.
		[[nodiscard("Pure constructor")]]
		RootSignature(Platform::Windows::ComPtr<ID3D12RootSignature>&& rootSignature, const PipelineLayoutParams& params);
		RootSignature(const RootSignature&) = delete;
		RootSignature(RootSignature&&) = delete;

		~RootSignature() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::span<const DescriptorSetMeta> DescriptorSets() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		ID3D12RootSignature& GetRootSignature() const noexcept;

		RootSignature& operator =(const RootSignature&) = delete;
		RootSignature& operator =(RootSignature&&) = delete;

	private:
		/// @brief Creates metas.
		/// @param descriptorSets Descriptor sets.
		/// @return Metas.
		static std::unique_ptr<std::byte[]> CreateMetas(std::span<const DescriptorSet> descriptorSets);

		Platform::Windows::ComPtr<ID3D12RootSignature> rootSignature; ///< Root signature.
		
		std::size_t setCount; ///< Descriptor set count.
		std::unique_ptr<std::byte[]> metas; ///< Descriptor set metas.

		std::string name; ///< Name.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	RootSignature::RootSignature(ID3D12RootSignature& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(&rootSignature),
		setCount{params.descriptorSets.size()},
		metas(setCount > 0uz ? CreateMetas(params.descriptorSets) : nullptr)
	{
	}

	RootSignature::RootSignature(Platform::Windows::ComPtr<ID3D12RootSignature>&& rootSignature, const PipelineLayoutParams& params) :
		rootSignature(std::move(rootSignature)),
		setCount{params.descriptorSets.size()},
		metas(setCount > 0uz ? CreateMetas(params.descriptorSets) : nullptr)
	{
		assert(this->rootSignature && "The root signature is nullptr.");
	}

	std::span<const DescriptorSetMeta> RootSignature::DescriptorSets() const noexcept
	{
		return setCount > 0uz 
			? std::span<const DescriptorSetMeta>(reinterpret_cast<const DescriptorSetMeta*>(metas.get()), setCount) 
			: std::span<const DescriptorSetMeta>();
	}

	std::string_view RootSignature::Name() const noexcept
	{
		return name;
	}

	void RootSignature::Name(const std::string_view name)
	{
		SetObjectName(*rootSignature, name);

		try
		{
			this->name = name;
		}
		catch (...)
		{
			SetObjectName(*rootSignature, this->name);
			throw;
		}
	}

	ID3D12RootSignature& RootSignature::GetRootSignature() const noexcept
	{
		return *rootSignature;
	}

	std::unique_ptr<std::byte[]> RootSignature::CreateMetas(const std::span<const DescriptorSet> descriptorSets)
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

		const std::size_t setByteSize = descriptorSets.size() * sizeof(DescriptorSetMeta);
		const std::size_t shaderDataByteOffset = Math::Align(setByteSize, alignof(ShaderDataDescriptorRange));
		const std::size_t shaderDataByteSize = shaderDataCount * sizeof(ShaderDataDescriptorRange);
		const std::size_t shaderDataByteEnd = shaderDataByteOffset + shaderDataByteSize;
		const std::size_t samplerByteOffset = Math::Align(shaderDataByteEnd, alignof(SamplerDescriptorRange));
		const std::size_t samplerByteSize = samplerCount * sizeof(SamplerDescriptorRange);
		const std::size_t samplerByteEnd = samplerByteOffset + samplerByteSize;
		const std::size_t staticSamplerByteOffset = Math::Align(samplerByteEnd, alignof(StaticSamplerParams));
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

			if (!set.staticSamplers.empty())
			{
				setMeta->staticSamplers = std::span<const StaticSamplerParams>(staticSamplerParams, set.staticSamplers.size());
				std::memcpy(staticSamplerParams, set.staticSamplers.data(), set.staticSamplers.size() * sizeof(StaticSamplerParams));
				staticSamplerParams += set.staticSamplers.size();
			}
			else
			{
				setMeta->staticSamplers = std::span<const StaticSamplerParams>();
			}
			setMeta->setIndex = set.setIndex;

			++setMeta;
		}

		return metas;
	}
}
