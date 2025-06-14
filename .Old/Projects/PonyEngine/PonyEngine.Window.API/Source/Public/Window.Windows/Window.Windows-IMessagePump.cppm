/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Window.Windows:IMessagePump;

import <span>;

import :IMessageObserver;

export namespace PonyEngine::Window::Windows
{
	/// @brief Windows message pump.
	class IMessagePump
	{
		INTERFACE_BODY(IMessagePump)

		/// @brief Adds the message observer.
		/// @note It's not supported to add the same message observer twice in a row. If you need to update its message types, you should remove it first.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe. Examples: WM_KEYDOWN, WM_KEYUP.
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IMessageObserver& observer) = 0;
	};
}
