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

export module PonyEngine.RenderDevice:IPipelineLayout;

import std;

import :DescriptorSetMeta;
import :StaticSamplerMeta;

export namespace PonyEngine::RenderDevice
{
	class IPipelineLayout
	{
		PONY_INTERFACE_BODY(IPipelineLayout)

		[[nodiscard("Pure function")]]
		virtual std::span<const DescriptorSetMeta> Sets() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}
