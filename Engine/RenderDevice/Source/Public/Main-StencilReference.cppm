/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:StencilReference;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Stencil reference.
	struct StencilReference final
	{
		std::uint32_t front = 0u; ///< Front faced reference.
		std::uint32_t back = 0u; ///< Back faced reference.
	};
}
