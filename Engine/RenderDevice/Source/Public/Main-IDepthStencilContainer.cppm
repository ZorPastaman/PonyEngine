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

export module PonyEngine.RenderDevice:IDepthStencilContainer;

import std;

import :DepthStencilMeta;

export namespace PonyEngine::RenderDevice
{
	class IDepthStencilContainer
	{
		PONY_INTERFACE_BODY(IDepthStencilContainer)

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const DepthStencilMeta& Meta(std::uint32_t index) const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}
