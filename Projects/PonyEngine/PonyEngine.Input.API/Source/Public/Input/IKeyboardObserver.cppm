/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Input:IKeyboardObserver;

import :KeyboardMessage;

export namespace PonyEngine::Input
{
	/// @brief Keyboard input observer.
	class IKeyboardObserver
	{
		INTERFACE_BODY(IKeyboardObserver)

		/// @brief Receives a keyboard input.
		/// @param keyboardMessage Keyboard message.
		virtual void Observe(const KeyboardMessage& keyboardMessage) = 0;
	};
}
