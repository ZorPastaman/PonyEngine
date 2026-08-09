/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.RawInput.Impl:InputDeviceContainer;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::RawInput
{
	/// @brief Input device container.
	class InputDeviceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputDeviceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		InputDeviceContainer(const InputDeviceContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		InputDeviceContainer(InputDeviceContainer&& other) noexcept = default;

		~InputDeviceContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the @p handle.
		/// @param handle Device handle.
		/// @return Handle index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(DeviceHandleID handle) const noexcept;

		/// @brief Gets a device handle at the @p index.
		/// @param index Index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		DeviceHandleID Handle(std::size_t index) const noexcept;
		/// @brief Gets a device controller at the @p index.
		/// @param index Index.
		/// @return Device controller.
		[[nodiscard("Pure function")]]
		IDeviceController& Controller(std::size_t index) const noexcept;
		/// @brief Gets a device name.
		/// @param index Device index.
		/// @return Device name.
		[[nodiscard("Pure function")]]
		std::string_view DeviceName(std::size_t index) const noexcept;
		/// @brief Gets a device type.
		/// @param index Device index.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		struct DeviceType DeviceType(std::size_t index) const noexcept;
		/// @brief Gets a device style.
		/// @param index Device index.
		/// @return Device style.
		[[nodiscard("Pure function")]]
		struct DeviceStyle DeviceStyle(std::size_t index) const noexcept;
		/// @brief Tries to find a feature.
		/// @param index Device index.
		/// @param type Feature type.
		/// @return Feature or nullptr if not found.
		[[nodiscard("Pure function")]]
		void* FindFeature(std::size_t index, std::type_index type) const noexcept;
		/// @brief Check if a device at the @p index is connected.
		/// @param index Device index.
		/// @return @a True if it's connected; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsConnected(std::size_t index) const noexcept;
		/// @brief Sets a device connection status.
		/// @param index Device index.
		/// @param value Connection status.
		void IsConnected(std::size_t index, bool value) noexcept;

		/// @brief Gets the global axis value.
		/// @param axis Axis.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		float Value(Axis axis) const noexcept;
		/// @brief Gets the axis value of the given device.
		/// @param axis Axis.
		/// @param deviceIndex Device index.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		float Value(Axis axis, std::size_t deviceIndex) const noexcept;
		/// @brief Sets the device axis value.
		/// @param deviceIndex Device index.
		/// @param axis Axis.
		/// @param value Axis value.
		/// @param type Event type.
		void Value(std::size_t deviceIndex, Axis axis, float value, InputEventType type);

		/// @brief Clears deltas.
		void ClearDeltas() noexcept;

		/// @brief Adds a new device.
		/// @param controller Device controller.
		/// @param handle Device handle.
		/// @param isConnected Is the device connected?
		/// @param params Device parameters.
		void Add(DeviceHandleID handle, IDeviceController& controller, bool isConnected, const DeviceParams& params);
		/// @brief Removes a device.
		/// @param index Device index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		InputDeviceContainer& operator =(const InputDeviceContainer& other) = delete;
		InputDeviceContainer& operator =(InputDeviceContainer&& other) noexcept = default;

	private:
		/// @brief Finds an index of the axis among the axis indices.
		/// @param axisIndices Axis indices.
		/// @param axis Axis.
		/// @return Axis index or axes size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::span<const std::size_t> axisIndices, Axis axis) const noexcept;

		/// @brief Gets an axis value.
		/// @param axisIndex Axis index.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		float Value(std::size_t axisIndex) const noexcept;

		/// @brief Adds a new axis.
		/// @param deviceIndex Device index.
		/// @param axis Axis.
		/// @return Axis index.
		std::size_t AddAxis(std::size_t deviceIndex, Axis axis);

		std::vector<DeviceHandleID> handles; ///< Device handles.
		std::vector<IDeviceController*> controllers; ///< Device controller.
		std::vector<std::string> deviceNames; ///< Device names.
		std::vector<struct DeviceType> deviceTypes; ///< Device types.
		std::vector<struct DeviceStyle> deviceStyles; ///< Device styles.
		std::vector<std::vector<FeatureEntry>> features; ///< Device features.
		std::vector<bool> connections; ///< Device connection statuses
		std::vector<std::vector<std::size_t>> axisIndices; ///< Device axes indices. These indices point to the @p axes, @p states and @p deltas.

		// These 3 vectors are synced by index.
		std::vector<Axis> axes; ///< Axes.
		std::vector<float> states; ///< State values.
		std::vector<float> deltas; ///< Delta values.
	};
}

