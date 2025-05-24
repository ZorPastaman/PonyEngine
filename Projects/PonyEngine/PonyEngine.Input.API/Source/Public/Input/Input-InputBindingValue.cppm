/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputBindingValue;

import :InputCode;

export namespace PonyEngine::Input
{
	/// @brief Input binding value.
	struct InputBindingValue final
	{
		// TODO: Use uint here. Input code must be just a predefined indices. So users can easily extend the system and add their own devices.
		InputCode inputCode; ///< Input code.
		float multiplier = 1.f; ///< Input multiplier.
	};
}
