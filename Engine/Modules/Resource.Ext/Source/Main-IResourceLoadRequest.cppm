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

import PonyEngine.Async;

export namespace PonyEngine::Resource
{
	/// @brief Resource load request.
	class IResourceLoadRequest
	{
		PONY_INTERFACE_BODY(IResourceLoadRequest)

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		virtual Async::RequestStatus Status() const noexcept = 0;
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
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const = 0;

		/// @brief Cancels the request.
		virtual void Cancel() = 0;

		/// @brief Makes the thread sleep till the request is completed with success or failure or cancel.
		virtual void Wait() const noexcept = 0;
	};
}
