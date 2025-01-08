/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputSystemParams;

import <memory>;
import <unordered_map>;
import <vector>;

import :IDeviceFactory;
import :InputBindingValue;

export namespace PonyEngine::Input
{
	/// @brief Input system parameters.
	struct InputSystemParams final
	{
		std::vector<std::shared_ptr<IDeviceFactory>> inputDeviceFactories; ///< Input device factories.
		std::unordered_map<std::string, std::vector<InputBindingValue>> inputBindings; ///< Input bindings.
	};
}
