/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Windows:IMessagePump;

import std;

export namespace PonyEngine::Application
{
	/// @brief Message pump data provider.
	class IMessagePump
	{
		PONY_INTERFACE_BODY(IMessagePump)

		/// @brief Gets a last message type.
		/// @return Message type.
		/// @note Must be called on a main thread.
		/// @remark Updated before dispatching.
		[[nodiscard("Pure function")]]
		virtual UINT LastMessageType() const noexcept = 0;
		/// @brief Gets a last message native time point.
		/// @return Message native time point.
		/// @note Must be called on a main thread.
		/// @remark Updated before dispatching.
		[[nodiscard("Pure function")]]
		virtual DWORD LastMessageNativeTimePoint() const noexcept = 0;
		/// @brief Gets a last message time point.
		/// @return Message time point.
		/// @note Must be called on a main thread.
		/// @remark Updated before dispatching.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTimePoint() const noexcept = 0;
		/// @brief Gets a last message cursor point.
		/// @return Message cursor point.
		/// @note Must be called on a main thread.
		/// @remark Updated before dispatching.
		[[nodiscard("Pure function")]]
		virtual POINT LastMessageCursorPoint() const noexcept = 0;
	};
}
