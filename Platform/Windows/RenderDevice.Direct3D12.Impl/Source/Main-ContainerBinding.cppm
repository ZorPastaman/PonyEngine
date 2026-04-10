/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ContainerBinding;

import :SamplerContainer;
import :ShaderDataContainer;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Shader data and sampler container binding.
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
		void SetContainers(const ShaderDataContainer* shaderDataContainer, const SamplerContainer* samplerContainer) noexcept;

		ContainerBinding& operator =(const ContainerBinding&) = delete;
		ContainerBinding& operator =(ContainerBinding&&) = delete;

	private:
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

	void ContainerBinding::SetContainers(const ShaderDataContainer* const shaderDataContainer, const SamplerContainer* const samplerContainer) noexcept
	{
		this->shaderDataContainer = shaderDataContainer;
		this->samplerContainer = samplerContainer;
	}
}
