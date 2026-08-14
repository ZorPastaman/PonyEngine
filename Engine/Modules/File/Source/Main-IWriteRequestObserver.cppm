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

export module PonyEngine.File:IWriteRequestObserver;

import std;

export namespace PonyEngine::File
{
	/// @brief Write request observer.
	class IWriteRequestObserver
	{
		PONY_INTERFACE_BODY(IWriteRequestObserver)

		/// @brief Invoked on a success.
		/// @param byteCount How many bytes were transferred.
		virtual void OnSuccess(std::size_t byteCount) noexcept = 0;
		/// @brief Invoked on a failure.
		/// @param exception Exception.
		virtual void OnFailure(const std::exception_ptr& exception) noexcept = 0;
		/// @brief Invoked on cancel.
		virtual void OnCancel() noexcept = 0;
	};
}
