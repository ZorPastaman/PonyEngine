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

export module PonyEngine.Render.Direct3D12.Detail:IMeshManagerPrivate;

import <memory>;

import PonyEngine.Render;

import :Mesh;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 mesh manager.
	class IMeshManager
	{
		INTERFACE_BODY(IMeshManager)

		/// @brief Creates a render mesh.
		/// @param mesh Source mesh.
		/// @return Render mesh.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Mesh> CreateMesh(const std::shared_ptr<const Render::Mesh>& mesh) = 0;
	};
}
