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

import :IResourceLoadRequestObserver;

export namespace PonyEngine::Resource
{
	/// @brief Resource load request.
	class IResourceLoadRequest
	{
		PONY_INTERFACE_BODY(IResourceLoadRequest)

		/// @brief Checks if the operation cancel is requested.
		/// @return @a True if it's requested; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsCancelRequested() const noexcept = 0;

		/// @brief Sets the observer.
		/// @param observer Observer to set. May be nullptr.
		virtual void SetObserver(IResourceLoadRequestObserver* observer) = 0;

		/// @brief Sets the success.
		/// @param resources Resources. Must have all requested resource types.
		virtual void SetSuccess(std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> resources) = 0;
		/// @brief Sets the failure.
		/// @param exception Exception.
		virtual void SetFailure(const std::exception_ptr& exception) = 0;
		/// @brief Sets canceled. May be set only if requested.
		virtual void SetCanceled() = 0;
	};
}
