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

export module PonyEngine.Input:IInputService;

import std;

import PonyEngine.Math;

import :ActionBindingHandle;
import :ActionId;
import :Axis;
import :AxisBinding;
import :DeviceHandle;
import :IDeviceObserver;
import :IInputObserver;
import :IRawInputObserver;

export namespace PonyEngine::Input
{
	/// @brief Input service.
	class IInputService
	{
		INTERFACE_BODY(IInputService)

		/// @brief Gets an axis count for the action.
		/// @param actionId Action ID.
		/// @return Axis count; 0 if the action is not bound.
		[[nodiscard("Pure function")]]
		virtual std::size_t AxisCount(ActionId actionId) const noexcept = 0;
		/// @brief Gets values for the action.
		/// @param actionId Action ID.
		/// @param values Values. It sets all values according to the action axes.
		[[nodiscard("Pure function")]]
		virtual void Value(ActionId actionId, std::span<float> values) const noexcept = 0;
		/// @brief Gets a float value for the action first axis.
		/// @param actionId Action ID.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		float Value(ActionId actionId) const noexcept;
		/// @brief Gets a vector of float values for the action.
		/// @tparam Size Vector size.
		/// @param actionId Action ID.
		/// @return Input vector of float values. It sets all values according to the action axes.
		template<std::size_t Size> [[nodiscard("Pure function")]]
		Math::Vector<float, Size> ValueVector(ActionId actionId) const noexcept;
		/// @brief Gets values for the action from specific devices.
		/// @param deviceHandles Device handles.
		/// @param actionId Action ID.
		/// @param values Values. It sets all values according to the action axes.
		[[nodiscard("Pure function")]]
		virtual void Value(std::span<const DeviceHandle> deviceHandles, ActionId actionId, std::span<float> values) const noexcept = 0;
		/// @brief Gets boolean values for the action from specific devices.
		/// @param deviceHandles Device handles.
		/// @param actionId Action ID.
		/// @param values Values. It sets all values according to the action axes.
		/// @param threshold Threshold for boolean conversion. If the absolute value is greater than the threshold, the boolean value is @a true; otherwise, it's @a false.
		[[nodiscard("Pure function")]]
		virtual void Value(std::span<const DeviceHandle> deviceHandles, ActionId actionId, std::span<bool> values, float threshold = 0.4f) const noexcept = 0;
		/// @brief Gets a float value for the action first axis from specific devices.
		/// @param deviceHandles Device handles.
		/// @param actionId Action ID.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		float Value(std::span<const DeviceHandle> deviceHandles, ActionId actionId) const noexcept;
		/// @brief Gets a vector of float values for the action from specific devices.
		/// @tparam Size Vector size.
		/// @param deviceHandles Device handles.
		/// @param actionId Action ID.
		/// @return Input vector of float values. It sets all values according to the action axes.
		template<std::size_t Size> [[nodiscard("Pure function")]]
		Math::Vector<float, Size> ValueVector(std::span<const DeviceHandle> deviceHandles, ActionId actionId) const noexcept;

		/// @brief Gets an axis value.
		/// @param layoutType Layout type.
		/// @param axisId Axis ID.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		virtual float Value(const std::type_info& layoutType, AxisIdType axisId) const noexcept = 0;
		/// @brief Gets an axis value.
		/// @tparam T Layout type.
		/// @param axisId Axis ID.
		/// @return Input float value.
		template<Layout T> [[nodiscard("Pure function")]]
		float Value(T axisId) const noexcept;
		/// @brief Gets an axis value from specific devices.
		/// @param deviceHandles Device handles.
		/// @param layoutType Layout type.
		/// @param axisId Axis ID.
		/// @return Input float value.
		[[nodiscard("Pure function")]]
		virtual float Value(std::span<const DeviceHandle> deviceHandles, const std::type_info& layoutType, AxisIdType axisId) const noexcept = 0;
		/// @brief Gets an axis value from specific devices.
		/// @tparam T Layout type.
		/// @param deviceHandles Device handles.
		/// @param axisId Axis ID.
		/// @return Input float value.
		template<Layout T> [[nodiscard("Pure function")]]
		float Value(std::span<const DeviceHandle> deviceHandles, T axisId) const noexcept;

