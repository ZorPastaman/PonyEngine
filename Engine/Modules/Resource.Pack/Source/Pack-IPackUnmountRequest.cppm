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

export module PonyEngine.Resource.Pack:IPackUnmountRequest;

import std;

import PonyEngine.Async;

import :PackHandle;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack unmount request.
	class IPackUnmountRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IPackUnmountRequest)

		/// @brief Gets a pack.
		/// @return Pack.
		[[nodiscard("Pure function")]]
		virtual PackHandle Pack() const noexcept = 0;

		/// @brief Gets exceptions that occured during the request execution.
		/// @return Exceptions.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::exception_ptr> Exceptions() const = 0;
	};
}
