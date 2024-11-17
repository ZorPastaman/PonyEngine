/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Input:IInputSystem;

import <functional>;

import :Event;
import :Handle;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class IInputSystem
	{
		INTERFACE_BODY(IInputSystem)

		/// @brief Registers the action that's raised if the event meets the condition.
		/// @param event Condition.
		/// @param action Action.
		/// @return Registration handle. It's used to unregister.
		virtual Handle RegisterAction(const Event& event, const std::function<void()>& action) = 0;
		/// @brief Unregisters an action by its handle.
		/// @param handle Action handle.
		virtual void UnregisterAction(Handle handle) = 0;
	};
}
