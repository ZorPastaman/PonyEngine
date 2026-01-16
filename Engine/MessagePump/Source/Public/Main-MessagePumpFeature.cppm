/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.MessagePump:MessagePumpFeature;

import std;

namespace PonyEngine::MessagePump
{
	/// @brief Message pump feature names.
	std::array<std::string_view, 2> MessagePumpFeatureNames
	{
		"Message Time",
		"Cursor Position"
	};
}

export namespace PonyEngine::MessagePump
{
	/// @brief Message pump feature.
	enum class MessagePumpFeature : std::uint8_t
	{
		None = 0,
		MessageTime = 1 << 0, ///< Detects a time when a message was created.
		CursorPosition = 1 << 1, ///< Detects a cursor position when a message was created.
		All = MessageTime | CursorPosition
	};

	PONY_ENUM_MASK_FEATURES(MessagePumpFeature)
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::MessagePump::MessagePumpFeature, PonyEngine::MessagePump::MessagePumpFeatureNames)
}
