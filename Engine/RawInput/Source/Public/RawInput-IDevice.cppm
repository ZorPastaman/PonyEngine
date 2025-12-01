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

export module PonyEngine.RawInput:IDevice;

import std;

import :DeviceTypeId;

export namespace PonyEngine::Input
{
	/// @brief Device.
	class IDevice
	{
		INTERFACE_BODY(IDevice)

		/// @brief Gets the device name.
		/// @return Device name.
		/// @remark It must be a unique name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;

		/// @brief Gets the device type.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		virtual DeviceTypeId DeviceType() const noexcept = 0;

		/// @brief Gets the feature types.
		/// @return Feature types.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::type_index> FeatureTypes() const noexcept = 0;
		/// @brief Tries to find a feature.
		/// @param type Feature type.
		/// @return Feature or nullptr if not found.
		[[nodiscard("Pure function")]]
		virtual void* FindFeature(std::type_index type) noexcept = 0;
		/// @brief Tries to find a feature.
		/// @param type Feature type.
		/// @return Feature or nullptr if not found.
		[[nodiscard("Pure function")]]
		virtual const void* FindFeature(std::type_index type) const noexcept = 0;
		/// @brief Tries to find a feature.
		/// @tparam T Feature type.
		/// @return Feature or nullptr if not found.
		template<typename T> [[nodiscard("Pure function")]]
		T* FindFeature() noexcept;
		/// @brief Tries to find a feature.
		/// @tparam T Feature type.
		/// @return Feature or nullptr if not found.
		template<typename T> [[nodiscard("Pure function")]]
		const T* FindFeature() const noexcept;
		/// @brief Gets a feature.
		/// @tparam T Feature type.
		/// @return Feature.
		template<typename T> [[nodiscard("Pure function")]]
		T& GetFeature();
		/// @brief Gets a feature.
		/// @tparam T Feature type.
		/// @return Feature.
		template<typename T> [[nodiscard("Pure function")]]
		const T& GetFeature() const;
	};
}

namespace PonyEngine::Input
{
	template<typename T>
	T* IDevice::FindFeature() noexcept
	{
		return static_cast<T*>(FindFeature(typeid(T)));
	}

	template<typename T>
	const T* IDevice::FindFeature() const noexcept
	{
		return static_cast<const T*>(FindFeature(typeid(T)));
	}

	template<typename T>
	T& IDevice::GetFeature()
	{
		T* const feature = FindFeature<T>();
		if (!feature) [[unlikely]]
		{
			throw std::logic_error("Feature not found");
		}

		return *feature;
	}

	template<typename T>
	const T& IDevice::GetFeature() const
	{
		const T* const feature = FindFeature<T>();
		if (!feature) [[unlikely]]
		{
			throw std::logic_error("Feature not found");
		}

		return *feature;
	}
}
