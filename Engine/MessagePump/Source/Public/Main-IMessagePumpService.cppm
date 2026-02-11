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

export module PonyEngine.MessagePump:IMessagePumpService;

import PonyEngine.Math;

import :MessagePumpFeature;

export namespace PonyEngine::MessagePump
{
	/// @brief Message pump service.
	/// @note By default, all the functions here are thread-safe unless stated otherwise.
	class IMessagePumpService
	{
		PONY_INTERFACE_BODY(IMessagePumpService)

		/// @brief Gets the supported features.
		/// @return Supported features.
		[[nodiscard("Pure function")]]
		virtual MessagePumpFeature SupportedFeatures() const noexcept = 0;

		/// @brief Gets the time of the last message.
		/// @return Time of the last message. It's a low resolution time point.
		/// @note Don't call it when the message pump service is ticking.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTime() const noexcept = 0;
		/// @brief Gets the cursor position of the last message.
		/// @return Cursor position in the screen coordinates of the last message.
		/// @note Don't call it when the message pump service is ticking.
		[[nodiscard("Pure function")]]
		virtual Math::Vector2<std::int32_t> LastMessageCursorPosition() const noexcept = 0;
	};
}
