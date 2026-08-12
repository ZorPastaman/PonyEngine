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

export module PonyEngine.File:IReadRequest;

import std;

import :IRequest;
import :ReadParams;

export namespace PonyEngine::File
{
	/// @brief Read request observer.
	class IReadObserver;

	/// @brief Read request.
	class IReadRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IReadRequest)

		/// @brief Gets the request params.
		/// @return Request params.
		[[nodiscard("Pure function")]]
		virtual const ReadParams& Params() const noexcept = 0;

		/// @brief Adds the observer.
		/// @param observer Observer to add. Must be removed before the request destruction.
		virtual void AddObserver(IReadObserver& observer) const = 0;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		virtual void RemoveObserver(IReadObserver& observer) const = 0;
	};

	/// @brief Read request observer.
	class IReadObserver
	{
		PONY_INTERFACE_BODY(IReadObserver)

		/// @brief Invoked on a request status changed.
		/// @param request Request.
		virtual void OnStatusChanged(const IReadRequest& request) noexcept = 0;
	};
}
