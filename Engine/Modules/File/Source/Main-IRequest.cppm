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

export module PonyEngine.File:IRequest;

import std;

import :RequestStatus;

export namespace PonyEngine::File
{
	/// @brief Request.
	class IRequest
	{
		PONY_INTERFACE_BODY(IRequest)

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

		/// @brief Cancels the request.
		/// @note The cancel is not immediate, it may take some time to cancel the operation.
		///       And because of it, the request may complete event if you requested a cancel.
		virtual void Cancel() = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure or cancel.
		virtual void Wait() const noexcept = 0;
	};
}
