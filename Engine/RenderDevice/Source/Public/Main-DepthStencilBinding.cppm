/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencilBinding;

import std;

import :IDepthStencilContainer;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil binding.
	struct DepthStencilBinding final
	{
		const IDepthStencilContainer* container = nullptr; ///< Depth stencil container. Must be a valid container.
		std::uint32_t index = 0u; ///< Container view index. Must be less than the @p container size.
	};
}
