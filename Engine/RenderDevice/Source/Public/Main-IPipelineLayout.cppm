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

import :DescriptorRangeMeta;
import :PipelineLayoutFlag;
import :StaticSamplerMeta;

export namespace PonyEngine::RenderDevice
{
	class IPipelineLayout
	{
		PONY_INTERFACE_BODY(IPipelineLayout)

		[[nodiscard("Pure function")]]
		virtual std::span<const DescriptorRangeMeta> Ranges() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::span<const StaticSamplerMeta> StaticSamplers() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual PipelineLayoutFlag Flags() const noexcept = 0;

		virtual void SetName(std::string_view name) noexcept = 0;
	};
}
