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

export module PonyEngine.RawInput.Impl:RawInputQueue;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput;
import PonyEngine.Utility;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input queue.
	class RawInputQueue final
	{
	public:
		[[nodiscard("Pure constructor")]]
		RawInputQueue() noexcept = default;
		[[nodiscard("Pure constructor")]]
		RawInputQueue(const RawInputQueue& other) = default;
		[[nodiscard("Pure constructor")]]
		RawInputQueue(RawInputQueue&& other) noexcept = default;

		~RawInputQueue() noexcept = default;

		/// @brief Gets the event count.
		/// @return Event count.
		/// @remark It works correct only after calling @p SortEvents().
		[[nodiscard("Pure function")]]
		std::size_t EventCount() const noexcept;

		/// @brief Gets a device handle.
		/// @param index Input event index.
		/// @return Device handle.
		/// @remark It works correct only after calling @p SortEvents().
		[[nodiscard("Pure function")]]
		DeviceHandleID Device(std::size_t index) const noexcept;
		/// @brief Gets an input event.
		/// @param index Input event index.
		/// @return Input event.
		/// @remark It works correct only after calling @p SortEvents().
		[[nodiscard("Pure function")]]
		std::variant<RawInputEvent, ConnectionEvent> Event(std::size_t index) const noexcept;

		/// @brief Sorts input events.
		void SortEvents();

		/// @brief Adds the input event.
		/// @param device Device.
		/// @param event Input event.
		void AddInput(DeviceHandleID device, const RawInputEvent& event);
		/// @brief Adds the connection event.
		/// @param device Device.
		/// @param event Connection event.
		void AddConnection(DeviceHandleID device, const ConnectionEvent& event);
		/// @brief Removes all the event for the device.
		/// @param device Device.
		void Remove(DeviceHandleID device) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		RawInputQueue& operator =(const RawInputQueue& other) = delete;
		RawInputQueue& operator =(RawInputQueue&& other) noexcept = default;

	private:
		/// @brief Input data.
		struct InputData final
		{
			std::size_t valueOffset = 0uz; ///< Input value offset.
			std::size_t valueCount = 0uz; ///< Input value count.
		};
		/// @brief Connection data.
		struct ConnectionData final
		{
			bool isConnected = false;
		};

		std::vector<DeviceHandleID> devices; ///< Input device handles.
		std::vector<std::variant<InputData, ConnectionData>> events; ///< Input events.
		std::vector<std::chrono::time_point<std::chrono::steady_clock>> eventTimes; ///< Input event times.

		std::vector<Axis> inputAxes; ///< Input axes.
		std::vector<float> inputValues; ///< Input values.
		std::vector<InputType> inputTypes; ///< Input types.

		std::vector<std::size_t> eventIndices; ///< Sorted event indices.
	};
}

namespace PonyEngine::RawInput
{
	std::size_t RawInputQueue::EventCount() const noexcept
	{
		return eventIndices.size();
	}

	DeviceHandleID RawInputQueue::Device(const std::size_t index) const noexcept
	{
		return devices[eventIndices[index]];
	}

	std::variant<RawInputEvent, ConnectionEvent> RawInputQueue::Event(const std::size_t index) const noexcept
	{
		const std::size_t eventIndex = eventIndices[index];
		const std::variant<InputData, ConnectionData>& event = events[eventIndex];
		const std::chrono::time_point<std::chrono::steady_clock> time = eventTimes[eventIndex];

		return std::visit<std::variant<RawInputEvent, ConnectionEvent>>(Utility::Overload
		{
			[&](const InputData& inputData) noexcept
			{
				return RawInputEvent
				{
					.axes = std::span<const Axis>(&inputAxes[inputData.valueOffset], inputData.valueCount),
					.values = std::span<const float>(&inputValues[inputData.valueOffset], inputData.valueCount),
					.inputTypes = std::span<const InputType>(&inputTypes[inputData.valueOffset], inputData.valueCount),
					.timePoint = time
				};
			},
			[&](const ConnectionData& connectionData) noexcept
			{
				return ConnectionEvent
				{
					.isConnected = connectionData.isConnected,
					.timePoint = time
				};
			}
		}, event);
	}

