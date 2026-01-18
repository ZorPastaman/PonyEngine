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
import :IResource;

export namespace PonyEngine::RenderDevice
{
	class IBuffer : public IResource
	{
		PONY_INTERFACE_BODY(IBuffer)

		[[nodiscard("Pure function")]]
		virtual std::uint64_t Size() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual BufferUsage Usage() const noexcept = 0;

		virtual void* Map() = 0;
		virtual void* Map(std::uint64_t offset, std::uint64_t length) = 0;
		virtual void Unmap() = 0;
		virtual void Unmap(std::uint64_t offset, std::uint64_t length) = 0;
	};
}