namespace PonyEngine::RawInput
{
	std::size_t InputDeviceContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t InputDeviceContainer::IndexOf(const DeviceHandleID handle) const noexcept
	{
		auto position = std::ranges::lower_bound(handles, handle);
		if (position != handles.cend() && *position != handle)
		{
			position = handles.cend();
		}

		return position - handles.cbegin();
	}

	IDeviceController& InputDeviceContainer::Controller(const std::size_t index) const noexcept
	{
		return *controllers[index];
	}

	DeviceHandleID InputDeviceContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	std::string_view InputDeviceContainer::DeviceName(const std::size_t index) const noexcept
	{
		return deviceNames[index];
	}

	struct DeviceType InputDeviceContainer::DeviceType(const std::size_t index) const noexcept
	{
		return deviceTypes[index];
	}

	struct DeviceStyle InputDeviceContainer::DeviceStyle(const std::size_t index) const noexcept
	{
		return deviceStyles[index];
	}

	void* InputDeviceContainer::FindFeature(const std::size_t index, const std::type_index type) const noexcept
	{
		const std::span<const FeatureEntry> featureEntries = features[index];
		if (const auto position = std::ranges::find(featureEntries, type, &FeatureEntry::featureType); position != featureEntries.cend())
		{
			return position->feature;
		}

		return nullptr;
	}

	bool InputDeviceContainer::IsConnected(const std::size_t index) const noexcept
	{
		return connections[index];
	}

	void InputDeviceContainer::IsConnected(const std::size_t index, const bool value) noexcept
	{
		assert(index < connections.size() && "The device index is incorrect.");

		connections[index] = value;
	}

	float InputDeviceContainer::Value(const Axis axis) const noexcept
	{
		float value = 0.f;
		for (std::size_t i = 0uz; i < axes.size(); ++i)
		{
			if (axes[i] == axis)
			{
				value += Value(i);
			}
		}

		return value;
	}

	float InputDeviceContainer::Value(const Axis axis, const std::size_t deviceIndex) const noexcept
	{
		const std::size_t axisIndex = IndexOf(axisIndices[deviceIndex], axis);
		return axisIndex < axes.size() ? Value(axisIndex) : 0.f;
	}

	void InputDeviceContainer::Value(const std::size_t deviceIndex, const Axis axis, const float value, const InputEventType type)
	{
		assert(deviceIndex < Size() && "Incorrect device.");

		std::size_t axisIndex = IndexOf(axisIndices[deviceIndex], axis);
		if (axisIndex >= axes.size()) [[unlikely]]
		{
			axisIndex = AddAxis(deviceIndex, axis);
		}

		switch (type)
		{
		case InputEventType::State:
			states[axisIndex] = value;
			break;
		case InputEventType::Delta:
			deltas[axisIndex] += value;
			break;
		default: [[unlikely]]
			assert(false && "Incorrect input event type.");
			break;
		}
	}

	void InputDeviceContainer::ClearDeltas() noexcept
	{
		std::ranges::fill(deltas, 0.f);
	}