	void RawInputQueue::SortEvents()
	{
		eventIndices.resize(eventTimes.size());
		std::ranges::iota(eventIndices, 0uz);
		std::ranges::sort(eventIndices, [&](const std::size_t lhs, const std::size_t rhs)
		{
			const std::chrono::time_point<std::chrono::steady_clock> lhsTime = eventTimes[lhs];
			const std::chrono::time_point<std::chrono::steady_clock> rhsTime = eventTimes[rhs];

			if (lhsTime != rhsTime) [[likely]]
			{
				return lhsTime <= rhsTime;
			}

			const bool lhsConnection = std::holds_alternative<ConnectionData>(events[lhs]);
			const bool rhsConnection = std::holds_alternative<ConnectionData>(events[rhs]);

			if (lhsConnection && rhsConnection) [[unlikely]]
			{
				return std::get<ConnectionData>(events[lhs]).isConnected > std::get<ConnectionData>(events[rhs]).isConnected;
			}

			if (lhsConnection && !rhsConnection) [[unlikely]]
			{
				return std::get<ConnectionData>(events[lhs]).isConnected;
			}

			if (!lhsConnection && rhsConnection) [[unlikely]]
			{
				return !std::get<ConnectionData>(events[rhs]).isConnected;
			}

			return true;
		});
	}

	void RawInputQueue::AddInput(const DeviceHandleID device, const RawInputEvent& event)
	{
		assert(event.axes.size() == event.values.size() && event.axes.size() == event.inputTypes.size() && "Input event axes, values and event types sizes are mismatched.");
		for (std::size_t i = 1uz; i < event.axes.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(event.axes[i] != event.axes[j] && "Axis duplicate in one event found.");
			}
		}

		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const std::size_t axisIndex = inputAxes.size();
		inputAxes.append_range(event.axes);
		const auto axesScopeGuard = Utility::ScopeGuard([&]() noexcept { inputAxes.erase(inputAxes.cbegin() + axisIndex, inputAxes.cend()); }, scopeGuardFlag);
		inputValues.append_range(event.values);
		const auto valuesScopeGuard = Utility::ScopeGuard([&]() noexcept { inputValues.erase(inputValues.cbegin() + axisIndex, inputValues.cend()); }, scopeGuardFlag);
		inputTypes.append_range(event.inputTypes);
		const auto eventTypesScopeGuard = Utility::ScopeGuard([&]() noexcept { inputTypes.erase(inputTypes.cbegin() + axisIndex, inputTypes.cend()); }, scopeGuardFlag);
		devices.push_back(device);
		const auto devicesScopeGuard = Utility::ScopeGuard([&]() noexcept { devices.pop_back(); }, scopeGuardFlag);
		events.push_back(InputData
		{
			.valueOffset = axisIndex,
			.valueCount = event.axes.size()
		});
		const auto eventsScopeGuard = Utility::ScopeGuard([&]() noexcept { events.pop_back(); }, scopeGuardFlag);
		eventTimes.push_back(event.timePoint);

		scopeGuardFlag.Release();
	}

	void RawInputQueue::AddConnection(const DeviceHandleID device, const ConnectionEvent& event)
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		devices.push_back(device);
		const auto devicesScopeGuard = Utility::ScopeGuard([&]() noexcept { devices.pop_back(); }, scopeGuardFlag);
		events.push_back(ConnectionData{.isConnected = event.isConnected});
		const auto eventsScopeGuard = Utility::ScopeGuard([&]() noexcept { events.pop_back(); }, scopeGuardFlag);
		eventTimes.push_back(event.timePoint);

		scopeGuardFlag.Release();
	}

	void RawInputQueue::Remove(const DeviceHandleID device) noexcept
	{
		for (std::size_t i = devices.size(); i-- > 0uz; )
		{
			if (devices[i] == device)
			{
				eventTimes.erase(eventTimes.cbegin() + i);
				events.erase(events.cbegin() + i);
				devices.erase(devices.cbegin() + i);
			}
		}
	}

	void RawInputQueue::Clear() noexcept
	{
		devices.clear();
		events.clear();
		eventTimes.clear();
		inputAxes.clear();
		inputValues.clear();
		eventIndices.clear();
	}
}
