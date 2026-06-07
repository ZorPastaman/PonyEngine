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

export module PonyEngine.File:IWriteRequest;

import std;

import :IRequest;
import :WriteParams;

export namespace PonyEngine::File
{
	class IWriteRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IWriteRequest)

		[[nodiscard("Pure function")]]
		virtual const WriteParams& Params() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::size_t WrittenByteCount() const = 0;
	};
}
