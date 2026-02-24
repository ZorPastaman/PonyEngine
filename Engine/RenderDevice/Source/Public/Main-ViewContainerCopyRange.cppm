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
import :IRenderTargetContainer;
import :ISamplerContainer;
import :IShaderDataContainer;

export namespace PonyEngine::RenderDevice
{
	template<typename T>
	struct ViewContainerCopyRange final
	{
		const T* source = nullptr;
		T* destination = nullptr;
		std::uint32_t sourceOffset = 0u;
		std::uint32_t destinationOffset = 0u;
		std::uint32_t count = 0u;
	};

	using ShaderDataCopyRange = ViewContainerCopyRange<IShaderDataContainer>;
	using RenderTargetCopyRange = ViewContainerCopyRange<IRenderTargetContainer>;
	using DepthStencilCopyRange = ViewContainerCopyRange<IDepthStencilContainer>;
	using SamplerCopyRange = ViewContainerCopyRange<ISamplerContainer>;
}
