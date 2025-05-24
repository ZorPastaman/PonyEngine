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

export module PonyEngine.Render.Core:IPipelineStateAgent;

import PonyEngine.Render;

import :PipelineStateDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Pipeline state agent.
	class IPipelineStateAgent
	{
		INTERFACE_BODY(IPipelineStateAgent)

		/// @brief Creates a GPU pipeline state.
		/// @param pipelineState CPU pipeline state.
		virtual void Create(const IPipelineState& pipelineState) = 0;
		/// @brief Destroys a GPU pipeline state.
		/// @param pipelineState CPU pipeline state.
		virtual void Destroy(const IPipelineState& pipelineState) = 0;
		/// @brief Updates a GPU pipeline state.
		/// @param pipelineState CPU pipeline state.
		/// @param dirtyFlags Pipeline state dirty flags.
		virtual void Update(const IPipelineState& pipelineState, PipelineStateDirtyFlag dirtyFlags) = 0;
	};
}
