/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CBVRequirement;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Constant buffer view requirement.
	struct CBVRequirement final
	{
		std::uint32_t offsetAlignment = 0u; ///< Offset alignment.
		std::uint32_t sizeAlignment = 0u; ///< Size alignment.
	};
}
