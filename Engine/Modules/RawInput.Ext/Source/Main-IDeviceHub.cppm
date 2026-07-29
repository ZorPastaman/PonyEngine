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

export module PonyEngine.RawInput.Ext:IDeviceHub;

import std;

import PonyEngine.RawInput;

import :IDeviceController;

export namespace PonyEngine::RawInput
{
	/// @brief Device hub.
	class IDeviceHub
	{
		PONY_INTERFACE_BODY(IDeviceHub)

		/// @brief Registers a new device.
		/// @param deviceController Device controller. Must be kept alive till the device is unregistered. The same controller may be used for many devices.
		/// @param deviceName Device name.
		/// @param deviceType Device type.
		/// @param isConnected Is the device connected?
		/// @return Device handle. Must be used to unregister a device before a destruction of the raw input service.
		/// @note @note Must be called on a main thread.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(IDeviceController& deviceController, std::string_view deviceName, DeviceType deviceType, bool isConnected) = 0;
		/// @brief Unregisters a device.
		/// @param deviceController Device controller.
		/// @param deviceHandle Device handle.
		/// @note @note Must be called on a main thread.
		virtual void UnregisterDevice(IDeviceController& deviceController, DeviceHandle deviceHandle) = 0;
	};
}
