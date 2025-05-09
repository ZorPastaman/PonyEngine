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

export namespace PonyEngine::Render
{
	/// @brief Render agent.
	class IRenderAgent
	{
		INTERFACE_BODY(IRenderAgent)

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
