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

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderObjectManager;

import <memory>;

import PonyEngine.Render;

import :IDirect3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render object manager.
	class IDirect3D12RenderObjectManager : public IRenderObjectManager
	{
		INTERFACE_BODY(IDirect3D12RenderObjectManager)

		/// @brief Creates a render object.
		/// @param mesh Render object mesh.
		/// @param modelMatrix Render object translation-rotation-scaling matrix.
		/// @return Render object handle.
		virtual std::shared_ptr<IDirect3D12RenderObject> CreateObjectD3D12(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix = PonyMath::Core::Matrix4x4<FLOAT>::Predefined::Identity) = 0;
	};
}
