/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseEventQueue;

import std;

import PonyEngine.RawInput;

import :MouseEvent;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse event queue.
	class MouseEventQueue final
	{
	public:
		[[nodiscard("Pure constructor")]]
		MouseEventQueue() noexcept = default;
		[[nodiscard("Pure constructor")]]
		MouseEventQueue(const MouseEventQueue& other) = default;
		[[nodiscard("Pure constructor")]]
		MouseEventQueue(MouseEventQueue&& other) noexcept = default;

		~MouseEventQueue() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Gets a mouse device.
		/// @param index Event index.
		/// @return Device.
		[[nodiscard("Pure function")]]
		DeviceHandle Device(std::size_t index) const noexcept;
		/// @brief Gets a mouse event.
		/// @param index Event index.
		/// @return Mouse event.
		[[nodiscard("Pure function")]]
		const MouseEvent& Event(std::size_t index) const noexcept;

		/// @brief Adds the event.
		/// @param device Device handle.
		/// @param event Mouse event.
		void Add(DeviceHandle device, const MouseEvent& event);
		/// @brief Removes all the mouse devices.
		/// @param device Device handle.
		void Remove(DeviceHandle device) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		MouseEventQueue& operator =(const MouseEventQueue& other) = delete;
		MouseEventQueue& operator =(MouseEventQueue&& other) noexcept = default;

	private:
		std::vector<DeviceHandle> devices; ///< Mouse device handles.
		std::vector<MouseEvent> events; ///< Mouse events.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	std::size_t MouseEventQueue::Size() const noexcept
	{
		return devices.size();
	}

	DeviceHandle MouseEventQueue::Device(const std::size_t index) const noexcept
	{
		return devices[index];
	}

	const MouseEvent& MouseEventQueue::Event(const std::size_t index) const noexcept
	{
		return events[index];
	}

	void MouseEventQueue::Add(const DeviceHandle device, const MouseEvent& event)
	{
		devices.push_back(device);
		try
		{
			events.push_back(event);
		}
		catch (...)
		{
			devices.pop_back();
			throw;
		}
	}

	void MouseEventQueue::Remove(const DeviceHandle device) noexcept
	{
		for (std::size_t i = devices.size(); i-- > 0uz; )
		{
			if (devices[i] == device)
			{
				devices.erase(devices.cbegin() + i);
				events.erase(events.cbegin() + i);
			}
		}
	}

	void MouseEventQueue::Clear() noexcept
	{
		devices.clear();
		events.clear();
	}
}
