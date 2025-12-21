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

export module PonyEngine.RawInput.Ext:IRawInputContext;

import PonyEngine.Application.Ext;
import PonyEngine.RawInput;
import PonyEngine.Log;

import :FeatureEntry;

export namespace PonyEngine::Input
{
	/// @brief Raw input context.
	class IRawInputContext
	{
		INTERFACE_BODY(IRawInputContext)

		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Registers a new device.
		/// @param deviceType Device type.
		/// @param deviceName Device name.
		/// @param isConnected Is the device connected?
		/// @param features Device features.
		/// @return Device handle.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(DeviceTypeId deviceType, std::string_view deviceName, bool isConnected, 
			std::span<const FeatureEntry> features = std::span<const FeatureEntry>()) = 0;
		/// @brief Unregisters a device.
		/// @param deviceHandle Device handle.
		virtual void UnregisterDevice(DeviceHandle deviceHandle) = 0;

		/// @brief Adds an input.
		/// @param deviceHandle Device handle.
		/// @param input Raw input event.
		virtual void AddInput(DeviceHandle deviceHandle, const RawInputEvent& input) = 0;
		/// @brief Changes a connection status of a device.
		/// @param deviceHandle Device handle.
		/// @param connection Connection event.
		virtual void Connect(DeviceHandle deviceHandle, const ConnectionEvent& connection) = 0;

		/// @brief Calculates a hash for the @p axis.
		/// @param axis Axis.
		/// @return Axis hash.
		[[nodiscard("Pure function")]]
		virtual AxisId Hash(const Axis& axis) = 0;
		/// @brief Gets an original axis from the hash value.
		/// @param axisId Axis hash.
		/// @return Axis.
		[[nodiscard("Pure function")]]
		virtual const Axis& Unhash(AxisId axisId) const = 0;
		/// @brief Checks if the @p axisId is valid.
		/// @param axisId Axis id.
		/// @return @a true if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(AxisId axisId) const noexcept = 0;
		/// @brief Calculates a hash for the @p deviceType.
		/// @param deviceType Device type.
		/// @return Device type hash.
		[[nodiscard("Pure function")]]
		virtual DeviceTypeId Hash(const DeviceType& deviceType) = 0;
		/// @brief Gets an original device type from the hash value.
		/// @param deviceTypeId Device type hash.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		virtual const DeviceType& Unhash(DeviceTypeId deviceTypeId) = 0;
		/// @brief Checks if the @p deviceTypeId is valid.
		/// @param deviceTypeId Device type id.
		/// @return @a true if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceTypeId deviceTypeId) const noexcept = 0;
	};
}
