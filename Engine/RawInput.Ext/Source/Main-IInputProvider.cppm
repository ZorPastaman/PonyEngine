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

export module PonyEngine.RawInput.Ext:IInputProvider;

import :IDeviceRegistry;
import :IInputRegistry;

export namespace PonyEngine::RawInput
{
	/// @brief Input provider.
	class IInputProvider
	{
		PONY_INTERFACE_BODY(IInputProvider)

		/// @brief Invoked before a first tick.
		/// @param deviceRegistry Device registry.
		/// @note The function is always called on a main thread.
		virtual void Begin(IDeviceRegistry& deviceRegistry) = 0;
		/// @brief Invoked after a last tick.
		/// @param deviceRegistry Device registry.
		/// @note The function is always called on a main thread.
		virtual void End(IDeviceRegistry& deviceRegistry) = 0;
		/// @brief Ticks the provider.
		/// @param deviceRegistry Device registry.
		/// @param inputRegistry Input registry.
		/// @note The function is always called on a main thread.
		virtual void Tick(IDeviceRegistry& deviceRegistry, IInputRegistry& inputRegistry) = 0;
	};
}
