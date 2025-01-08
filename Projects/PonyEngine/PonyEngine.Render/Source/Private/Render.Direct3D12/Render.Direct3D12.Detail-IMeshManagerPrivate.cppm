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
	class IMeshManagerPrivate
	{
		INTERFACE_BODY(IMeshManagerPrivate)

		/// @brief Creates a render mesh.
		/// @param mesh Mesh.
		/// @return Render mesh.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Mesh> CreateDirect3D12Mesh(const std::shared_ptr<const Render::Mesh>& mesh) = 0;
	};
}
