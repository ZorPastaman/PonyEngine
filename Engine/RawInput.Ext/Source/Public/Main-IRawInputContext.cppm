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
import PonyEngine.Log;
import PonyEngine.RawInput;

import :FeatureEntry;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input context.
	/// @note All the functions here except for the application and logger getters must be called only on constructor, begin, tick or end of an input provider.
	class IRawInputContext
	{
		PONY_INTERFACE_BODY(IRawInputContext)

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
		/// @return Device handle. Must be used to unregister a device before a destruction of the raw input service.
		/// @note This function mustn't be called concurrently with any other function here except for the application and logger getters.
		/// @note @note Must be called on a main thread.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(DeviceTypeId deviceType, std::string_view deviceName, bool isConnected, 
			std::span<const FeatureEntry> features = std::span<const FeatureEntry>()) = 0;
		/// @brief Unregisters a device.
		/// @param deviceHandle Device handle.
		/// @note This function mustn't be called concurrently with any other function here except for the application and logger getters.
		/// @note Must be called on a main thread.
		virtual void UnregisterDevice(DeviceHandle deviceHandle) = 0;

		/// @brief Adds an input.
		/// @param deviceHandle Device handle.
		/// @param input Raw input event.
		/// @note This function mustn't be called concurrently with any other function here except for the application and logger getters.
		/// @note Must be called on a main thread.
		virtual void AddInput(DeviceHandle deviceHandle, const RawInputEvent& input) = 0;
		/// @brief Changes a connection status of a device.
		/// @param deviceHandle Device handle.
		/// @param connection Connection event.
		/// @note This function mustn't be called concurrently with any other function here except for the application and logger getters.
		/// @note Must be called on a main thread.
		virtual void Connect(DeviceHandle deviceHandle, const ConnectionEvent& connection) = 0;

		/// @brief Calculates a hash for the @p axis.
		/// @param axis Axis.
		/// @return Axis hash.
		/// @note This function mustn't be called concurrently with @p RegisterDevice(), @p UnregisterDevice(), @p AddInput(), @p Connect(), @p Unhash(AxisId) and @p IsValid(AxisId).
		[[nodiscard("Pure function")]]
		virtual AxisId Hash(const Axis& axis) = 0;
		/// @brief Gets an original axis from the hash value.
		/// @param axisId Axis hash.
		/// @return Axis.
		/// @note This function mustn't be called concurrently with @p Hash(AxisId).
		[[nodiscard("Pure function")]]
		virtual const Axis& Unhash(AxisId axisId) const = 0;
		/// @brief Checks if the @p axisId is valid.
		/// @param axisId Axis id.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note This function mustn't be called concurrently with @p Hash(AxisId).
		[[nodiscard("Pure function")]]
		virtual bool IsValid(AxisId axisId) const noexcept = 0;
		/// @brief Calculates a hash for the @p deviceType.
		/// @param deviceType Device type.
		/// @return Device type hash.
		/// @note This function mustn't be called concurrently with @p RegisterDevice(), @p UnregisterDevice(), @p AddInput(), @p Connect(), @p Unhash(DeviceTypeId) and @p IsValid(DeviceTypeId).
		[[nodiscard("Pure function")]]
		virtual DeviceTypeId Hash(const DeviceType& deviceType) = 0;
		/// @brief Gets an original device type from the hash value.
		/// @param deviceTypeId Device type hash.
		/// @return Device type.
		/// @note This function mustn't be called concurrently with @p Hash(DeviceTypeId).
		[[nodiscard("Pure function")]]
		virtual const DeviceType& Unhash(DeviceTypeId deviceTypeId) = 0;
		/// @brief Checks if the @p deviceTypeId is valid.
		/// @param deviceTypeId Device type id.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note This function mustn't be called concurrently with @p Hash(DeviceTypeId).
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceTypeId deviceTypeId) const noexcept = 0;
	};
}
