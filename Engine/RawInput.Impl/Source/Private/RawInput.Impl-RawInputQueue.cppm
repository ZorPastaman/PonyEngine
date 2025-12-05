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

import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
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

		[[nodiscard("Pure function")]]
		std::size_t EventSize() const noexcept;

		[[nodiscard("Pure function")]]
		DeviceHandle Device(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::variant<RawInputEvent, ConnectionEvent> Event(std::size_t index) const noexcept;

		void SortEvents();

		void AddInput(DeviceHandle device, const RawInputEvent& event);
		void AddConnection(DeviceHandle device, const ConnectionEvent& event);
		void Remove(DeviceHandle device) noexcept;
		void Clear() noexcept;

		RawInputQueue& operator =(const RawInputQueue& other) = default;
		RawInputQueue& operator =(RawInputQueue&& other) noexcept = default;

	private:
		struct InputData final
		{
			std::size_t valueIndex; ///< Index in the axes and values.
			std::size_t valueCount; ///< Value count.
			InputEventType eventType = InputEventType::State; ///< Event type.
			std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position in screen coordinates; std::nullopt if not applicable.
		};
		struct ConnectionData final
		{
			bool isConnected;
		};

		std::vector<DeviceHandle> devices;
		std::vector<std::variant<InputData, ConnectionData>> events;
		std::vector<std::chrono::time_point<std::chrono::steady_clock>> eventTimes;

		std::vector<AxisId> axes;
		std::vector<float> values;

		std::vector<std::size_t> eventIndices;
	};
}

namespace PonyEngine::Input
{
	std::size_t RawInputQueue::EventSize() const noexcept
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

		if (event.index() == 0uz) [[likely]]
		{
			const InputData& inputData = std::get<0>(event);
			return RawInputEvent
			{
				.axes = std::span<const AxisId>(&axes[inputData.valueIndex], inputData.valueCount),
				.values = std::span<const float>(&values[inputData.valueIndex], inputData.valueCount),
				.eventType = inputData.eventType,
				.timePoint = time,
				.cursorPosition = inputData.cursorPosition
			};
		}
		else [[unlikely]]
		{
			const ConnectionData& connectionData = std::get<1>(events[index]);
			return ConnectionEvent
			{
				.isConnected = connectionData.isConnected,
				.timePoint = time
			};
		}
	}

	void RawInputQueue::SortEvents()
	{
		eventIndices.resize(eventTimes.size());
		std::ranges::iota(eventIndices, 0uz);
		std::ranges::sort(eventIndices, [&](const std::size_t lhs, const std::size_t rhs) { return eventTimes[lhs] < eventTimes[rhs]; });
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
		axes.clear();
		values.clear();
		eventIndices.clear();
	}
}
