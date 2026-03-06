/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ViewContainerCopyRange;

import std;

import :IDepthStencilContainer;
import :IContainer;
import :IRenderTargetContainer;
import :ISamplerContainer;
import :IShaderDataContainer;

export namespace PonyEngine::RenderDevice
{
	/// @brief View container copy range.
	/// @tparam T Container type.
	template<std::derived_from<IContainer> T>
	struct ViewContainerCopyRange final
	{
		const T* source = nullptr; ///< Source container. Must be a valid container.
		T* destination = nullptr; ///< Destination container. Must be a valid container.
		std::uint32_t sourceOffset = 0u; ///< Source offset.
		std::uint32_t destinationOffset = 0u; ///< Destination offset.
		std::uint32_t count = 0u; ///< Copy count.
	};

	using ShaderDataCopyRange = ViewContainerCopyRange<IShaderDataContainer>; ///< Shader data copy range.
	using RenderTargetCopyRange = ViewContainerCopyRange<IRenderTargetContainer>; ///< Render target copy range.
	using DepthStencilCopyRange = ViewContainerCopyRange<IDepthStencilContainer>; ///< Depth stencil copy range.
	using SamplerCopyRange = ViewContainerCopyRange<ISamplerContainer>; ///< Sampler copy range.
}
