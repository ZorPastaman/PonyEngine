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

export module PonyEngine.Input:IDeviceObserver;

import :DeviceHandle;

export namespace PonyEngine::Input
{
	/// @brief Device observer.
	class IDeviceObserver
	{
		INTERFACE_BODY(IDeviceObserver)

		/// @brief Invoked when a new device is added.
		/// @param deviceHandle New device handle.
		virtual void OnDeviceAdded(DeviceHandle deviceHandle) {};
		/// @brief Invoked when a device is removed.
		/// @param deviceHandle New device handle.
		virtual void OnDeviceRemoved(DeviceHandle deviceHandle) {};
		/// @brief Invoked when a device connection change.
		/// @param deviceHandle Device handle.
		/// @param isConnected @a True if it's connected; @a false otherwise.
		virtual void OnDeviceConnectionChanged(DeviceHandle deviceHandle, bool isConnected) {};
	};
}
