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

export module PonyEngine.Input:IKeyboardProvider;

import :IKeyboardObserver;

export namespace PonyEngine::Input
{
	/// @brief Keyboard input provider.
	class IKeyboardProvider
	{
		INTERFACE_BODY(IKeyboardProvider)

		/// @brief Adds a keyboard input observer.
		/// @param keyboardObserver Keyboard input observer. It mustn't be already added.
		virtual void AddKeyboardObserver(IKeyboardObserver& keyboardObserver) = 0;
		/// @brief Removes a keyboard input observer.
		/// @param keyboardObserver Keyboard input observer.
		virtual void RemoveKeyboardObserver(IKeyboardObserver& keyboardObserver) = 0;
	};
}