	void InputDeviceContainer::Add(const DeviceHandleID handle, IDeviceController& controller, const bool isConnected, const DeviceParams& params)
	{
		const std::size_t initialSize = Size();
		const std::size_t index = std::ranges::lower_bound(handles, handle) - handles.cbegin();

		try
		{
			handles.insert(handles.cbegin() + index, handle);
			controllers.insert(controllers.cbegin() + index, &controller);
			deviceNames.insert(deviceNames.cbegin() + index, std::string(params.name));
			deviceTypes.insert(deviceTypes.cbegin() + index, params.type);
			deviceStyles.insert(deviceStyles.cbegin() + index, params.style);
			features.insert(features.cbegin() + index, std::vector(params.features.cbegin(), params.features.cend()));
			connections.insert(connections.cbegin() + index, isConnected);
			axisIndices.insert(axisIndices.cbegin() + index, std::vector<std::size_t>());
		}
		catch (...)
		{
			if (axisIndices.size() != initialSize)
			{
				axisIndices.erase(axisIndices.cbegin() + index);
			}
			if (connections.size() != initialSize)
			{
				connections.erase(connections.cbegin() + index);
			}
			if (features.size() != initialSize)
			{
				features.erase(features.cbegin() + index);
			}
			if (deviceStyles.size() != initialSize)
			{
				deviceStyles.erase(deviceStyles.cbegin() + index);
			}
			if (deviceTypes.size() != initialSize)
			{
				deviceTypes.erase(deviceTypes.cbegin() + index);
			}
			if (deviceNames.size() != initialSize)
			{
				deviceNames.erase(deviceNames.cbegin() + index);
			}
			if (controllers.size() != initialSize)
			{
				controllers.erase(controllers.cbegin() + index);
			}
			if (handles.size() != initialSize)
			{
				handles.erase(handles.cbegin() + index);
			}

			throw;
		}
	}

	void InputDeviceContainer::Remove(const std::size_t index) noexcept
	{
		for (std::size_t i = 0uz; i < axisIndices.size(); ++i)
		{
			if (i == index) [[unlikely]]
			{
				continue;
			}

			for (std::size_t& axisIndex : axisIndices[i])
			{
				std::size_t shift = 0uz;
				for (const std::size_t removedAxisIndex : axisIndices[index])
				{
					shift += removedAxisIndex < axisIndex;
				}
				axisIndex -= shift;
			}
		}

		const std::span<const std::size_t> indices = axisIndices[index];
		for (std::size_t i = indices.size(); i-- > 0uz; )
		{
			const std::size_t axisIndex = indices[i];
			deltas.erase(deltas.cbegin() + axisIndex);
			states.erase(states.cbegin() + axisIndex);
			axes.erase(axes.cbegin() + axisIndex);
		}

		axisIndices.erase(axisIndices.cbegin() + index);
		connections.erase(connections.cbegin() + index);
		features.erase(features.cbegin() + index);
		deviceStyles.erase(deviceStyles.cbegin() + index);
		deviceTypes.erase(deviceTypes.cbegin() + index);
		deviceNames.erase(deviceNames.cbegin() + index);
		controllers.erase(controllers.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void InputDeviceContainer::Clear() noexcept
	{
		handles.clear();
		controllers.clear();
		deviceNames.clear();
		deviceTypes.clear();
		deviceStyles.clear();
		features.clear();
		connections.clear();
		axisIndices.clear();

		axes.clear();
		states.clear();
		deltas.clear();
	}

	std::size_t InputDeviceContainer::IndexOf(const std::span<const std::size_t> axisIndices, const Axis axis) const noexcept
	{
		const std::size_t axisIndex = std::ranges::find_if(axisIndices, [&](const std::size_t index) { return axes[index] == axis; }) - axisIndices.cbegin();
		return axisIndex < axisIndices.size() ? axisIndices[axisIndex] : axes.size();
	}

	float InputDeviceContainer::Value(const std::size_t axisIndex) const noexcept
	{
		return states[axisIndex] + deltas[axisIndex];
	}

	std::size_t InputDeviceContainer::AddAxis(const std::size_t deviceIndex, const Axis axis)
	{
		const std::size_t axisIndex = axes.size();
		std::vector<std::size_t>& deviceAxes = axisIndices[deviceIndex];

		const std::size_t initialAxisCount = deviceAxes.size();
		try
		{
			deviceAxes.push_back(axisIndex);
			axes.push_back(axis);
			states.push_back(0.f);
			deltas.push_back(0.f);
		}
		catch (...)
		{
			deltas.resize(initialAxisCount);
			states.resize(initialAxisCount);
			axes.resize(initialAxisCount);
			deviceAxes.resize(initialAxisCount);
			throw;
		}

		return axisIndex;
	}
}
