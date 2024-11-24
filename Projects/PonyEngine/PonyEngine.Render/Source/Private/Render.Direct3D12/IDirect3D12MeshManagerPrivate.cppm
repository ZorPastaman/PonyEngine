/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12MeshManagerPrivate;

import <memory>;

import PonyMath.Geometry;

import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class IDirect3D12MeshManagerPrivate
	{
		INTERFACE_BODY(IDirect3D12MeshManagerPrivate)

		[[nodiscard("Pure constructor")]]
		virtual std::shared_ptr<Direct3D12Mesh> CreateDirect3D12Mesh(const PonyMath::Geometry::Mesh& mesh) = 0;
	};
}
