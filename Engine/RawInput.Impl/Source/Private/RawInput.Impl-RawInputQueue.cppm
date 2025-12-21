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
import PonyEngine.Type;

export namespace PonyEngine::Input
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
		DeviceHandle Device(std::size_t index) const noexcept;
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
		void AddInput(DeviceHandle device, const RawInputEvent& event);
		/// @brief Adds the connection event.
		/// @param device Device.
		/// @param event Connection event.
		void AddConnection(DeviceHandle device, const ConnectionEvent& event);
		/// @brief Removes all the event for the device.
		/// @param device Device.
		void Remove(DeviceHandle device) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		RawInputQueue& operator =(const RawInputQueue& other) = delete;
		RawInputQueue& operator =(RawInputQueue&& other) noexcept = default;

	private:
		/// @brief Input data.
		struct InputData final
		{
			std::size_t valueIndex = 0uz; ///< Index in the axes and values.
			std::size_t valueCount = 0uz; ///< Value count.
			InputEventType eventType = InputEventType::State; ///< Event type.
			std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position in screen coordinates; std::nullopt if not applicable.
		};
		/// @brief Connection data.
		struct ConnectionData final
		{
			bool isConnected = false;
		};

		std::vector<DeviceHandle> devices; ///< Input device handles.
		std::vector<std::variant<InputData, ConnectionData>> events; ///< Input events.
		std::vector<std::chrono::time_point<std::chrono::steady_clock>> eventTimes; ///< Input event times.

		std::vector<AxisId> axes; ///< Input axes.
		std::vector<float> values; ///< Input values.

		std::vector<std::size_t> eventIndices; ///< Sorted event indices.
	};
}

namespace PonyEngine::Input
{
	std::size_t RawInputQueue::EventCount() const noexcept
	{
		return eventIndices.size();
	}

	DeviceHandle RawInputQueue::Device(const std::size_t index) const noexcept
	{
		return devices[eventIndices[index]];
	}

	std::variant<RawInputEvent, ConnectionEvent> RawInputQueue::Event(const std::size_t index) const noexcept
	{
		const std::variant<InputData, ConnectionData>& event = events[index];
		const std::chrono::time_point<std::chrono::steady_clock> time = eventTimes[index];

		return std::visit<std::variant<RawInputEvent, ConnectionEvent>>(Type::Overload
		{
			[&](const InputData& inputData) noexcept
			{
				return RawInputEvent
				{
					.axes = std::span<const AxisId>(&axes[inputData.valueIndex], inputData.valueCount),
					.values = std::span<const float>(&values[inputData.valueIndex], inputData.valueCount),
					.eventType = inputData.eventType,
					.timePoint = time,
					.cursorPosition = inputData.cursorPosition
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
				return lhsTime < rhsTime;
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

	void RawInputQueue::AddInput(const DeviceHandle device, const RawInputEvent& event)
	{
		assert(event.axes.size() == event.values.size() && "Incorrect event axes/values.");

		const std::size_t axisIndex = axes.size();

		axes.append_range(event.axes);
		try
		{
			values.append_range(event.values);
		}
		catch (...)
		{
			axes.erase(axes.cbegin() + axisIndex, axes.cend());
			throw;
		}

		devices.push_back(device);
		try
		{
			events.push_back(InputData
			{
				.valueIndex = axisIndex,
				.valueCount = event.axes.size(),
				.eventType = event.eventType,
				.cursorPosition = event.cursorPosition
			});
			try
			{
				eventTimes.push_back(event.timePoint);
			}
			catch (...)
			{
				events.pop_back();
				throw;
			}
		}
		catch (...)
		{
			devices.pop_back();
			throw;
		}
	}

	void RawInputQueue::AddConnection(const DeviceHandle device, const ConnectionEvent& event)
	{
		devices.push_back(device);
		try
		{
			events.push_back(ConnectionData{.isConnected = event.isConnected});
			try
			{
				eventTimes.push_back(event.timePoint);
			}
			catch (...)
			{
				events.pop_back();
				throw;
			}
		}
		catch (...)
		{
			devices.pop_back();
			throw;
		}
	}

	void RawInputQueue::Remove(const DeviceHandle device) noexcept
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
		axes.clear();
		values.clear();
		eventIndices.clear();
	}
}
