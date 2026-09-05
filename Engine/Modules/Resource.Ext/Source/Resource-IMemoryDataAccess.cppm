/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Resource.Ext:IMemoryDataAccess;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Data access that provides direct access to a resource data in the memory.
	class IMemoryDataAccess
	{
		PONY_INTERFACE_BODY(IMemoryDataAccess)

		/// @brief Gets the buffer.
		/// @return Buffer.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Buffer() const noexcept = 0;
	};
}
