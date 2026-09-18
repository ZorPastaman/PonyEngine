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

export module PonyEngine.Resource.Pack:IPackMountRequest;

import std;

import PonyEngine.Async;

import :PackHandle;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack mount request.
	class IPackMountRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IPackMountRequest)

		/// @brief Gets a pack.
		/// @return Pack.
		/// @not It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual PackHandle Pack() const = 0;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;
	};
}
