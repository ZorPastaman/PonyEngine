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

export module PonyEngine.Async:IRequest;

import std;

import :RequestStatus;

export namespace PonyEngine::Async
{
	/// @brief Async request.
	class IRequest
	{
		PONY_INTERFACE_BODY(IRequest)

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual RequestStatus Status() const noexcept = 0;
		/// @brief Requests a cancel.
		/// @remark The request may ignore it or delay the cancel request.
		virtual void Cancel() = 0;
		/// @brief Wait for the request to finish.
		virtual void Wait() const noexcept = 0;
	};
}
