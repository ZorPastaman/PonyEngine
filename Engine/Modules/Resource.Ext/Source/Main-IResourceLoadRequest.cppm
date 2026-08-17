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

export module PonyEngine.Resource.Ext:IResourceLoadRequest;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource load request.
	class IResourceLoadRequest
	{
		PONY_INTERFACE_BODY(IResourceLoadRequest)

		/// @brief Stops the request.
		/// @note It mustn't call a handler after this function returns.
		virtual void Stop() = 0;
	};
}
