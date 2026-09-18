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

export module PonyEngine.File:IReadRequest;

import std;

import :IRequest;
import :ReadParams;

export namespace PonyEngine::File
{
	/// @brief Read request.
	class IReadRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IReadRequest)

		/// @brief Gets the request params.
		/// @return Request params.
		[[nodiscard("Pure function")]]
		virtual const ReadParams& Params() const noexcept = 0;
	};
}
