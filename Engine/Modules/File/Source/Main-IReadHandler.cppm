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

export module PonyEngine.File:IReadHandler;

import :IReadRequest;

export namespace PonyEngine::File
{
	/// @brief Read request handler.
	class IReadHandler
	{
		PONY_INTERFACE_BODY(IReadHandler)

		/// @brief Invoked on a request complete event.
		/// @param request Request.
		virtual void OnCompleted(const IReadRequest& request) noexcept = 0;
		/// @brief Invoked on a request cancel event.
		/// @param request Request.
		virtual void OnCanceled(const IReadRequest& request) noexcept = 0;
	};
}
