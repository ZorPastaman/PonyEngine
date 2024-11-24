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

export module PonyEngine.Render:IRenderObjectManager;

import <memory>;

import PonyMath.Core;
import PonyMath.Geometry;

import :IRenderObject;

export namespace PonyEngine::Render
{
	/// @brief Render object manager.
	class IRenderObjectManager
	{
		INTERFACE_BODY(IRenderObjectManager)

		/// @brief Creates a render object.
		/// @param mesh Render object mesh.
		/// @param modelMatrix Render object translation-rotation-scaling matrix.
		/// @return Render object handle.
		virtual std::shared_ptr<IRenderObject> CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity) = 0;
	};
}
