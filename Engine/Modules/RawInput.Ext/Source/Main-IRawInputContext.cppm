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

export namespace PonyEngine::RawInput
{
	/// @brief Raw input context.
	class IRawInputContext
	{
		PONY_INTERFACE_BODY(IRawInputContext)

		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept = 0;
		/// @brief Gets the application context.
		/// @return Application context.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept = 0;

		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual Log::ILogger& Logger() noexcept = 0;
		/// @brief Gets the logger.
		/// @return Logger.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& Logger() const noexcept = 0;

		/// @brief Calculates a hash for the @p axis.
		/// @param axis Axis.
		/// @return Axis hash.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual AxisID HashAxis(std::string_view axis) = 0;
		/// @brief Gets an original axis from the hash value.
		/// @param axisId Axis hash.
		/// @return Axis.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view UnhashAxis(AxisID axisId) const = 0;
		/// @brief Checks if the @p axisId is valid.
		/// @param axisId Axis id.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsAxisValid(AxisID axisId) const noexcept = 0;
		/// @brief Calculates a hash for the @p deviceType.
		/// @param deviceType Device type.
		/// @return Device type hash.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual DeviceTypeID HashDeviceType(std::string_view deviceType) = 0;
		/// @brief Gets an original device type from the hash value.
		/// @param deviceTypeId Device type hash.
		/// @return Device type.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::string_view UnhashDeviceType(DeviceTypeID deviceTypeId) = 0;
		/// @brief Checks if the @p deviceTypeId is valid.
		/// @param deviceTypeId Device type id.
		/// @return @a true if it's valid; @a false otherwise.
		/// @note This function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsDeviceTypeValid(DeviceTypeID deviceTypeId) const noexcept = 0;
	};
}
