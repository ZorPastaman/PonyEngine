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

namespace PonyEngine::Input
{
	/// @brief Input event.
	export struct Event final
	{
	public:
		/// @brief Creates an input event.
		/// @param expectedMessage The event is raised if the input system receives such an event.
		[[nodiscard("Pure constructor")]]
		explicit inline Event(const KeyboardMessage& expectedMessage) noexcept;
		[[nodiscard("Pure constructor")]]
		inline Event(const Event& other) noexcept = default;

		inline ~Event() noexcept = default;

		/// @brief Gets an expected message.
		/// @return Expected message.
		inline const KeyboardMessage& GetExpectedMessage() const noexcept;

		inline Event& operator =(const Event& other) noexcept = default;

	private:
		KeyboardMessage m_expectedMessage; /// @brief The event is raised if the input system receives such an event.
	};

	inline Event::Event(const KeyboardMessage& expectedMessage) noexcept :
		m_expectedMessage{expectedMessage}
	{
	}

	inline const KeyboardMessage& Event::GetExpectedMessage() const noexcept
	{
		return m_expectedMessage;
	}
}
