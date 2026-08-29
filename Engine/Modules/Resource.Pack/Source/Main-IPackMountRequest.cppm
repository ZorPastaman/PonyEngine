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

export module PonyEngine.Resource.Pack:IPackMountRequest;

import std;

import :PackHandle;
import :PackMountRequestStatus;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Pack mount request.
	class IPackMountRequest
	{
		PONY_INTERFACE_BODY(IPackMountRequest)

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual PackRequestStatus Status() const noexcept = 0;
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

		/// @brief Cancels the request.
		/// @remark The request may be completed even if the cancel was requested.
		virtual void Cancel() = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure or cancel.
		virtual void Wait() const noexcept = 0;
	};
}
