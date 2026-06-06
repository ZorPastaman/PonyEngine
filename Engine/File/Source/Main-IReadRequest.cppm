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

export module PonyEngine.File:IReadRequest;

import std;

import :IRequest;
import :ReadParams;

export namespace PonyEngine::File
{
	class IReadRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IReadRequest)

		[[nodiscard("Pure function")]]
		virtual const ReadParams& Params() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual std::size_t ReadByteCount() const = 0;
	};
}