		/// @brief Binds an action to axis bindings.
		/// @param actionId Action ID.
		/// @param axisBindings Axis bindings.
		/// @return Action binding handle to unbind later.
		virtual ActionBindingHandle Bind(ActionId actionId, std::span<const AxisBinding> axisBindings) = 0;
		/// @brief Unbinds an action binding.
		/// @param handle Action binding handle.
		virtual void Unbind(ActionBindingHandle handle) = 0;

		/// @brief Gets all device handles.
		/// @return Device handles.
		[[nodiscard("Pure function")]]
		virtual std::span<const DeviceHandle> Devices() const noexcept = 0;
		/// @brief Is the device handle valid?
		/// @param deviceHandle Device handle.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsValid(DeviceHandle deviceHandle) const noexcept = 0;
		/// @brief Gets all layout types supported by the device.
		/// @param deviceHandle Device handle.
		/// @return Layout types.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::reference_wrapper<const std::type_info>> Layouts(DeviceHandle deviceHandle) const = 0;
		/// @brief Checks if the device supports the layout.
		/// @param deviceHandle Device handle.
		/// @param layoutType Layout type.
		/// @return @a True if it supports; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasLayout(DeviceHandle deviceHandle, const std::type_info& layoutType) const;
		/// @brief Checks if the device supports the layout.
		/// @tparam T Layout type.
		/// @param deviceHandle Device handle.
		/// @return @a True if it supports; @a false otherwise.
		template<Layout T> [[nodiscard("Pure function")]]
		bool HasLayout(DeviceHandle deviceHandle) const;
		/// @brief Gets all feature types supported by the device.
		/// @param deviceHandle Device handle.
		/// @return Supported feature types.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::reference_wrapper<const std::type_info>> Features(DeviceHandle deviceHandle) const = 0;
		/// @brief Checks if the device supports the feature.
		/// @param deviceHandle Device handle.
		/// @param featureType Feature type.
		/// @return @a True if it supports; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasFeature(DeviceHandle deviceHandle, const std::type_info& featureType) const;
		/// @brief Checks if the device supports the feature.
		/// @tparam T Feature type.
		/// @param deviceHandle Device handle.
		/// @return @a True if it supports; @a false otherwise.
		template<typename T> [[nodiscard("Pure function")]]
		bool HasFeature(DeviceHandle deviceHandle) const;
		/// @brief Gets the device feature.
		/// @param deviceHandle Device handle.
		/// @param featureType Feature type.
		/// @return Feature; nullptr if it's not supported.
		[[nodiscard("Pure function")]]
		virtual void* Feature(DeviceHandle deviceHandle, const std::type_info& featureType) = 0;
		/// @brief Gets the device feature.
		/// @param deviceHandle Device handle.
		/// @param featureType Feature type.
		/// @return Feature; nullptr if it's not supported.
		[[nodiscard("Pure function")]]
		virtual const void* Feature(DeviceHandle deviceHandle, const std::type_info& featureType) const = 0;
		/// @brief Gets the device feature.
		/// @tparam T Feature type.
		/// @param deviceHandle Device handle.
		/// @return Feature; nullptr if it's not supported.
		template<typename T> [[nodiscard("Pure function")]]
		T* Feature(DeviceHandle deviceHandle);
		/// @brief Gets the device feature.
		/// @tparam T Feature type.
		/// @param deviceHandle Device handle.
		/// @return Feature; nullptr if it's not supported.
		template<typename T> [[nodiscard("Pure function")]]
		const T* Feature(DeviceHandle deviceHandle) const;
		/// @brief Checks if the device is connected.
		/// @param deviceHandle Device handle.
		/// @return @a True if it's connected; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool IsConnected(DeviceHandle deviceHandle) const = 0;

