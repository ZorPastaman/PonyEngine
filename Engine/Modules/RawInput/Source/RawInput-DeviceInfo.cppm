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
		std::string_view friendlyName; ///< Device friendly name.
		std::string_view interfaceName; ///< Device interface name. It's a source API name.

		DeviceType type; ///< Device type.
		DeviceStyle style; ///< Device style.
	};
}
