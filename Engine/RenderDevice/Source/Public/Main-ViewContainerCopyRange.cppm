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

import :IShaderDataContainer;

export namespace PonyEngine::RenderDevice
{
	template<typename T>
	struct ViewContainerCopyRange final
	{
		const T* source = nullptr;
		T* destination = nullptr;
		std::uint32_t sourceOffset;
		std::uint32_t destinationOffset;
		std::uint32_t count;
	};

	using ShaderDataCopyRange = ViewContainerCopyRange<IShaderDataContainer>;
}
