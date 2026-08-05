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

export module PonyEngine.File.Impl:IRequestController;

export namespace PonyEngine::File
{
	/// @brief Request controller
	class IRequestController
	{
		PONY_INTERFACE_BODY(IRequestController)

		/// @brief Cancels the request.
		virtual void Cancel() = 0;
	};
}
