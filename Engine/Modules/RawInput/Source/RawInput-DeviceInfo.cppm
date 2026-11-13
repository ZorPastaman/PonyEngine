/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:DeviceInfo;

import std;

import :DeviceStyle;
import :DeviceType;

export namespace PonyEngine::RawInput
{
	/// @brief Device info.
	struct DeviceInfo final
	{
		std::string_view name; ///< Device name.
		DeviceType type; ///< Device type.
		DeviceStyle style; ///< Device style.
	};
}
