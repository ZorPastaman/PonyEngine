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
		inline Event() noexcept = default;
		/// @brief Creates an input event.
		/// @param expectedMessage The event is raised if the input system receives such an event.
		[[nodiscard("Pure constructor")]]
		inline Event(Window::KeyboardMessage expectedMessage) noexcept;
		[[nodiscard("Pure constructor")]]
		inline Event(const Event& other) noexcept = default;
		inline Event(Event&& other) noexcept = default;

		inline ~Event() noexcept = default;

		inline Event& operator =(const Event& other) noexcept = default;
		inline Event& operator =(Event&& other) noexcept = default;

		Window::KeyboardMessage expectedMessage; /// @brief The event is raised if the input system receives such an event.
	};

	inline Event::Event(const Window::KeyboardMessage expectedMessage) noexcept :
		expectedMessage{expectedMessage}
	{
	}
}
