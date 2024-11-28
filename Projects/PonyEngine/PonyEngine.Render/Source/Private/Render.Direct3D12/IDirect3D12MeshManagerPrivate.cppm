/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12MeshManagerPrivate;

import <memory>;

import PonyMath.Geometry;

import :Direct3D12IndexFormat;
import :Direct3D12Mesh;
import :Direct3D12VertexFormat;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 mesh manager.
	class IDirect3D12MeshManagerPrivate
	{
		INTERFACE_BODY(IDirect3D12MeshManagerPrivate)

		/// @brief Gets the vertex format.
		/// @return Vertex format.
		[[nodiscard("Pure function")]]
		virtual const Direct3D12VertexFormat& VertexFormat() const noexcept = 0;
		/// @brief Gets the vertex color format.
		/// @return Vertex color format.
		[[nodiscard("Pure function")]]
		virtual const Direct3D12VertexFormat& VertexColorFormat() const noexcept = 0;
		/// @brief Gets the index format.
		/// @return Index format.
		[[nodiscard("Pure function")]]
		virtual const Direct3D12IndexFormat& VertexIndexFormat() const noexcept = 0;

		/// @brief Creates a render mesh.
		/// @param mesh Mesh.
		/// @return Render mesh.
		[[nodiscard("Pure constructor")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh) = 0;
	};
}
