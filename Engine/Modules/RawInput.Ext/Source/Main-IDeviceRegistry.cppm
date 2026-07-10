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

export module PonyEngine.RawInput.Ext:IDeviceRegistry;

import std;

import PonyEngine.RawInput;

import :FeatureEntry;

export namespace PonyEngine::RawInput
{
	/// @brief Device registry. Used to register and unregister devices.
	class IDeviceRegistry
	{
		PONY_INTERFACE_BODY(IDeviceRegistry)

		/// @brief Registers a new device.
		/// @param deviceType Device type.
		/// @param deviceName Device name.
		/// @param isConnected Is the device connected?
		/// @param features Device features.
		/// @return Device handle. Must be used to unregister a device before a destruction of the raw input service.
		/// @note @note Must be called on the same thread on which the interface was passed.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(DeviceTypeID deviceType, std::string_view deviceName, bool isConnected,
			std::span<const FeatureEntry> features = std::span<const FeatureEntry>()) = 0;
		/// @brief Unregisters a device.
		/// @param deviceHandle Device handle.
		/// @note @note Must be called on the same thread on which the interface was passed.
		virtual void UnregisterDevice(DeviceHandle deviceHandle) = 0;
	};
}
