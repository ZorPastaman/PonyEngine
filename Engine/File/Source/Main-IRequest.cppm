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

import :RequestStatus;

export namespace PonyEngine::File
{
	class IRequest
	{
		PONY_INTERFACE_BODY(IRequest)

		[[nodiscard("Pure function")]]
		virtual RequestStatus Status() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const = 0;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;

		virtual void Wait() const noexcept = 0;
	};
}
