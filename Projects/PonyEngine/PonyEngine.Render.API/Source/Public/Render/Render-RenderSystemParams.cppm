/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:RenderSystemParams;

import :RenderTargetParams;
import :RenderViewParams;

export namespace PonyEngine::Render
{
	/// @brief Render system parameters.
	struct RenderSystemParams
	{
		RenderTargetParams renderTargetParams; ///< Render target parameters.
		RenderViewParams renderViewParams; ///< Render view parameters.
	};
}
