/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:IInputSystem;

import <functional>;

import :Event;
import :Handle;

export namespace PonyEngine::Input
{
	/// @brief Input system.
	class IInputSystem
	{
	public:
		IInputSystem(const IInputSystem&) = delete;
		IInputSystem(IInputSystem&&) = delete;

		/// @brief Registers the action that's raised if the event meets the condition.
		/// @param event Condition.
		/// @param action Action.
		/// @return Registration handle. It's used to unregister.
		[[nodiscard("Pure function")]]
		virtual Handle RegisterAction(const Event& event, const std::function<void()>& action) = 0;
		/// @brief Unregisters an action by its handle.
		/// @param handle Action handle.
		virtual void UnregisterAction(Handle handle) = 0;

		IInputSystem& operator =(const IInputSystem&) = delete;
		IInputSystem& operator =(IInputSystem&&) = delete;

	protected:
		[[nodiscard("Pure constructor")]]
		IInputSystem() noexcept = default;

		~IInputSystem() noexcept = default;
	};
}
