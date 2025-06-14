/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:IPipelineStateManager;

import <memory>;

import :IPipelineState;
import :PipelineStateParams;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state manager.
	class IPipelineStateManager
	{
		INTERFACE_BODY(IPipelineStateManager)

		/// @brief Creates a pipeline state.
		/// @param params Pipeline state parameters.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IPipelineState> CreatePipelineState(const PipelineStateParams& params) = 0;
	};
}
