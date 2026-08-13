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

export module PonyEngine.Resource.Ext:IResourceLoadHandler;

import std;

export namespace PonyEngine::Resource
{
	/// @brief Resource load handler.
	class IResourceLoadHandler
	{
		PONY_INTERFACE_BODY(IResourceLoadHandler)

		/// @brief Sets the success.
		/// @param mainResource Main resource.
		/// @param resources Resources. Must have all requested resource types.
		virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) = 0;
		/// @brief Sets the failure.
		/// @param exception Exception.
		virtual void SetFailure(const std::exception_ptr& exception) = 0;
		/// @brief Cancels the request.
		virtual void SetCancel() = 0;
	};
}