		/// @brief Calculates a hash for the @p actionId.
		/// @param actionId Action ID.
		/// @return Action ID hash.
		[[nodiscard("Wierd call")]]
		virtual ActionId HashActionId(std::string_view actionId) = 0;
		/// @brief Gets the action ID from its hash.
		/// @param actionId Action ID hash.
		/// @return Original action ID; empty string if it's not found.
		[[nodiscard("Pure function")]]
		virtual std::string_view UnhashActionId(ActionId actionId) const noexcept = 0;

		/// @brief Adds the device observer.
		/// @param observer Device observer.
		virtual void AddObserver(IDeviceObserver& observer) = 0;
		/// @brief Removes the device observer.
		/// @param observer Device observer.
		virtual void RemoveObserver(IDeviceObserver& observer) noexcept = 0;
		/// @brief Adds the global input observer.
		/// @param observer Input observer.
		virtual void AddObserver(IInputObserver& observer) = 0;
		/// @brief Removes the global input observer.
		/// @param observer Input observer.
		virtual void RemoveObserver(IInputObserver& observer) noexcept = 0;
		/// @brief Adds the input observer.
		/// @param deviceHandle Device handle.
		/// @param observer Input observer.
		virtual void AddObserver(DeviceHandle deviceHandle, IInputObserver& observer) = 0;
		/// @brief Removes the input observer.
		/// @param deviceHandle Device handle.
		/// @param observer Input observer.
		virtual void RemoveObserver(DeviceHandle deviceHandle, IInputObserver& observer) noexcept = 0;
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

namespace PonyEngine::Input
{
	float IInputService::Value(const ActionId actionId) const noexcept
	{
		float value;
		Value(actionId, std::span(&value, 1uz));
		return value;
	}

	float IInputService::Value(const std::span<const DeviceHandle> deviceHandles, const ActionId actionId) const noexcept
	{
		float value;
		Value(deviceHandles, actionId, std::span(&value, 1uz));
		return value;
	}

	template<std::size_t Size>
	Math::Vector<float, Size> IInputService::ValueVector(const ActionId actionId) const noexcept
	{
		Math::Vector<float, Size> vector;
		Value(actionId, vector.Span());
		return vector;
	}

	template<std::size_t Size>
	Math::Vector<float, Size> IInputService::ValueVector(const std::span<const DeviceHandle> deviceHandles, const ActionId actionId) const noexcept
	{
		Math::Vector<float, Size> vector;
		Value(deviceHandles, actionId, vector.Span());
		return vector;
	}

	template<Layout T>
	float IInputService::Value(const T axisId) const noexcept
	{
		return Value(typeid(T), static_cast<AxisIdType>(axisId));
	}

	template<Layout T>
	float IInputService::Value(const std::span<const DeviceHandle> deviceHandles, const T axisId) const noexcept
	{
		return Value(deviceHandles, typeid(T), static_cast<AxisIdType>(axisId));
	}

	bool IInputService::HasLayout(const DeviceHandle deviceHandle, const std::type_info& layoutType) const
	{
		for (const std::reference_wrapper<const std::type_info> layout : Layouts(deviceHandle))
		{
			if (layout.get() == layoutType)
			{
				return true;
			}
		}

		return false;
	}

	template<Layout T>
	bool IInputService::HasLayout(const DeviceHandle deviceHandle) const
	{
		return HasLayout(deviceHandle, typeid(T));
	}

	bool IInputService::HasFeature(const DeviceHandle deviceHandle, const std::type_info& featureType) const
	{
		for (const std::reference_wrapper<const std::type_info> feature : Features(deviceHandle))
		{
			if (feature.get() == featureType)
			{
				return true;
			}
		}

		return false;
	}

	template<typename T>
	bool IInputService::HasFeature(const DeviceHandle deviceHandle) const
	{
		return HasFeature(deviceHandle, typeid(T));
	}

	template<typename T>
	T* IInputService::Feature(const DeviceHandle deviceHandle)
	{
		return static_cast<T*>(Feature(deviceHandle, typeid(T)));
	}

	template<typename T>
	const T* IInputService::Feature(const DeviceHandle deviceHandle) const
	{
		return static_cast<const T*>(Feature(deviceHandle, typeid(T)));
	}
}
