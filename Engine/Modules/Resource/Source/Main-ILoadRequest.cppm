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

export module PonyEngine.Resource:ILoadRequest;

import std;

import :LoadParams;
import :RequestStatus;

export namespace PonyEngine::Resource
{
	/// @brief Load request.
	class ILoadRequest
	{
		PONY_INTERFACE_BODY(ILoadRequest)

		/// @brief Gets the load parameters.
		/// @return Load parameters.
		[[nodiscard("Pure function")]]
		virtual const LoadParams& Params() const noexcept = 0;

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual RequestStatus Status() const noexcept = 0;
		/// @brief Gets how many bytes were transferred.
		/// @return Transferred byte count.
		/// @note It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const = 0;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure.
		virtual void Wait() const noexcept = 0;
	};
}
