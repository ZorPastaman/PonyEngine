/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputEvent;

import :ActionId;
import :DeviceHandle;
import :InputEventType;

export namespace PonyEngine::Input
{
	/// @brief Input event.
	struct InputEvent final
	{
		ActionId actionId; ///< Action ID.
		std::span<const float> values; ///< Values.
		DeviceHandle deviceHandle; ///< Device handle.
		InputEventType eventType = InputEventType::State; ///< Event type.
	};
}
