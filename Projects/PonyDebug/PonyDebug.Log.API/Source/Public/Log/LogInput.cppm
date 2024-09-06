/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LogInput;

import <cstddef>;
import <optional>;

export namespace PonyDebug::Log
{
	/// @brief Log data input.
	struct LogInput final
	{
		const char* message = nullptr; ///< Log message.
		std::optional<std::size_t> frameCount = {}; ///< Engine frame count.
	};
}
