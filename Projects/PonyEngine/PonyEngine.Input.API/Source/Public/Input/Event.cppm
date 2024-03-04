/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Event;

import PonyEngine.Window;

namespace PonyEngine::Input
{
	/// @brief Input event.
	export struct Event final
	{
	public:
		/// @brief Creates an input event.
		/// @param expectedMessage The event is raised if the input system receives such an event.
		[[nodiscard("Pure constructor")]]
		constexpr inline Event(Window::Messages::KeyboardMessage expectedMessage) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		[[nodiscard("Pure constructor")]]
		constexpr inline Event(const Event& other) noexcept;
		Event(Event&&) = delete;

		constexpr inline ~Event() noexcept = default;

		/// @brief Copy assignment.
		/// @param other Copy source.
		/// @return @a This.
		constexpr inline Event& operator =(const Event& other) noexcept;

		Window::Messages::KeyboardMessage expectedMessage; /// @brief The event is raised if the input system receives such an event.
	};

	constexpr inline Event::Event(const Window::Messages::KeyboardMessage expectedMessage) noexcept :
		expectedMessage{expectedMessage}
	{
	}

	constexpr inline Event::Event(const Event& other) noexcept :
		expectedMessage{other.expectedMessage}
	{
	}

	constexpr inline Event& Event::operator =(const Event& other) noexcept
	{
		expectedMessage = other.expectedMessage;

		return *this;
	}
}
