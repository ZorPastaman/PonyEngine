/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencilParams;

import std;

import :ComparisonFunc;
import :StencilOperation;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth parameters.
	struct DepthParams final
	{
		bool depthWrite = true; ///< Is the depth write enable?
		ComparisonFunc comparisonFunc = ComparisonFunc::Less; ///< Depth comparison function.
		bool depthBoundsTest = false; ///< Is the depth bounds test enable?
	};

	/// @brief Stencil operation parameters.
	struct StencilOperationParams final
	{
		StencilOperation failOperation = StencilOperation::Keep; ///< Operation that is executed when a stencil test fails.
		StencilOperation depthFailOperation = StencilOperation::Keep; ///< Operation that is executed when a stencil test passes but a depth test fails.
		StencilOperation passOperation = StencilOperation::Keep; ///< Operation that is executed when both a stencil and a depth tests pass.
		ComparisonFunc stencilFunc = ComparisonFunc::Always; ///< Stencil comparison function.
		std::uint8_t readMask = std::numeric_limits<std::uint8_t>::max(); ///< Stencil read mask.
		std::uint8_t writeMask = std::numeric_limits<std::uint8_t>::max(); ///< Stencil write mask.
	};

	/// @brief Stencil parameters.
	struct StencilParams final
	{
		StencilOperationParams frontFace; ///< Stencil operation parameters for front faced pixels.
		StencilOperationParams backFace; ///< Stencil operation parameters for back faced pixels.
	};

	/// @brief Depth stencil parameters.
	struct DepthStencilParams final
	{
		std::optional<DepthParams> depth; ///< Depth parameters. Nullopt means depth test is disable.
		std::optional<StencilParams> stencil; ///< Stencil parameters. Nullopt means stencil test is disable.
	};
}
