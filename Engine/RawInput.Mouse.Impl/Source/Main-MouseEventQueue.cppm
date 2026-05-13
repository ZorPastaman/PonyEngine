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
		std::size_t DeviceIndex(std::size_t index) const noexcept;
		/// @brief Gets a mouse event.
		/// @param index Event index.
		/// @return Mouse event.
		[[nodiscard("Pure function")]]
		const MouseEvent& Event(std::size_t index) const noexcept;

		/// @brief Adds the event.
		/// @param deviceIndex Device index.
		/// @param event Mouse event.
		void Add(std::size_t deviceIndex, const MouseEvent& event);
		/// @brief Clears all the data.
		void Clear() noexcept;

		MouseEventQueue& operator =(const MouseEventQueue& other) = delete;
		MouseEventQueue& operator =(MouseEventQueue&& other) noexcept = default;

	private:
		std::vector<std::size_t> deviceIndices; ///< Mouse device indices.
		std::vector<MouseEvent> events; ///< Mouse events.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	std::size_t MouseEventQueue::Size() const noexcept
	{
		return deviceIndices.size();
	}

	std::size_t MouseEventQueue::DeviceIndex(const std::size_t index) const noexcept
	{
		return deviceIndices[index];
	}

	const MouseEvent& MouseEventQueue::Event(const std::size_t index) const noexcept
	{
		return events[index];
	}

	void MouseEventQueue::Add(const std::size_t deviceIndex, const MouseEvent& event)
	{
		deviceIndices.push_back(deviceIndex);
		try
		{
			events.push_back(event);
		}
		catch (...)
		{
			deviceIndices.pop_back();
			throw;
		}
	}

	void MouseEventQueue::Clear() noexcept
	{
		deviceIndices.clear();
		events.clear();
	}
}
