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

export module PonyEngine.RawInput.Ext:IInputRegistry;

import PonyEngine.RawInput;

export namespace PonyEngine::RawInput
{
	/// @brief Input registry. Used to add input and connection events.
	class IInputRegistry
	{
		PONY_INTERFACE_BODY(IInputRegistry)

		/// @brief Adds an input.
		/// @param deviceHandle Device handle.
		/// @param input Raw input event.
		/// @note @note Must be called on the same thread on which the interface was passed.
		virtual void AddInput(DeviceHandle deviceHandle, const RawInputEvent& input) = 0;
		/// @brief Changes a connection status of a device.
		/// @param deviceHandle Device handle.
		/// @param connection Connection event.
		/// @note @note Must be called on the same thread on which the interface was passed.
		virtual void Connect(DeviceHandle deviceHandle, const ConnectionEvent& connection) = 0;
	};
}
