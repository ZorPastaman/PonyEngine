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

export module PonyEngine.Resource.Ext:IResourceLoadRequest;

import std;

import PonyEngine.Async;

export namespace PonyEngine::Resource
{
	/// @brief Resource load request.
	class IResourceLoadRequest : public Async::IRequest
	{
		PONY_INTERFACE_BODY(IResourceLoadRequest)

		/// @brief Gets a main resource.
		/// @return Main resource.
		/// @not It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<const void> MainResource() const = 0;
		/// @brief Gets resource interfaces.
		/// @return Resource interfaces. Its order must follow the order of the interface types in the context.
		/// @not It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		virtual std::span<const void* const> ResourceInterfaces() const = 0;
		/// @brief Gets exceptions that occured during the request execution.
		/// @return Exceptions.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::exception_ptr> Exceptions() const = 0;
	};
}
