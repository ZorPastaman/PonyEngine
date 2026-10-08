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

export module PonyEngine.Resource.World:IWorldDeserializationRequest;

import std;

import PonyEngine.Async;

export namespace PonyEngine::Resource::World
{
	/// @brief World data deserialization request.
	class IWorldDeserializationRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IWorldDeserializationRequest)

		/// @brief Gets the request exceptions.
		/// @return Exceptions.
		/// @note May be called only the status is failure.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::exception_ptr> Exceptions() const = 0;
	};
}
