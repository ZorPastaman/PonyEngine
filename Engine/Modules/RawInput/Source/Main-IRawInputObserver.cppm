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

export module PonyEngine.RawInput:IRawInputObserver;

import :ConnectionEvent;
import :DeviceHandle;
import :RawInputEvent;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input observer.
	class IRawInputObserver
	{
		PONY_INTERFACE_BODY(IRawInputObserver)

		/// @brief Invoked when a new device is added.
		/// @param deviceHandle New device handle.
		/// @note The function is called during a raw input service tick.
		virtual void OnDeviceAdded(DeviceHandle deviceHandle) {}
		/// @brief Invoked when a device is removed.
		/// @param deviceHandle New device handle.
		/// @note The function is called during a raw input service tick.
		virtual void OnDeviceRemoved(DeviceHandle deviceHandle) {}
		/// @brief Invoked when a device connection change.
		/// @param deviceHandle Device handle.
		/// @param connection Connection event.
		/// @note The function is called during a raw input service tick.
		virtual void OnDeviceConnectionChanged(DeviceHandle deviceHandle, const ConnectionEvent& connection) {}
		/// @brief Invoked on raw input event.
		/// @param deviceHandle Device handle.
		/// @param inputEvent Raw input event.
		/// @note The function is called during a raw input service tick.
		virtual void OnRawInput(DeviceHandle deviceHandle, const RawInputEvent& inputEvent) {}
	};
}
