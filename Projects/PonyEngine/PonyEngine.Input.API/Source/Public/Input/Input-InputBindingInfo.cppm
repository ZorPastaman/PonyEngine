/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputBindingInfo;

import <vector>;

import :InputBindingValue;

export namespace PonyEngine::Input
{
	/// @brief Input binding info.
	struct InputBindingInfo final
	{
		std::vector<InputBindingValue> inputBindingValues; ///< Input binding values.

		std::size_t inputReceiverCount = 0; ///< Expected number of input receivers. It's used to preallocate memory and doesn't limit a count of receivers.
	};
}
