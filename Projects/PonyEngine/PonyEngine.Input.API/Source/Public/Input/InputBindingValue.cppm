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
	/// @brief Input binding value. It's the second element a table pair.
	struct InputBindingValue final
	{
		InputCode inputCode; ///< Input code.
		float multiplier = 1.f; ///< Input multiplier.
	};
}
