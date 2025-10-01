/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"
#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Application.Windows:IMessageLoopService;

import std;

import :IMessageObserver;

export namespace PonyEngine::Application::Windows
{
	/// @brief Message loop service.
	class IMessageLoopService
	{
		INTERFACE_BODY(IMessageLoopService)

		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageType Message type to observe. Example: WM_QUIT.
		/// @remark It observes only global messages, not window-specific messages.
		virtual void AddMessageObserver(IMessageObserver& observer, UINT messageType) = 0;
		/// @brief Adds the message observer.
		/// @param observer Observer to add.
		/// @param messageTypes Message types to observe. Example: WM_QUIT.
		/// @remark It observes only global messages, not window-specific messages.
		virtual void AddMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) = 0;
		/// @brief Removes the message observer from the specified message type.
		/// @param observer Observer to remove.
		/// @param messageType Message type to observe. Example: WM_QUIT.
		virtual void RemoveMessageObserver(IMessageObserver& observer, UINT messageType) noexcept = 0;
		/// @brief Removes the message observer from the specified message types.
		/// @param observer Observer to remove.
		/// @param messageTypes Message types to observe. Example: WM_QUIT.
		virtual void RemoveMessageObserver(IMessageObserver& observer, std::span<const UINT> messageTypes) noexcept = 0;
		/// @brief Removes the message observer from all the message types.
		/// @param observer Observer to remove.
		virtual void RemoveMessageObserver(IMessageObserver& observer) noexcept = 0;
	};
}
