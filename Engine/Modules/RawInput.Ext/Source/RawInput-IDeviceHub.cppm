/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.RawInput.Ext:IDeviceHub;

import std;

import PonyEngine.RawInput;

import :DeviceParams;
import :IDeviceController;

export namespace PonyEngine::RawInput
{
	/// @brief Device hub.
	class IDeviceHub
	{
		PONY_INTERFACE_BODY(IDeviceHub)

		/// @brief Registers a new device.
		/// @param deviceController Device controller. Must be kept alive till the device is unregistered. The same controller may be used for many devices.
		/// @param isConnected Is the device connected?
		/// @param params Device parameters.
		/// @return Device handle. Must be used to unregister a device before a destruction of the raw input service.
		/// @note @note Must be called on a main thread.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(IDeviceController& deviceController, bool isConnected, const DeviceParams& params) = 0;
		/// @brief Unregisters a device.
		/// @param deviceHandle Device handle.
		/// @param deviceController Device controller.
		/// @note @note Must be called on a main thread.
		virtual void UnregisterDevice(DeviceHandle deviceHandle, IDeviceController& deviceController) = 0;

		/// @brief Makes an axis from the axis string.
		/// @param axis Axis string.
		/// @return Axis.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual Axis MakeAxis(std::string_view axis) = 0;
		/// @brief Checks if the @p axis is valid.
		/// @param axis Axis id.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsAxisValid(Axis axis) const = 0;
		/// @brief Gets an original axis string.
		/// @param axis Axis. Must be valid.
		/// @return Axis string.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetAxisString(Axis axis) const = 0;
		/// @brief Makes a device type from the device type string.
		/// @param deviceType Device type string.
		/// @return Device type.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual struct DeviceType MakeDeviceType(std::string_view deviceType) = 0;
		/// @brief Checks if the @p deviceType is valid.
		/// @param deviceType Device type.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsDeviceTypeValid(struct DeviceType deviceType) const = 0;
		/// @brief Gets an original device type string.
		/// @param deviceType Device type. Must be valid.
		/// @return Device type string.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetDeviceTypeString(struct DeviceType deviceType) const = 0;
		/// @brief Makes a device style from the device style string.
		/// @param deviceStyle Device style string.
		/// @return Device style.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual struct DeviceStyle MakeDeviceStyle(std::string_view deviceStyle) = 0;
		/// @brief Checks if the @p deviceStyle is valid.
		/// @param deviceStyle Device style.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsDeviceStyleValid(struct DeviceStyle deviceStyle) const = 0;
		/// @brief Gets an original device style string.
		/// @param deviceStyle Device style. Must be valid.
		/// @return Device style string.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetDeviceStyleString(struct DeviceStyle deviceStyle) const = 0;
	};
}
