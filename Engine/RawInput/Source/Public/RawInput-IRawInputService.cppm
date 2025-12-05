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

export module PonyEngine.RawInput:IRawInputService;

import std;

import PonyEngine.Math;

import :Axis;
import :AxisId;
import :DeviceHandle;
import :DeviceType;
import :DeviceTypeId;
import :IDevice;
import :IDeviceObserver;
import :IRawInputObserver;

export namespace PonyEngine::Input
{
	/// @brief Raw input service.
	class IRawInputService
	{
		INTERFACE_BODY(IRawInputService)

		/// @brief Gets an axis value.
		/// @param axis Axis.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		virtual float Value(AxisId axis) const noexcept = 0;
		/// @brief Gets an axis value from a specific device.
		/// @param axis Axis
		/// @param deviceHandle Device handle.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		virtual float Value(AxisId axis, DeviceHandle deviceHandle) const noexcept = 0;

		/// @brief Gets a last device reported its input.
		/// @return Last input device.
		/// @remark The value is updated each frame. If no device reported an input this frame, the return value is invalid.
		[[nodiscard("Pure function")]]
		virtual DeviceHandle LastInputDevice() const noexcept = 0;

		/// @brief Gets the device count.
		/// @return Device count.
		[[nodiscard("Pure function")]]
		virtual std::size_t DeviceCount() const noexcept = 0;
		/// @brief Gets a device handle.
		/// @param index Device index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		virtual DeviceHandle Device(std::size_t index) const = 0;
		/// @brief Is the device handle valid?
		/// @param deviceHandle Device handle.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Checks if the device is connected.
		/// @param deviceHandle Device handle.
		/// @return @a True if it's connected; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DeviceHandle deviceHandle) const = 0;
		/// @brief Gets a device by its handle.
		/// @param deviceHandle Device handle.
		/// @return Device.
		[[nodiscard("Pure function")]]
		virtual IDevice& Device(DeviceHandle deviceHandle) = 0;
		/// @brief Gets a device by its handle.
		/// @param deviceHandle Device handle.
		/// @return Device.
		[[nodiscard("Pure function")]]
		virtual const IDevice& Device(DeviceHandle deviceHandle) const = 0;

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

		/// @brief Adds the global device observer.
		/// @param observer Device observer.
		virtual void AddObserver(IDeviceObserver& observer) = 0;
		/// @brief Removes the global device observer.
		/// @param observer Device observer.
		virtual void RemoveObserver(IDeviceObserver& observer) noexcept = 0;
		/// @brief Adds the device observer.
		/// @param deviceHandle Device handle.
		/// @param observer Device observer.
		virtual void AddObserver(DeviceHandle deviceHandle, IDeviceObserver& observer) = 0;
		/// @brief Removes the device observer.
		/// @param deviceHandle Device handle.
		/// @param observer Device observer.
		virtual void RemoveObserver(DeviceHandle deviceHandle, IDeviceObserver& observer) noexcept = 0;
		/// @brief Adds the global raw input observer.
		/// @param observer Raw input observer.
		virtual void AddObserver(IRawInputObserver& observer) = 0;
		/// @brief Removes the global raw input observer.
		/// @param observer Raw input observer.
		virtual void RemoveObserver(IRawInputObserver& observer) noexcept = 0;
		/// @brief Adds the device raw input observer.
		/// @param deviceHandle Device handle.
		/// @param observer Raw input observer.
		virtual void AddObserver(DeviceHandle deviceHandle, IRawInputObserver& observer) = 0;
		/// @brief Removes the device raw input observer.
		/// @param deviceHandle Device handle.
		/// @param observer Raw input observer.
		virtual void RemoveObserver(DeviceHandle deviceHandle, IRawInputObserver& observer) noexcept = 0;
	};
}
