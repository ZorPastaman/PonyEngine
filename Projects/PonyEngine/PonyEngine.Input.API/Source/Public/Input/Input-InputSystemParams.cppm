/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputSystemParams;

import <cstddef>;
import <memory>;
import <unordered_map>;
import <vector>;

import :IDeviceFactory;
import :InputBindingInfo;

export namespace PonyEngine::Input
{
	/// @brief Input system parameters.
	struct InputSystemParams final
	{
		std::vector<std::shared_ptr<IDeviceFactory>> inputDeviceFactories; ///< Input device factories.
		std::unordered_map<std::string, InputBindingInfo> inputBindings; ///< Input bindings.

		std::size_t inputEventsPerFrame = 100; ///< Expected number of input events per frame. It's used to preallocate memory and doesn't limit a count of events.
	};
}
