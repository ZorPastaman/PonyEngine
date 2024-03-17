/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:IKeyboardObserver;

import PonyEngine.Utility;

import :KeyboardMessage;

namespace PonyEngine::Window
{
	/// @brief Object that accepts an input from a keyboard.
	export class IKeyboardObserver : public Utility::INamed
	{
	public:
		/// @brief Receives a new keyboard input.
		/// @param keyboardMessage Keyboard message.
		virtual void Observe(const KeyboardMessage& keyboardMessage) = 0;

	protected:
		inline virtual ~IKeyboardObserver() noexcept = default;
	};
}
