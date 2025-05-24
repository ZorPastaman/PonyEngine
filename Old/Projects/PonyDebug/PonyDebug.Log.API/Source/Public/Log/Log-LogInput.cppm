/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LogInput;

import <cstdint>;
import <optional>;
import <string_view>;

export namespace PonyDebug::Log
{
	/// @brief Log data input.
	struct LogInput final
	{
		std::string_view message; ///< Log message.
		std::optional<std::int64_t> frameCount = {}; ///< Engine frame count.
	};
}
