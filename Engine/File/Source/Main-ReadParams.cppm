/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File:ReadParams;

import std;

export namespace PonyEngine::File
{
	/// @brief Read parameters.
	struct ReadParams final
	{
		std::span<std::byte> buffer; ///< Input buffer. Its size determines how many bytes are read from a file.
		std::size_t offset = 0uz; ///< File offset.
	};
}
