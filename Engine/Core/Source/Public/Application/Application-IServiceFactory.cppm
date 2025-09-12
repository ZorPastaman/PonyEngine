/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application:IServiceFactory;

import :IApplicationContext;
import :ServiceData;

export namespace PonyEngine::Application
{
	/// @brief Service factory.
	class IServiceFactory
	{
		INTERFACE_BODY(IServiceFactory)

		/// @brief Creates a service.
		/// @param application Application context.
		/// @return Created service data.
		[[nodiscard("Redundant call")]]
		virtual ServiceData Create(IApplicationContext& application) = 0;
	};
}
