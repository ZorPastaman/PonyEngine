/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl:KeyboardEventQueue;

import std;

import PonyEngine.RawInput;

import :KeyboardEvent;

export namespace PonyEngine::RawInput
{
	/// @brief Keyboard event queue.
	/// @tparam NativeKeyType Native key type.
	template<typename NativeKeyType>
	class KeyboardEventQueue final
	{
	public:
		[[nodiscard("Pure constructor")]]
		KeyboardEventQueue() noexcept = default;
		[[nodiscard("Pure constructor")]]
		KeyboardEventQueue(const KeyboardEventQueue& other) = default;
		[[nodiscard("Pure constructor")]]
		KeyboardEventQueue(KeyboardEventQueue&& other) noexcept = default;

		~KeyboardEventQueue() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Gets a keyboard device.
		/// @param index Event index.
		/// @return Device.
		[[nodiscard("Pure function")]]
		DeviceHandle Device(std::size_t index) const noexcept;
		/// @brief Gets a keyboard event.
		/// @param index Event index.
		/// @return Keyboard event.
		[[nodiscard("Pure function")]]
		const KeyboardEvent<NativeKeyType>& Event(std::size_t index) const noexcept;

		/// @brief Adds the event.
		/// @param device Device handle.
		/// @param event Keyboard event.
		void Add(DeviceHandle device, const KeyboardEvent<NativeKeyType>& event);
		/// @brief Removes all the keyboard devices.
		/// @param device Device handle.
		void Remove(DeviceHandle device) noexcept;
		/// @brief Clears all the data.
		void Clear() noexcept;

		KeyboardEventQueue& operator =(const KeyboardEventQueue& other) = delete;
		KeyboardEventQueue& operator =(KeyboardEventQueue&& other) noexcept = default;

	private:
		std::vector<DeviceHandle> devices; ///< Keyboard device handles.
		std::vector<KeyboardEvent<NativeKeyType>> events; ///< Keyboard events.
	};
}

namespace PonyEngine::RawInput
{
	template<typename NativeKeyType>
	std::size_t KeyboardEventQueue<NativeKeyType>::Size() const noexcept
	{
		return devices.size();
	}

	template<typename NativeKeyType>
	DeviceHandle KeyboardEventQueue<NativeKeyType>::Device(const std::size_t index) const noexcept
	{
		return devices[index];
	}

	template<typename NativeKeyType>
	const KeyboardEvent<NativeKeyType>& KeyboardEventQueue<NativeKeyType>::Event(const std::size_t index) const noexcept
	{
		return events[index];
	}

	template<typename NativeKeyType>
	void KeyboardEventQueue<NativeKeyType>::Add(const DeviceHandle device, const KeyboardEvent<NativeKeyType>& event)
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

	template<typename NativeKeyType>
	void KeyboardEventQueue<NativeKeyType>::Remove(const DeviceHandle device) noexcept
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

	template<typename NativeKeyType>
	void KeyboardEventQueue<NativeKeyType>::Clear() noexcept
	{
		devices.clear();
		events.clear();
	}
}
