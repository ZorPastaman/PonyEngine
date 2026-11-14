/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Impl:DeviceProperties;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::RawInput
{
	/// @brief Device properties.
	struct DeviceProperties final
	{
		std::string name; ///< Device name.
		std::string friendlyName; ///< Device friendly name.
		std::string interfaceName; ///< Device interface name.

		DeviceType type; ///< Device type.
		DeviceStyle style; ///< Device style.

		std::vector<FeatureEntry> features; ///< Device features.
	};
}
