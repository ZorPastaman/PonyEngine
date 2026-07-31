/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Ext:DeviceParams;

import std;

import PonyEngine.RawInput;

import :FeatureEntry;

export namespace PonyEngine::RawInput
{
	/// @brief Device parameters.
	struct DeviceParams final
	{
		std::string_view name; ///< Device name.
		DeviceType type; ///< Device type.
		DeviceStyle style; ///< Device style.
		std::span<const FeatureEntry> features; ///< Device features.
	};
}
