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

import :FenceValue;

export namespace PonyEngine::RenderDevice
{
	class IWaiter
	{
		PONY_INTERFACE_BODY(IWaiter)

		virtual void Wait(std::span<const FenceValue> fenceValues, std::chrono::nanoseconds timeout) = 0;
	};
}
