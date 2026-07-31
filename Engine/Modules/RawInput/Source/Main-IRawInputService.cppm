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

import :Axis;
import :DeviceHandle;
import :DeviceStyle;
import :DeviceType;
import :IRawInputObserver;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input service.
	class IRawInputService
	{
		PONY_INTERFACE_BODY(IRawInputService)

		/// @brief Gets an axis value.
		/// @param axis Axis.
		/// @return Input float value.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual float Value(Axis axis) const noexcept = 0;
		/// @brief Gets an axis value from a specific device.
		/// @param axis Axis
		/// @param deviceHandle Device handle.
		/// @return Input float value.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual float Value(Axis axis, DeviceHandle deviceHandle) const noexcept = 0;

		/// @brief Gets a last device reported its input.
		/// @return Last input device.
		/// @remark The value is updated each frame. If no device reported an input this frame, the return value is invalid.
		/// @remark If the last input device was unregistered, the return value is invalid.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DeviceHandle LastInputDevice() const noexcept = 0;

		/// @brief Gets the device count.
		/// @return Device count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::size_t DeviceCount() const noexcept = 0;
		/// @brief Gets a device handle.
		/// @param index Device index. Must be less than the @p DeviceCount().
		/// @return Device handle.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DeviceHandle Device(std::size_t index) const noexcept = 0;
		/// @brief Is the device handle valid?
		/// @param deviceHandle Device handle.
		/// @return @a True if it's valid; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Checks if the device is connected.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return @a True if it's connected; @a false otherwise.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Gets a device name.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return Device name.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view DeviceName(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Gets a device type.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return Device type.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DeviceType DeviceType(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Gets a device style.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return Device style.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual DeviceStyle DeviceStyle(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Tries to find a device feature.
		/// @param deviceHandle Device handle. Must be valid.
		/// @param type Feature type.
		/// @return Feature or nullptr if not found.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual void* FindFeature(DeviceHandle deviceHandle, std::type_index type) const noexcept = 0;
		/// @brief Tries to find a device feature.
		/// @tparam T Feature type.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return Feature or nullptr if not found.
		/// @note The function must be called on a main thread.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindFeature(DeviceHandle deviceHandle) const noexcept;
		/// @brief Gets a device feature.
		/// @tparam T Feature type.
		/// @param deviceHandle Device handle. Must be valid.
		/// @return Feature.
		/// @note The function must be called on a main thread.
		template<typename T> [[nodiscard("Pure function")]]
		T& GetFeature(DeviceHandle deviceHandle) const;

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
		virtual bool IsAxisValid(Axis axis) const noexcept = 0;
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
		virtual bool IsDeviceTypeValid(struct DeviceType deviceType) const noexcept = 0;
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
		virtual bool IsDeviceStyleValid(struct DeviceStyle deviceStyle) const noexcept = 0;
		/// @brief Gets an original device style string.
		/// @param deviceStyle Device style. Must be valid.
		/// @return Device style string.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::string_view GetDeviceStyleString(struct DeviceStyle deviceStyle) const = 0;

		/// @brief Adds the global raw input observer.
		/// @param observer Raw input observer. Must be kept alive till it's removed.
		/// @note The function must be called on a main thread.
		virtual void AddObserver(IRawInputObserver& observer) = 0;
		/// @brief Removes the global raw input observer.
		/// @param observer Raw input observer.
		/// @note The function must be called on a main thread.
		virtual void RemoveObserver(IRawInputObserver& observer) = 0;
	};
}

namespace PonyEngine::RawInput
{
	template<typename T>
	T* IRawInputService::FindFeature(const DeviceHandle deviceHandle) const noexcept
	{
		return static_cast<T*>(FindFeature(deviceHandle, typeid(T)));
	}

	template<typename T>
	T& IRawInputService::GetFeature(const DeviceHandle deviceHandle) const
	{
		T* const feature = FindFeature<T>(deviceHandle);
		if (!feature) [[unlikely]]
		{
			throw std::logic_error("Feature not found");
		}

		return *feature;
	}
}
