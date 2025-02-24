/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:StencilFace;

import :ComparisonFunction;
import :StencilOperation;

export namespace PonyEngine::Render
{
	struct StencilFace final
	{
		StencilOperation failOperation = StencilOperation::Keep;
		StencilOperation depthFailOperation = StencilOperation::Keep;
		StencilOperation passOperation = StencilOperation::Keep;
		ComparisonFunction comparison = ComparisonFunction::Always;

		[[nodiscard("Pure operator")]]
		bool operator ==(const StencilFace& other) const noexcept = default;
	};
}
