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

export module PonyEngine.File:IRequest;

import std;

import PonyEngine.Async;

export namespace PonyEngine::File
{
	/// @brief Request.
	class IRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IRequest)

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
	};
}
