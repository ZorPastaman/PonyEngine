/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CBVParams;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Constant buffer view parameters.
	struct CBVParams final
	{
		std::uint64_t offset = 0ull; ///< Buffer offset. Must be correctly aligned.
		std::uint32_t size = 0u; ///< View size. Must be correctly aligned.
	};
}
