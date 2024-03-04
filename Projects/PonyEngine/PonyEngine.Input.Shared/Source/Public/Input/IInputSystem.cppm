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

namespace PonyEngine::Input
{
	/// @brief Input system interface.
	export class IInputSystem : public Core::ISystem
	{
	public:
		/// @brief Registers an action that's raised if the event meets the conditions.
		/// @param event Condition.
		/// @param action Action.
		/// @return Registration id. It's used to unregister.
		virtual std::size_t RegisterAction(Event event, std::function<void()> action) = 0;
		/// @brief Unregisters an action by id.
		/// @param id Action id.
		virtual void UnregisterAction(std::size_t id) = 0;

	protected:
		inline virtual ~IInputSystem() noexcept = default;
	};
}
