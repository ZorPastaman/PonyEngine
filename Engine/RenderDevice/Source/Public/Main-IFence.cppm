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

export module PonyEngine.RenderDevice:IFence;

import std;

export namespace PonyEngine::RenderDevice
{
	class IFence
	{
		PONY_INTERFACE_BODY(IFence)

		[[nodiscard("Pure function")]]
		virtual std::uint64_t CompletedValue() const noexcept = 0;
		virtual void Signal(std::uint64_t value) = 0;

		virtual void SetName(std::string_view name) = 0;
	};
}
