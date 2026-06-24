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

export module PonyEngine.Resource.Ext:IMemoryResourceData;

import std;

export namespace PonyEngine::Resource
{
	class IMemoryResourceData
	{
		PONY_INTERFACE_BODY(IMemoryResourceData)

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Memory() const noexcept = 0;
	};
}
