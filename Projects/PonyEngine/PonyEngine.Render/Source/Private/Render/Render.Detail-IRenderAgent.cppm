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

export module PonyEngine.Render.Detail:IRenderAgent;

import :IMeshAgent;
import :IPipelineStateAgent;
import :IRootSignatureAgent;

export namespace PonyEngine::Render
{
	/// @brief Render agent.
	class IRenderAgent
	{
		INTERFACE_BODY(IRenderAgent)

		/// @brief Gets the root signature agent.
		/// @return Root signature agent.
		[[nodiscard("Pure function")]]
		virtual IRootSignatureAgent& RootSignatureAgent() noexcept = 0;
		/// @brief Gets the root signature agent.
		/// @return Root signature agent.
		[[nodiscard("Pure function")]]
		virtual const IRootSignatureAgent& RootSignatureAgent() const noexcept = 0;

		/// @brief Gets the pipeline state agent.
		/// @return Pipeline state agent.
		[[nodiscard("Pure function")]]
		virtual IPipelineStateAgent& PipelineStateAgent() noexcept = 0;
		/// @brief Gets the pipeline state agent.
		/// @return Pipeline state agent.
		[[nodiscard("Pure function")]]
		virtual const IPipelineStateAgent& PipelineStateAgent() const noexcept = 0;

		/// @brief Gets the mesh agent.
		/// @return Mesh agent.
		[[nodiscard("Pure function")]]
		virtual IMeshAgent& MeshAgent() noexcept = 0;
		/// @brief Gets the mesh agent.
		/// @return Mesh agent.
		[[nodiscard("Pure function")]]
		virtual const IMeshAgent& MeshAgent() const noexcept = 0;
	};
}
