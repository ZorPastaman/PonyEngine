/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Event;

import :KeyboardMessage;

export namespace PonyEngine::Input
{
	/// @brief Input event.
	class Event final
	{
	public:
		/// @brief Creates an input event.
		/// @param expectedMessage The event is raised if the input system receives such an event.
		[[nodiscard("Pure constructor")]]
		explicit Event(const KeyboardMessage& expectedMessage) noexcept;
		[[nodiscard("Pure constructor")]]
		Event(const Event& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Event(Event&& other) noexcept = default;

		~Event() noexcept = default;

		/// @brief Gets the expected message.
		/// @return Expected message.
		[[nodiscard("Pure function")]]
		KeyboardMessage& ExpectedMessage() noexcept;
		/// @brief Gets the expected message.
		/// @return Expected message.
		[[nodiscard("Pure function")]]
		const KeyboardMessage& ExpectedMessage() const noexcept;

		Event& operator =(const Event& other) noexcept = default;
		Event& operator =(Event&& other) noexcept = default;

	private:
		KeyboardMessage expectedMessage; ///< The event is raised if the input system receives such an event.
	};
}

namespace PonyEngine::Input
{
	Event::Event(const KeyboardMessage& expectedMessage) noexcept :
		expectedMessage{expectedMessage}
	{
	}

	KeyboardMessage& Event::ExpectedMessage() noexcept
	{
		return expectedMessage;
	}

	const KeyboardMessage& Event::ExpectedMessage() const noexcept
	{
		return expectedMessage;
	}
}
