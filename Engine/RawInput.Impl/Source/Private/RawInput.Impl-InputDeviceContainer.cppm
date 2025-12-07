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

import PonyEngine.RawInput;

export namespace PonyEngine::Input
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
		std::size_t IndexOf(DeviceHandle handle) const noexcept;
		/// @brief Finds an index of the @p device.
		/// @param device Device.
		/// @return Device index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const IDevice& device) const noexcept;

		/// @brief Gets a device handle at the @p index.
		/// @param index Index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		DeviceHandle Handle(std::size_t index) const noexcept;
		/// @brief Gets a device at the @p index.
		/// @param index Index.
		/// @return Device.
		[[nodiscard("Pure function")]]
		IDevice& Device(std::size_t index) const noexcept;
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
		float Value(AxisId axis) const noexcept;
		/// @brief Gets the axis value of the given device.
		/// @param axis Axis.
		/// @param device Device.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		float Value(AxisId axis, DeviceHandle device) const noexcept;
		/// @brief Sets the device axis value.
		/// @param deviceIndex Device index.
		/// @param axis Axis.
		/// @param value Axis value.
		/// @param type Event type.
		void Value(std::size_t deviceIndex, AxisId axis, float value, InputEventType type);

		/// @brief Clears deltas.
		void ClearDeltas() noexcept;

		/// @brief Adds a new device.
		/// @param handle Device handle.
		/// @param device Device.
		/// @param connected Is the device connected?
		void Add(DeviceHandle handle, const std::shared_ptr<IDevice>& device, bool connected);
		/// @brief Removes a device.
		/// @param index Device index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		InputDeviceContainer& operator =(const InputDeviceContainer& other) = delete;
		InputDeviceContainer& operator =(InputDeviceContainer&& other) noexcept = default;

	private:
		/// @brief Finds an index of the device axis.
		/// @param handle Device handle.
		/// @param axis Axis.
		/// @return Axis index or axes size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(DeviceHandle handle, AxisId axis) const noexcept;
		/// @brief Finds an index of the axis among the axis indices.
		/// @param axisIndices Axis indices.
		/// @param axis Axis.
		/// @return Axis index or axes size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(std::span<const std::size_t> axisIndices, AxisId axis) const noexcept;

		/// @brief Gets an axis value.
		/// @param axisIndex Axis index.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		float Value(std::size_t axisIndex) const noexcept;

		/// @brief Adds a new axis.
		/// @param deviceIndex Device index.
		/// @param axis Axis.
		/// @return Axis index.
		std::size_t AddAxis(std::size_t deviceIndex, AxisId axis);

		std::vector<DeviceHandle> handles; ///< Device handles.
		std::vector<std::shared_ptr<IDevice>> devices; ///< Devices.
		std::vector<bool> connections; ///< Device connection statuses
		std::vector<std::vector<std::size_t>> axisIndices; ///< Device axes indices. These indices point to the @p axes, @p states and @p deltas.

		// These 3 vectors are synced by index.
		std::vector<AxisId> axes; ///< Axes.
		std::vector<float> states; ///< State values.
		std::vector<float> deltas; ///< Delta values.
	};
}

namespace PonyEngine::Input
{
	std::size_t InputDeviceContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t InputDeviceContainer::IndexOf(const DeviceHandle handle) const noexcept
	{
		return std::ranges::find(handles, handle) - handles.cbegin();
	}

	std::size_t InputDeviceContainer::IndexOf(const IDevice& device) const noexcept
	{
		return std::ranges::find_if(devices, [&](const std::shared_ptr<IDevice>& d) { return d.get() == &device; }) - devices.cbegin();
	}

	DeviceHandle InputDeviceContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	IDevice& InputDeviceContainer::Device(const std::size_t index) const noexcept
	{
		return *devices[index];
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

	float InputDeviceContainer::Value(const AxisId axis) const noexcept
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

	float InputDeviceContainer::Value(const AxisId axis, const DeviceHandle device) const noexcept
	{
		const std::size_t axisIndex = IndexOf(device, axis);
		return axisIndex < axes.size() ? Value(axisIndex) : 0.f;
	}

	void InputDeviceContainer::Value(const std::size_t deviceIndex, const AxisId axis, const float value, const InputEventType type)
	{
		assert(deviceIndex < devices.size() && "Incorrect device.");

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

	void InputDeviceContainer::Add(const DeviceHandle handle, const std::shared_ptr<IDevice>& device, const bool connected)
	{
		assert(device && "The device is nullptr");

		handles.push_back(handle);
		try
		{
			devices.push_back(device);
			try
			{
				connections.push_back(connected);
				try
				{
					axisIndices.push_back(std::vector<std::size_t>());
				}
				catch (...)
				{
					connections.pop_back();
					throw;
				}
			}
			catch (...)
			{
				devices.pop_back();
				throw;
			}
		}
		catch (...)
		{
			handles.pop_back();
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
		devices.erase(devices.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void InputDeviceContainer::Clear() noexcept
	{
		handles.clear();
		devices.clear();
		connections.clear();
		axisIndices.clear();

		axes.clear();
		states.clear();
		deltas.clear();
	}

	std::size_t InputDeviceContainer::IndexOf(const DeviceHandle handle, const AxisId axis) const noexcept
	{
		const std::size_t deviceIndex = IndexOf(handle);
		if (deviceIndex >= devices.size()) [[unlikely]]
		{
			return axes.size();
		}

		return IndexOf(axisIndices[deviceIndex], axis);
	}

	std::size_t InputDeviceContainer::IndexOf(const std::span<const std::size_t> axisIndices, const AxisId axis) const noexcept
	{
		const std::size_t axisIndex = std::ranges::find_if(axisIndices, [&](const std::size_t index) { return axes[index] == axis; }) - axisIndices.cbegin();
		return axisIndex < axisIndices.size() ? axisIndices[axisIndex] : axes.size();
	}

	float InputDeviceContainer::Value(const std::size_t axisIndex) const noexcept
	{
		return states[axisIndex] + deltas[axisIndex];
	}

	std::size_t InputDeviceContainer::AddAxis(const std::size_t deviceIndex, const AxisId axis)
	{
		const std::size_t axisIndex = axes.size();

		std::vector<std::size_t>& deviceAxes = axisIndices[deviceIndex];
		deviceAxes.push_back(axisIndex);
		try
		{
			axes.push_back(axis);
			try
			{
				states.push_back(0.f);
				try
				{
					deltas.push_back(0.f);
				}
				catch (...)
				{
					states.pop_back();
					throw;
				}
			}
			catch (...)
			{
				axes.pop_back();
				throw;
			}
		}
		catch (...)
		{
			deviceAxes.pop_back();
			throw;
		}

		return axisIndex;
	}
}
