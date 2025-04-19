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

export module PonyEngine.Render.Direct3D12.Detail:IPipelineStateManager;

import <memory>;

import PonyEngine.Render;

import :PipelineState;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 pipeline state manager.
	class IPipelineStateManager
	{
		INTERFACE_BODY(IPipelineStateManager)

		/// @brief Creates a Direct3D12 pipeline state.
		/// @param pipelineState Pipeline state.
		/// @return Direct3D12 pipeline state.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<PipelineState> CreatePipelineState(const std::shared_ptr<const Render::PipelineState>& pipelineState) = 0;
	};
}
