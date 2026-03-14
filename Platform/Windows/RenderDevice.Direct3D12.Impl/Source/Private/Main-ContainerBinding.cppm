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
	/// @brief Shader data and sampler container binding helper.
	class ContainerBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ContainerBinding() noexcept;
		ContainerBinding(const ContainerBinding&) = delete;
		ContainerBinding(ContainerBinding&&) = delete;

		~ContainerBinding() noexcept = default;

		/// @brief Resets the containers.
		void Reset() noexcept;

		/// @brief Checks if it has a shader data container bound.
		/// @return @a True if it's bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasShaderDataContainer() const noexcept;
		/// @brief Checks if it has a sampler container bound.
		/// @return @a True if it's bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasSamplerContainer() const noexcept;

		/// @brief Gets the bound shader data container.
		/// @return Shader data container.
		[[nodiscard("Pure function")]]
		const ShaderDataContainer* GetShaderDataContainer() const noexcept;
		/// @brief Gets the bound sampler container.
		/// @return Sampler container.
		[[nodiscard("Pure function")]]
		const SamplerContainer* GetSamplerContainer() const noexcept;

		/// @brief Sets containers to the command list and to the helper.
		/// @param shaderDataContainer Shader data container.
		/// @param samplerContainer Sampler container.
		/// @param commandList Command list.
		void SetContainers(const ShaderDataContainer* shaderDataContainer, const SamplerContainer* samplerContainer, CommandList& commandList);
		/// @brief Binds the shader data to a graphics binding point.
		/// @param shaderDataBindings Shader data bindings.
		/// @param commandList Command list.
		void BindGraphicsShaderData(std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const;
		/// @brief Binds the samplers to a graphics binding point.
		/// @param samplerBindings Sampler bindings.
		/// @param commandList Command list.
		void BindGraphicsSampler(std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const;
		/// @brief Binds the shader data to a compute binding point.
		/// @param shaderDataBindings Shader data bindings.
		/// @param commandList Command list.
		void BindComputeShaderData(std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const;
		/// @brief Binds the samplers to a compute binding point.
		/// @param samplerBindings Sampler bindings.
		/// @param commandList Command list.
		void BindComputeSampler(std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const;

		/// @brief Validates the shader data that is about to be bound.
		/// @param rootSig Root signature.
		/// @param tableIndex Root signature table index.
		/// @param shaderDataIndex Shader data container index.
		void ValidateShaderData(const RootSignature& rootSig, std::uint32_t tableIndex, std::uint32_t shaderDataIndex) const;
		/// @brief Validates the sampler that is about to be bound.
		/// @param rootSig Root signature.
		/// @param tableIndex Root signature table index.
		/// @param samplerIndex Sampler container index.
		void ValidateSamplerData(const RootSignature& rootSig, std::uint32_t tableIndex, std::uint32_t samplerIndex) const;

		ContainerBinding& operator =(const ContainerBinding&) = delete;
		ContainerBinding& operator =(ContainerBinding&&) = delete;

	private:
		/// @brief Validates if the bound shader data container is valid and has enough elements.
		/// @param index Target index.
		void ValidateShaderDataIndex(std::uint32_t index) const;
		/// @brief Validates if the bound sampler container is valid and has enough elements.
		/// @param index Target index.
		void ValidateSamplerIndex(std::uint32_t index) const;

		const ShaderDataContainer* shaderDataContainer; ///< Bound shader data container.
		const SamplerContainer* samplerContainer; ///< Bound sampler container.
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
#ifndef NDEBUG
		if (shaderDataContainer)
		{
			if (!shaderDataContainer->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Shader data container is not shader visible");
			}
		}

		if (samplerContainer)
		{
			if (!samplerContainer->IsShaderVisible()) [[unlikely]]
			{
				throw std::invalid_argument("Sampler container is not shader visible");
			}
		}
#endif

		commandList.SetContainers(shaderDataContainer, samplerContainer);
		this->shaderDataContainer = shaderDataContainer;
		this->samplerContainer = samplerContainer;
	}

	void ContainerBinding::BindGraphicsShaderData(const std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const
	{
		assert((shaderDataBindings.empty() || shaderDataContainer) && "The shader data container is nullptr.");

		for (const ShaderDataBinding& binding : shaderDataBindings)
		{
			commandList.SetGraphicsDescriptorTable(binding.layoutSetIndex, shaderDataContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindGraphicsSampler(const std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const
	{
		assert((samplerBindings.empty() || samplerContainer) && "The sampler container is nullptr.");

		for (const SamplerBinding& binding : samplerBindings)
		{
			commandList.SetGraphicsDescriptorTable(binding.layoutSetIndex, samplerContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindComputeShaderData(const std::span<const ShaderDataBinding> shaderDataBindings, CommandList& commandList) const
	{
		assert((shaderDataBindings.empty() || shaderDataContainer) && "The shader data container is nullptr.");

		for (const ShaderDataBinding& binding : shaderDataBindings)
		{
			commandList.SetComputeDescriptorTable(binding.layoutSetIndex, shaderDataContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::BindComputeSampler(const std::span<const SamplerBinding> samplerBindings, CommandList& commandList) const
	{
		assert((samplerBindings.empty() || samplerContainer) && "The sampler container is nullptr.");

		for (const SamplerBinding& binding : samplerBindings)
		{
			commandList.SetComputeDescriptorTable(binding.layoutSetIndex, samplerContainer->GpuHandle(binding.containerIndex));
		}
	}

	void ContainerBinding::ValidateShaderData(const RootSignature& rootSig, const std::uint32_t tableIndex, const std::uint32_t shaderDataIndex) const
	{
		ValidateShaderDataIndex(shaderDataIndex);

#ifndef NDEBUG
		if (tableIndex >= rootSig.DescriptorSets().size()) [[unlikely]]
		{
			throw std::invalid_argument("Table index is invalid");
		}

		const DescriptorSetMeta& set = rootSig.DescriptorSets()[tableIndex];

		std::uint32_t requiredDescriptorCount = 0uz;
		for (const ShaderDataDescriptorRange& range : set.shaderDataRanges)
		{
			requiredDescriptorCount += range.shaderRegisterCount;
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
			for (std::uint32_t i = 0u; i < range.shaderRegisterCount; ++i, ++containerIndex)
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
		if (tableIndex >= rootSig.DescriptorSets().size()) [[unlikely]]
		{
			throw std::invalid_argument("Table index is invalid");
		}

		const DescriptorSetMeta& set = rootSig.DescriptorSets()[tableIndex];

		std::uint32_t requiredDescriptorCount = 0uz;
		for (const SamplerDescriptorRange& range : set.samplerRanges)
		{
			requiredDescriptorCount += range.shaderRegisterCount;
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
			for (std::uint32_t i = 0u; i < range.shaderRegisterCount; ++i, ++containerIndex)
			{
				if (!std::holds_alternative<SamplerParams>(samplerContainer->Meta(containerIndex))) [[unlikely]]
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
