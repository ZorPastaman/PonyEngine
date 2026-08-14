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

export module PonyEngine.Resource:IResourceRequestObserver;

import :IResourceRequestResult;

export namespace PonyEngine::Resource
{
	/// @brief Resource request observer.
	class IResourceRequestObserver
	{
		PONY_INTERFACE_BODY(IResourceRequestObserver)

		/// @brief Invoked on a success.
		/// @param result Resource request result.
		virtual void OnSuccess(const std::shared_ptr<const IResourceRequestResult>& result) noexcept = 0;
		/// @brief Invoked on a failure.
		/// @param exception Exception.
		virtual void OnFailure(const std::exception_ptr& exception) noexcept = 0;
		/// @brief Invoked on cancel.
		virtual void OnCancel() noexcept = 0;
	};
}
