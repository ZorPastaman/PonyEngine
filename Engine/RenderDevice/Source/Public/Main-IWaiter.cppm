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

export module PonyEngine.RenderDevice:IWaiter;

import std;

import :IFence;

export namespace PonyEngine::RenderDevice
{
	class IWaiter
	{
		PONY_INTERFACE_BODY(IWaiter)

		[[nodiscard("Pure function")]]
		virtual std::size_t MaxFences() const noexcept = 0;
		virtual void Wait(std::span<const std::pair<const IFence*, std::uint64_t>> fenceValues, std::chrono::nanoseconds timeout) = 0;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}
