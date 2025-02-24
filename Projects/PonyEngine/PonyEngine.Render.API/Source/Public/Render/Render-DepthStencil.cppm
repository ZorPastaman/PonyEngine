/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:DepthStencil;

import :ComparisonFunction;
import :StencilFace;

export namespace PonyEngine::Render
{
	struct DepthStencil final
	{
		bool depth = true;
		bool depthWrite = true;
		ComparisonFunction depthFunc = ComparisonFunction::Less;

		bool stencil = true;
		StencilFace stencilFront;
		StencilFace stencilBack;

		[[nodiscard("Pure operator")]]
		bool operator ==(const DepthStencil& other) const noexcept = default;
	};
}
