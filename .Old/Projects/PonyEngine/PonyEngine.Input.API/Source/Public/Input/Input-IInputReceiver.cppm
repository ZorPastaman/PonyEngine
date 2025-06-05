/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Input:IInputReceiver;

import <functional>;

export namespace PonyEngine::Input
{
	/// @brief Input receiver. It executes a function when a bound to it event is invoked.
	class IInputReceiver
	{
		INTERFACE_BODY(IInputReceiver)

		/// @brief Resets the receiver. it sets an empty action.
		virtual void Reset() noexcept = 0;
		/// @brief Gets the action.
		/// @return Action that is called on a receiver event.
		[[nodiscard("Pure function")]]
		virtual const std::function<void(float)>& Action() const noexcept = 0;
		/// @brief Sets the action.
		/// @param action Action that is called on a receiver event.
		virtual void Action(const std::function<void(float)>& action) noexcept = 0;
	};
}
