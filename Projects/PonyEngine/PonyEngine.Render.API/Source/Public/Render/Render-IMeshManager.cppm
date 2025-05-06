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

export module PonyEngine.Render:IMeshManager;

import <memory>;

import :IMesh;
import :MeshParams;

export namespace PonyEngine::Render
{
	/// @brief Mesh manager.
	class IMeshManager
	{
		INTERFACE_BODY(IMeshManager)

		/// @brief Creates a mesh.
		/// @param params Mesh parameters.
		/// @return Mesh.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IMesh> CreateMesh(const MeshParams& params) = 0;
	};
}
