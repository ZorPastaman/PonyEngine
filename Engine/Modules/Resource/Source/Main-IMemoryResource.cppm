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

export module PonyEngine.Resource:IMemoryResource;

import std;

import :IResource;

export namespace PonyEngine::Resource
{
	/// @brief Direct memory resource access.
	class IMemoryResource : public IResource
	{
		PONY_INTERFACE_BODY(IMemoryResource)

		/// @brief Gets a resource memory.
		/// @return Resource memory.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Memory() const noexcept = 0;
	};
}
