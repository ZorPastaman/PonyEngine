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

export module PonyEngine.File:IWriteRequest;

import std;

import :IRequest;
import :WriteParams;

export namespace PonyEngine::File
{
	/// @brief Write request.
	class IWriteRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IWriteRequest)

		/// @brief Gets the request params.
		/// @return Request params.
		[[nodiscard("Pure function")]]
		virtual const WriteParams& Params() const noexcept = 0;
	};
}
