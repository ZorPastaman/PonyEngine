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

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12MeshManagerPrivate;

import <memory>;

import PonyEngine.Render;

import :Direct3D12IndexFormat;
import :Direct3D12Mesh;
import :Direct3D12VertexFormat;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh manager.
	class IDirect3D12MeshManagerPrivate
	{
		INTERFACE_BODY(IDirect3D12MeshManagerPrivate)

		/// @brief Creates a render mesh.
		/// @param mesh Mesh.
		/// @return Render mesh.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const std::shared_ptr<const Mesh>& mesh) = 0;
	};
}
