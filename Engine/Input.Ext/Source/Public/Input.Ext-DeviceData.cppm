/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Ext:DeviceData;

import std;

import PonyEngine.Input;

import :IDevice;

export namespace PonyEngine::Input
{
	/// @brief Device data.
	struct DeviceData final
	{
		std::shared_ptr<IDevice> device; ///< Device.
		std::vector<std::reference_wrapper<const std::type_info>> layouts; ///< Device layouts.
		std::unordered_map<std::reference_wrapper<const std::type_info>, void*> features; ///< Device features.
	};
}
