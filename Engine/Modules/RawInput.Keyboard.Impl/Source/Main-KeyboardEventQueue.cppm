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

import :KeyboardEvent;

export namespace PonyEngine::RawInput::Keyboard
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
		std::size_t DeviceIndex(std::size_t index) const noexcept;
		/// @brief Gets a keyboard event.
		/// @param index Event index.
		/// @return Keyboard event.
		[[nodiscard("Pure function")]]
		const KeyboardEvent<NativeKeyType>& Event(std::size_t index) const noexcept;

		/// @brief Adds the event.
		/// @param deviceIndex Device index.
		/// @param event Keyboard event.
		void Add(std::size_t deviceIndex, const KeyboardEvent<NativeKeyType>& event);
		/// @brief Clears all the data.
		void Clear() noexcept;

		KeyboardEventQueue& operator =(const KeyboardEventQueue& other) = delete;
		KeyboardEventQueue& operator =(KeyboardEventQueue&& other) noexcept = default;

	private:
		std::vector<std::size_t> deviceIndices; ///< Keyboard device indices.
		std::vector<KeyboardEvent<NativeKeyType>> events; ///< Keyboard events.
	};
}

namespace PonyEngine::RawInput::Keyboard
{
	template<typename NativeKeyType>
	std::size_t KeyboardEventQueue<NativeKeyType>::Size() const noexcept
	{
		return deviceIndices.size();
	}

	template<typename NativeKeyType>
	std::size_t KeyboardEventQueue<NativeKeyType>::DeviceIndex(const std::size_t index) const noexcept
	{
		return deviceIndices[index];
	}

	template<typename NativeKeyType>
	const KeyboardEvent<NativeKeyType>& KeyboardEventQueue<NativeKeyType>::Event(const std::size_t index) const noexcept
	{
		return events[index];
	}

	template<typename NativeKeyType>
	void KeyboardEventQueue<NativeKeyType>::Add(const std::size_t deviceIndex, const KeyboardEvent<NativeKeyType>& event)
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

	template<typename NativeKeyType>
	void KeyboardEventQueue<NativeKeyType>::Clear() noexcept
	{
		deviceIndices.clear();
		events.clear();
	}
}
