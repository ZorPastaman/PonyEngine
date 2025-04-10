/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:DepthStencil;

import <limits>;

import :ComparisonFunction;
import :DepthStencilOperation;

export namespace PonyEngine::Render
{
	/// @brief Depth stencil parameters.
	struct DepthStencil final
	{
		bool depth = true; ///< Is the depth testing enabled?
		bool depthWrite = true; ///< Is the depth writing enabled?
		ComparisonFunction depthFunc = ComparisonFunction::Less; ///< Depth comparison function.

		bool stencil = false; ///< Is the stencil testing enabled?
		std::uint8_t stencilReadMask = std::numeric_limits<std::uint8_t>::max(); ///< Stencil read mask.
		std::uint8_t stencilWriteMask = std::numeric_limits<std::uint8_t>::max(); ///< Stencil write mask.

		DepthStencilOperation frontFace; ///< Operation for front faced pixels.
		DepthStencilOperation backFace; ///< Operation for back faced pixels.

		[[nodiscard("Pure operator")]]
		bool operator ==(const DepthStencil& other) const noexcept = default;
	};
}
