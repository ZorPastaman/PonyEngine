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
	struct StencilOperationParams final
	{
		StencilOperation failOperation = StencilOperation::Keep;
		StencilOperation depthFailOperation = StencilOperation::Keep;
		StencilOperation passOperation = StencilOperation::Keep;
		ComparisonFunc stencilFunc = ComparisonFunc::Always;
		std::uint8_t readMask = std::numeric_limits<std::uint8_t>::max();
		std::uint8_t writeMask = std::numeric_limits<std::uint8_t>::max();
	};

	struct DepthParams final
	{
		bool depthWrite = true;
		ComparisonFunc comparisonFunc = ComparisonFunc::Less;
		bool depthBoundsTest = false;
	};

	struct StencilParams final
	{
		StencilOperationParams frontFace;
		StencilOperationParams backFace;
	};

	struct DepthStencilParams final
	{
		std::optional<DepthParams> depth = DepthParams{};
		std::optional<StencilParams> stencil;
	};
}
