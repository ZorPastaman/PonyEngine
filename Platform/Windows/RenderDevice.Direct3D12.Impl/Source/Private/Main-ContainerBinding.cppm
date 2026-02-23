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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ContainerBinding;

import std;

import PonyEngine.RenderDevice;

import :CommandList;
import :RootSignature;
import :SamplerContainer;
import :ShaderDataContainer;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class ContainerBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ContainerBinding() noexcept;
		ContainerBinding(const ContainerBinding&) = delete;
		ContainerBinding(ContainerBinding&&) = delete;

		~ContainerBinding() noexcept = default;

		void Reset() noexcept;

		[[nodiscard("Pure function")]]
		bool HasShaderDataContainer() const noexcept;
		[[nodiscard("Pure function")]]
		bool HasSamplerContainer() const noexcept;

		[[nodiscard("Pure function")]]
		const ShaderDataContainer* GetShaderDataContainer() const noexcept;
		[[nodiscard("Pure function")]]
		const SamplerContainer* GetSamplerContainer() const noexcept;

		void SetContainers(const ShaderDataContainer* shaderDataContainer, const SamplerContainer* samplerContainer, CommandList& commandList);
		void BindGraphicsShaderData(std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const;
		void BindGraphicsSampler(std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const;
		void BindComputeShaderData(std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const;
		void BindComputeSampler(std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const;

		void ValidateShaderData(const RootSignature& rootSig, std::uint32_t tableIndex, std::uint32_t shaderDataIndex) const;
		void ValidateSamplerData(const RootSignature& rootSig, std::uint32_t tableIndex, std::uint32_t samplerIndex) const;

		ContainerBinding& operator =(const ContainerBinding&) = delete;
		ContainerBinding& operator =(ContainerBinding&&) = delete;

	private:
		void ValidateShaderDataIndex(std::uint32_t index) const;
		void ValidateSamplerIndex(std::uint32_t index) const;

		const ShaderDataContainer* shaderDataContainer;
		const SamplerContainer* samplerContainer;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ContainerBinding::ContainerBinding() noexcept :
		shaderDataContainer{nullptr},
		samplerContainer{nullptr}
	{
	}

	void ContainerBinding::Reset() noexcept
	{
		shaderDataContainer = nullptr;
		samplerContainer = nullptr;
	}

	bool ContainerBinding::HasShaderDataContainer() const noexcept
	{
		return shaderDataContainer;
	}

	bool ContainerBinding::HasSamplerContainer() const noexcept
	{
		return samplerContainer;
	}

	const ShaderDataContainer* ContainerBinding::GetShaderDataContainer() const noexcept
	{
		return shaderDataContainer;
	}

	const SamplerContainer* ContainerBinding::GetSamplerContainer() const noexcept
	{
		return samplerContainer;
	}

	void ContainerBinding::SetContainers(const ShaderDataContainer* const shaderDataContainer, const SamplerContainer* const samplerContainer, CommandList& commandList)
	{
		commandList.SetContainers(shaderDataContainer, samplerContainer);
		this->shaderDataContainer = shaderDataContainer;
		this->samplerContainer = samplerContainer;
	}

	void ContainerBinding::BindGraphicsShaderData(const std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const
	{
		for (const ShaderDataBinding& binding : shaderDataBindings)
		{
			commandList.SetGraphicsDescriptorTable(binding.layoutSetIndex, shaderDataContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindGraphicsSampler(const std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const
	{
		for (const SamplerBinding& binding : samplerBindings)
		{
			commandList.SetGraphicsDescriptorTable(binding.layoutSetIndex, samplerContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindComputeShaderData(const std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const
	{
		for (const ShaderDataBinding& binding : shaderDataBindings)
		{
			commandList.SetComputeDescriptorTable(binding.layoutSetIndex, shaderDataContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindComputeSampler(const std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const
	{
		for (const SamplerBinding& binding : samplerBindings)
		{
			commandList.SetComputeDescriptorTable(binding.layoutSetIndex, samplerContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::ValidateShaderData(const RootSignature& rootSig, const std::uint32_t tableIndex, const std::uint32_t shaderDataIndex) const
	{
		ValidateShaderDataIndex(shaderDataIndex);

#ifndef NDEBUG
		if (tableIndex >= rootSig.Sets().size()) [[unlikely]]
		{
			throw std::invalid_argument("Table index is invalid");
		}

		const DescriptorSetMeta& set = rootSig.Sets()[tableIndex];

		std::uint32_t requiredDescriptorCount = 0uz;
		for (const ShaderDataDescriptorRange& range : set.shaderDataRanges)
		{
			requiredDescriptorCount += range.count;
		}
		if (requiredDescriptorCount == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Pipeline layout set doesn't have shader data slots");
		}
		if (shaderDataContainer->Size() - shaderDataIndex < requiredDescriptorCount) [[unlikely]]
		{
			throw std::invalid_argument("Unexpected shader data container end");
		}

		for (std::uint32_t containerIndex = shaderDataIndex; const ShaderDataDescriptorRange& range : set.shaderDataRanges)
		{
			for (std::uint32_t i = 0u; i < range.count; ++i, ++containerIndex)
			{
				switch (range.type)
				{
				case ShaderDataDescriptorType::ConstantBuffer:
					if (!std::holds_alternative<CBVMeta>(shaderDataContainer->Meta(containerIndex))) [[unlikely]]
					{
						throw std::invalid_argument("View type mismatch");
					}
					break;
				case ShaderDataDescriptorType::BufferShaderResource:
					if (!std::holds_alternative<BufferSRVMeta>(shaderDataContainer->Meta(containerIndex))) [[unlikely]]
					{
						throw std::invalid_argument("View type mismatch");
					}
					break;
				case ShaderDataDescriptorType::TextureShaderResource:
					if (!std::holds_alternative<TextureSRVMeta>(shaderDataContainer->Meta(containerIndex))) [[unlikely]]
					{
						throw std::invalid_argument("View type mismatch");
					}
					break;
				case ShaderDataDescriptorType::BufferUnorderedAccess:
					if (!std::holds_alternative<BufferUAVMeta>(shaderDataContainer->Meta(containerIndex))) [[unlikely]]
					{
						throw std::invalid_argument("View type mismatch");
					}
					break;
				case ShaderDataDescriptorType::TextureUnorderedAccess:
					if (!std::holds_alternative<TextureUAVMeta>(shaderDataContainer->Meta(containerIndex))) [[unlikely]]
					{
						throw std::invalid_argument("View type mismatch");
					}
					break;
				default: [[unlikely]]
					assert(false && "Invalid range type.");
					break;
				}
			}
		}
#endif
	}

	void ContainerBinding::ValidateSamplerData(const RootSignature& rootSig, const std::uint32_t tableIndex, const std::uint32_t samplerIndex) const
	{
		ValidateSamplerIndex(samplerIndex);

#ifndef NDEBUG
		if (tableIndex >= rootSig.Sets().size()) [[unlikely]]
		{
			throw std::invalid_argument("Table index is invalid");
		}

		const DescriptorSetMeta& set = rootSig.Sets()[tableIndex];

		std::uint32_t requiredDescriptorCount = 0uz;
		for (const SamplerDescriptorRange& range : set.samplerRanges)
		{
			requiredDescriptorCount += range.count;
		}
		if (requiredDescriptorCount == 0uz) [[unlikely]]
		{
			throw std::invalid_argument("Pipeline layout set doesn't have sampler slots");
		}
		if (samplerContainer->Size() - samplerIndex < requiredDescriptorCount) [[unlikely]]
		{
			throw std::invalid_argument("Unexpected sampler container end");
		}

		for (std::uint32_t containerIndex = samplerIndex; const ShaderDataDescriptorRange& range : set.shaderDataRanges)
		{
			for (std::uint32_t i = 0u; i < range.count; ++i, ++containerIndex)
			{
				if (std::holds_alternative<EmptySamplerParams>(samplerContainer->Meta(containerIndex))) [[unlikely]]
				{
					throw std::invalid_argument("View type mismatch");
				}
			}
		}
#endif
	}

	void ContainerBinding::ValidateShaderDataIndex(const std::uint32_t index) const
	{
#ifndef NDEBUG
		if (!shaderDataContainer || index >= shaderDataContainer->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid shader data index");
		}
#endif
	}

	void ContainerBinding::ValidateSamplerIndex(const std::uint32_t index) const
	{
#ifndef NDEBUG
		if (!samplerContainer || index >= samplerContainer->Size()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid sampler index");
		}
#endif
	}
}
