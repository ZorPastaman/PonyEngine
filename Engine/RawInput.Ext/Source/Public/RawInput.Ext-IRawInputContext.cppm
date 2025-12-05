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

import :DeviceData;

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
		/// @param data Device data.
		/// @return Device handle.
		[[nodiscard("Must be used to unregister")]]
		virtual DeviceHandle RegisterDevice(const DeviceData& data) = 0;
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
	};
}
