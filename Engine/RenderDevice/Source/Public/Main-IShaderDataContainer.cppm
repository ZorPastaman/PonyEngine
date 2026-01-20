/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IShaderDataContainer;

import std;

import :ShaderDataMeta;

export namespace PonyEngine::RenderDevice
{
	class IShaderDataContainer
	{
		PONY_INTERFACE_BODY(IShaderDataContainer)

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsShaderVisible() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const ShaderDataMeta& Meta(std::uint32_t index) const noexcept = 0;
	};
}
