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

export module PonyEngine.File:IWriteHandler;

import :IWriteRequest;

export namespace PonyEngine::File
{
	/// @brief Write request handler.
	class IWriteHandler
	{
		PONY_INTERFACE_BODY(IWriteHandler)

		/// @brief Invoked on a request finish event.
		/// @param request Request.
		virtual void OnCompleted(const IWriteRequest& request) = 0;
		/// @brief Invoked on a request cancel event.
		/// @param request Request.
		virtual void OnCanceled(const IWriteRequest& request) = 0;
	};
}
