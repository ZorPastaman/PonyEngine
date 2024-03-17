/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:IInputSystem;

import <cstddef>;
import <functional>;

import PonyEngine.Core;

import :Event;
import :Handle;

namespace PonyEngine::Input
{
	/// @brief Input system interface.
	export class IInputSystem : public Core::ISystem
	{
	public:
		/// @brief Registers an action that's raised if the event meets the conditions.
		/// @param event Condition.
		/// @param action Action.
		/// @return Registration handle. It's used to unregister.
		virtual Handle RegisterAction(Event event, std::function<void()> action) = 0;
		/// @brief Unregisters an action by its handle.
		/// @param handle Action handle.
		virtual void UnregisterAction(Handle handle) = 0;

	protected:
		inline virtual ~IInputSystem() noexcept = default;
	};
}
