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

export module PonyEngine.File:IWriteRequest;

import std;

import :IRequest;
import :WriteParams;

export namespace PonyEngine::File
{
	/// @brief Write request observer.
	class IWriteObserver;

	/// @brief Write request.
	class IWriteRequest : public IRequest
	{
		PONY_INTERFACE_BODY(IWriteRequest)

		/// @brief Gets the request params.
		/// @return Request params.
		[[nodiscard("Pure function")]]
		virtual const WriteParams& Params() const noexcept = 0;

		/// @brief Adds the observer.
		/// @param observer Observer to add. Must be removed before the request destruction.
		virtual void AddObserver(IWriteObserver& observer) const = 0;
		/// @brief Removes the observer.
		/// @param observer Observer to remove.
		virtual void RemoveObserver(IWriteObserver& observer) const = 0;
	};

	/// @brief Write request observer.
	class IWriteObserver
	{
		PONY_INTERFACE_BODY(IWriteObserver)

		/// @brief Invoked on a request status change.
		/// @param request Request.
		virtual void OnStatusChanged(const IWriteRequest& request) noexcept = 0;
	};
}
