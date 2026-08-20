/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.File:WriteParams;

import std;

export namespace PonyEngine::File
{
	/// @brief Write parameters.
	struct WriteParams final
	{
		std::span<const std::byte> buffer; ///< Output buffer. Must be kept alive till the end of an operation.
		std::size_t offset = 0uz; ///< File offset.
	};
}
