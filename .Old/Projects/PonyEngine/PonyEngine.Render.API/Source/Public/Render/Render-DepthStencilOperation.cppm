/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:DepthStencilOperation;

import :ComparisonFunction;
import :StencilOperation;

export namespace PonyEngine::Render
{
	/// @brief Depth stencil operation.
	struct DepthStencilOperation final
	{
		StencilOperation failOperation = StencilOperation::Keep; ///< Operation on stencil testing fail.
		StencilOperation depthFailOperation = StencilOperation::Keep; ///< Operation on stencil testing pass and depth testing fail.
		StencilOperation passOperation = StencilOperation::Keep; ///< Operation on both stencil and depth testings pass.
		ComparisonFunction stencilComparison = ComparisonFunction::Always; ///< Stencil comparison function.

		[[nodiscard("Pure operator")]]
		bool operator ==(const DepthStencilOperation& other) const noexcept = default;
	};
}
