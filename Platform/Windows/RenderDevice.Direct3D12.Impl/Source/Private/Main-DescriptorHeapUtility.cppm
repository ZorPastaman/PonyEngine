/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:DescriptorHeapUtility;

import std;

import PonyEngine.RenderDevice;

import :DepthStencilContainer;
import :RenderTargetContainer;
import :SamplerContainer;
import :ShaderDataContainer;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Casts to a native depth stencil container.
	/// @param container Depth stencil container.
	/// @return Native depth stencil container.
	[[nodiscard("Pure function")]]
	DepthStencilContainer& ToNativeContainer(IDepthStencilContainer& container);
	/// @brief Casts to a native depth stencil container.
	/// @param container Depth stencil container.
	/// @return Native depth stencil container.
	[[nodiscard("Pure function")]]
	const DepthStencilContainer& ToNativeContainer(const IDepthStencilContainer& container);
	/// @brief Casts to a native depth stencil container.
	/// @param container Depth stencil container.
	/// @return Native depth stencil container.
	[[nodiscard("Pure function")]]
	DepthStencilContainer* ToNativeContainer(IDepthStencilContainer* container);
	/// @brief Casts to a native depth stencil container.
	/// @param container Depth stencil container.
	/// @return Native depth stencil container.
	[[nodiscard("Pure function")]]
	const DepthStencilContainer* ToNativeContainer(const IDepthStencilContainer* container);
	/// @brief Casts to a native render target container.
	/// @param container Render target container.
	/// @return Native render target container.
	[[nodiscard("Pure function")]]
	RenderTargetContainer& ToNativeContainer(IRenderTargetContainer& container);
	/// @brief Casts to a native render target container.
	/// @param container Render target container.
	/// @return Native render target container.
	[[nodiscard("Pure function")]]
	const RenderTargetContainer& ToNativeContainer(const IRenderTargetContainer& container);
	/// @brief Casts to a native render target container.
	/// @param container Render target container.
	/// @return Native render target container.
	[[nodiscard("Pure function")]]
	RenderTargetContainer* ToNativeContainer(IRenderTargetContainer* container);
	/// @brief Casts to a native render target container.
	/// @param container Render target container.
	/// @return Native render target container.
	[[nodiscard("Pure function")]]
	const RenderTargetContainer* ToNativeContainer(const IRenderTargetContainer* container);
	/// @brief Casts to a native shader data container.
	/// @param container Shader data container.
	/// @return Native shader data container.
	[[nodiscard("Pure function")]]
	ShaderDataContainer& ToNativeContainer(IShaderDataContainer& container);
	/// @brief Casts to a native shader data container.
	/// @param container Shader data container.
	/// @return Native shader data container.
	[[nodiscard("Pure function")]]
	const ShaderDataContainer& ToNativeContainer(const IShaderDataContainer& container);
	/// @brief Casts to a native shader data container.
	/// @param container Shader data container.
	/// @return Native shader data container.
	[[nodiscard("Pure function")]]
	ShaderDataContainer* ToNativeContainer(IShaderDataContainer* container);
	/// @brief Casts to a native shader data container.
	/// @param container Shader data container.
	/// @return Native shader data container.
	[[nodiscard("Pure function")]]
	const ShaderDataContainer* ToNativeContainer(const IShaderDataContainer* container);
	/// @brief Casts to a native sampler container.
	/// @param container Sampler container.
	/// @return Native sampler container.
	[[nodiscard("Pure function")]]
	SamplerContainer& ToNativeContainer(ISamplerContainer& container);
	/// @brief Casts to a native sampler container.
	/// @param container Sampler container.
	/// @return Native sampler container.
	[[nodiscard("Pure function")]]
	const SamplerContainer& ToNativeContainer(const ISamplerContainer& container);
	/// @brief Casts to a native sampler container.
	/// @param container Sampler container.
	/// @return Native sampler container.
	[[nodiscard("Pure function")]]
	SamplerContainer* ToNativeContainer(ISamplerContainer* container);
	/// @brief Casts to a native sampler container.
	/// @param container Sampler container.
	/// @return Native sampler container.
	[[nodiscard("Pure function")]]
	const SamplerContainer* ToNativeContainer(const ISamplerContainer* container);

	/// @brief Makes a descriptor heap description.
	/// @param params Shader data container parameters.
	/// @return Descriptor heap description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const ShaderDataContainerParams& params) noexcept;
	/// @brief Makes a descriptor heap description.
	/// @param params Render target container parameters.
	/// @return Descriptor heap description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const RenderTargetContainerParams& params) noexcept;
	/// @brief Makes a descriptor heap description.
	/// @param params Depth stencil parameters.
	/// @return Descriptor heap description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const DepthStencilContainerParams& params) noexcept;
	/// @brief Makes a descriptor heap description.
	/// @param params Sampler parameters.
	/// @return Descriptor heap description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const SamplerContainerParams& params) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	DepthStencilContainer& ToNativeContainer(IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<DepthStencilContainer&>(container);
	}

	const DepthStencilContainer& ToNativeContainer(const IDepthStencilContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const DepthStencilContainer&>(container);
	}

	DepthStencilContainer* ToNativeContainer(IDepthStencilContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<DepthStencilContainer*>(container);
	}

	const DepthStencilContainer* ToNativeContainer(const IDepthStencilContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(DepthStencilContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const DepthStencilContainer*>(container);
	}

	RenderTargetContainer& ToNativeContainer(IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<RenderTargetContainer&>(container);
	}

	const RenderTargetContainer& ToNativeContainer(const IRenderTargetContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const RenderTargetContainer&>(container);
	}

	RenderTargetContainer* ToNativeContainer(IRenderTargetContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<RenderTargetContainer*>(container);
	}

	const RenderTargetContainer* ToNativeContainer(const IRenderTargetContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(RenderTargetContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const RenderTargetContainer*>(container);
	}

	ShaderDataContainer& ToNativeContainer(IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<ShaderDataContainer&>(container);
	}

	const ShaderDataContainer& ToNativeContainer(const IShaderDataContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const ShaderDataContainer&>(container);
	}

	ShaderDataContainer* ToNativeContainer(IShaderDataContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<ShaderDataContainer*>(container);
	}

	const ShaderDataContainer* ToNativeContainer(const IShaderDataContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(ShaderDataContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const ShaderDataContainer*>(container);
	}

	SamplerContainer& ToNativeContainer(ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<SamplerContainer&>(container);
	}

	const SamplerContainer& ToNativeContainer(const ISamplerContainer& container)
	{
#ifndef NDEBUG
		if (typeid(container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const SamplerContainer&>(container);
	}

	SamplerContainer* ToNativeContainer(ISamplerContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<SamplerContainer*>(container);
	}

	const SamplerContainer* ToNativeContainer(const ISamplerContainer* const container)
	{
#ifndef NDEBUG
		if (container && typeid(*container) != typeid(SamplerContainer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid container");
		}
#endif

		return static_cast<const SamplerContainer*>(container);
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const ShaderDataContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
			.NumDescriptors = params.size,
			.Flags = params.shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const RenderTargetContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
			.NumDescriptors = params.size,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const DepthStencilContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
			.NumDescriptors = params.size,
			.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}

	constexpr D3D12_DESCRIPTOR_HEAP_DESC MakeDescriptorHeapDesc(const SamplerContainerParams& params) noexcept
	{
		return D3D12_DESCRIPTOR_HEAP_DESC
		{
			.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,
			.NumDescriptors = params.size,
			.Flags = params.shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			.NodeMask = 0u
		};
	}
}
