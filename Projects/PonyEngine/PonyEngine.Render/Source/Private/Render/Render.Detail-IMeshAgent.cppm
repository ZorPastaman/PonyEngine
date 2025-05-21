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

export module PonyEngine.Render.Detail:IMeshAgent;

import PonyEngine.Render;

import :MeshDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Mesh agent.
	class IMeshAgent
	{
		INTERFACE_BODY(IMeshAgent)

		/// @brief Creates a GPU mesh.
		/// @param mesh CPU mesh.
		virtual void Create(const IMesh& mesh) = 0;
		/// @brief Destroys a GPU mesh.
		/// @param mesh CPU mesh.
		virtual void Destroy(const IMesh& mesh) = 0;
		/// @brief Updates a GPU mesh.
		/// @param mesh CPU mesh.
		/// @param dirtyFlags Dirty flags.
		virtual void Update(const IMesh& mesh, MeshDirtyFlag dirtyFlags) = 0;
	};
}
