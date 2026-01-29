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

export module PonyEngine.RenderDevice:ISamplerContainer;

import std;

import :SamplerParams;

export namespace PonyEngine::RenderDevice
{
	struct EmptySamplerParams final
	{
	};
	using SamplerMeta = std::variant<EmptySamplerParams, SamplerParams>;

	class ISamplerContainer
	{
		PONY_INTERFACE_BODY(ISamplerContainer)

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Size() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsShaderVisible() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const SamplerMeta& Meta(std::uint32_t index) const noexcept = 0;

		virtual void SetName(std::string_view name) = 0;
	};
}
