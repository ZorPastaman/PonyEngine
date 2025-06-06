/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstdint>
#include <optional>
#include <string_view>

export module PonyEngine.Log:LogInput;

export namespace PonyEngine::Log
{
	/// @brief Log data input.
	struct LogInput final
	{
		std::string_view message; ///< Log message.
		std::optional<std::uint64_t> frameCount = {}; ///< Engine frame count.
	};
}
