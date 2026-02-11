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

export module PonyEngine.RawInput:IDeviceObserver;

import :ConnectionEvent;
import :DeviceHandle;

export namespace PonyEngine::RawInput
{
	/// @brief Device observer.
	/// @note The observer functions are always called during a raw input service tick.
	class IDeviceObserver
	{
		PONY_INTERFACE_BODY(IDeviceObserver)

		/// @brief Invoked when a new device is added.
		/// @param deviceHandle New device handle.
		virtual void OnDeviceAdded(DeviceHandle deviceHandle) {};
		/// @brief Invoked when a device is removed.
		/// @param deviceHandle New device handle.
		virtual void OnDeviceRemoved(DeviceHandle deviceHandle) {};
		/// @brief Invoked when a device connection change.
		/// @param deviceHandle Device handle.
		/// @param connection Connection event.
		virtual void OnDeviceConnectionChanged(DeviceHandle deviceHandle, const ConnectionEvent& connection) {};
	};
}
