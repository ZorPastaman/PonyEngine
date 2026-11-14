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

export module PonyEngine.RawInput.Impl:DeviceContainer;

import std;

import PonyEngine.RawInput.Ext;
import PonyEngine.Utility;

import :DeviceProperties;

export namespace PonyEngine::RawInput
{
	/// @brief Device container.
	class DeviceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		DeviceContainer() noexcept = default;
		[[nodiscard("Pure constructor")]]
		DeviceContainer(const DeviceContainer& other) = default;
		[[nodiscard("Pure constructor")]]
		DeviceContainer(DeviceContainer&& other) noexcept = default;

		~DeviceContainer() noexcept = default;

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
		/// @brief Gets device properties.
		/// @param index Device index.
		/// @return Device properties.
		[[nodiscard("Pure function")]]
		const DeviceProperties& Properties(std::size_t index) const noexcept;
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
		void Value(std::size_t deviceIndex, Axis axis, float value, InputType type);

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

		DeviceContainer& operator =(const DeviceContainer& other) = delete;
		DeviceContainer& operator =(DeviceContainer&& other) noexcept = default;

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
		std::vector<DeviceProperties> properties; ///< Device properties.
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
	std::size_t DeviceContainer::Size() const noexcept
	{
		return handles.size();
	}

	std::size_t DeviceContainer::IndexOf(const DeviceHandleID handle) const noexcept
	{
		auto position = std::ranges::lower_bound(handles, handle);
		if (position != handles.cend() && *position != handle)
		{
			position = handles.cend();
		}

		return position - handles.cbegin();
	}

	DeviceHandleID DeviceContainer::Handle(const std::size_t index) const noexcept
	{
		return handles[index];
	}

	IDeviceController& DeviceContainer::Controller(const std::size_t index) const noexcept
	{
		return *controllers[index];
	}

	const DeviceProperties& DeviceContainer::Properties(const std::size_t index) const noexcept
	{
		return properties[index];
	}

	bool DeviceContainer::IsConnected(const std::size_t index) const noexcept
	{
		return connections[index];
	}

	void DeviceContainer::IsConnected(const std::size_t index, const bool value) noexcept
	{
		assert(index < connections.size() && "The device index is incorrect.");

		connections[index] = value;
	}

	float DeviceContainer::Value(const Axis axis) const noexcept
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

	float DeviceContainer::Value(const Axis axis, const std::size_t deviceIndex) const noexcept
	{
		const std::size_t axisIndex = IndexOf(axisIndices[deviceIndex], axis);
		return axisIndex < axes.size() ? Value(axisIndex) : 0.f;
	}

	void DeviceContainer::Value(const std::size_t deviceIndex, const Axis axis, const float value, const InputType type)
	{
		assert(deviceIndex < Size() && "Incorrect device.");

		std::size_t axisIndex = IndexOf(axisIndices[deviceIndex], axis);
		if (axisIndex >= axes.size()) [[unlikely]]
		{
			axisIndex = AddAxis(deviceIndex, axis);
		}

		switch (type)
		{
		case InputType::State:
			states[axisIndex] = value;
			break;
		case InputType::Delta:
			deltas[axisIndex] += value;
			break;
		default: [[unlikely]]
			assert(false && "Incorrect input event type.");
			break;
		}
	}

	void DeviceContainer::ClearDeltas() noexcept
	{
		std::ranges::fill(deltas, 0.f);
	}

	void DeviceContainer::Add(const DeviceHandleID handle, IDeviceController& controller, const bool isConnected, const DeviceParams& params)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const std::size_t index = std::ranges::lower_bound(handles, handle) - handles.cbegin();
		handles.insert(handles.cbegin() + index, handle);
		const auto handlesScopeGuard = Utility::ScopeGuard([&]() noexcept { handles.erase(handles.cbegin() + index); }, scopeGuardFlag);
		controllers.insert(controllers.cbegin() + index, &controller);
		const auto controllersScopeGuard = Utility::ScopeGuard([&]() noexcept { controllers.erase(controllers.cbegin() + index); }, scopeGuardFlag);
		properties.insert(properties.cbegin() + index, DeviceProperties
		{
			.name = std::string(params.name),
			.friendlyName = std::string(params.friendlyName),
			.interfaceName = std::string(params.interfaceName),
			.type = params.type,
			.style = params.style,
			.features = std::vector(params.features.cbegin(), params.features.cend())
		});
		const auto propertiesScopeGuard = Utility::ScopeGuard([&]() noexcept { properties.erase(properties.cbegin() + index); }, scopeGuardFlag);
		connections.insert(connections.cbegin() + index, isConnected);
		const auto connectionsScopeGuard = Utility::ScopeGuard([&]() noexcept { connections.erase(connections.cbegin() + index); }, scopeGuardFlag);
		axisIndices.insert(axisIndices.cbegin() + index, std::vector<std::size_t>());

		scopeGuardFlag.Release();
	}

	void DeviceContainer::Remove(const std::size_t index) noexcept
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
		properties.erase(properties.cbegin() + index);
		controllers.erase(controllers.cbegin() + index);
		handles.erase(handles.cbegin() + index);
	}

	void DeviceContainer::Clear() noexcept
	{
		handles.clear();
		controllers.clear();
		properties.clear();
		connections.clear();
		axisIndices.clear();

		axes.clear();
		states.clear();
		deltas.clear();
	}

	std::size_t DeviceContainer::IndexOf(const std::span<const std::size_t> axisIndices, const Axis axis) const noexcept
	{
		const std::size_t axisIndex = std::ranges::find_if(axisIndices, [&](const std::size_t index) { return axes[index] == axis; }) - axisIndices.cbegin();
		return axisIndex < axisIndices.size() ? axisIndices[axisIndex] : axes.size();
	}

	float DeviceContainer::Value(const std::size_t axisIndex) const noexcept
	{
		return states[axisIndex] + deltas[axisIndex];
	}

	std::size_t DeviceContainer::AddAxis(const std::size_t deviceIndex, const Axis axis)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const std::size_t axisIndex = axes.size();
		std::vector<std::size_t>& deviceAxes = axisIndices[deviceIndex];
		deviceAxes.push_back(axisIndex);
		const auto deviceAxesScopeGuard = Utility::ScopeGuard([&]() noexcept { deviceAxes.pop_back(); }, scopeGuardFlag);
		axes.push_back(axis);
		const auto axesScopeGuard = Utility::ScopeGuard([&]() noexcept { axes.pop_back(); }, scopeGuardFlag);
		states.push_back(0.f);
		const auto statesScopeGuard = Utility::ScopeGuard([&]() noexcept { states.pop_back(); }, scopeGuardFlag);
		deltas.push_back(0.f);

		scopeGuardFlag.Release();

		return axisIndex;
	}
}
