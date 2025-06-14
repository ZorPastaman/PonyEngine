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

export module PonyEngine.Input:IInputSystem;

import <memory>;
import <string_view>;

import :IInputReceiver;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class IInputSystem
	{
		INTERFACE_BODY(IInputSystem)

		/// @brief Creates a receiver for input events.
		/// @param id Input ID.
		/// @return Input receiver.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IInputReceiver> CreateReceiver(std::string_view id) = 0;

		/// @brief Gets the input state - a sum of all inputs with the same ID.
		/// @param id Input ID.
		/// @return Input state.
		[[nodiscard("Pure function")]]
		virtual float State(std::string_view id) const noexcept = 0;
	};
}
