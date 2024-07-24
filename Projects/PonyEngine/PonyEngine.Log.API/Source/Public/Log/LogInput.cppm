/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogInput;

import <cstddef>;

export namespace PonyEngine::Log
{
	/// @brief Log data input.
	struct LogInput final
	{
		const char* message = ""; ///< Log message.
		std::size_t frameCount = 0; ///< Engine frame count.
	};
}
