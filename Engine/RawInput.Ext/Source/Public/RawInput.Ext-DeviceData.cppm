/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Ext:DeviceData;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
	/// @brief Device data.
	struct DeviceData final
	{
		std::string name; ///< Device name.
		DeviceTypeId type; ///< Device type.
		std::unordered_map<std::type_index, void*> features; ///< Device features.
		bool isConnected = true; ///< Is the device connected?

		/// @brief Sets basic device data.
		/// @param name Device name.
		/// @param type Device type.
		/// @param isConnected Is the device connected?
		void SetDevice(std::string_view name, DeviceTypeId type, bool isConnected);
		/// @brief Adds a feature.
		/// @tparam T Feature type.
		/// @param feature Feature.
		template<typename T>
		void AddFeature(T& feature);
	};
}

namespace PonyEngine::Input
{
	void DeviceData::SetDevice(const std::string_view name, const DeviceTypeId type, const bool isConnected)
	{
		this->name = name;
		this->type = type;
		this->isConnected = isConnected;
	}

	template<typename T>
	void DeviceData::AddFeature(T& feature)
	{
		features[typeid(T)] = &feature;
	}
}
