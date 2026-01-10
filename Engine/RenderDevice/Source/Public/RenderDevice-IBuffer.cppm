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

export module PonyEngine.RenderDevice:IBuffer;

import std;

import :BufferUsage;

export namespace PonyEngine::Render
{
	class IBuffer
	{
		PONY_INTERFACE_BODY(IBuffer)

		[[nodiscard("Pure function")]]
		virtual std::uint64_t Size() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual BufferUsage Usage() const noexcept = 0;
	};
}
