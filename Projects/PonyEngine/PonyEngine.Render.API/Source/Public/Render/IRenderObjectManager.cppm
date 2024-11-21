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

import PonyMath.Core;
import PonyMath.Geometry;

import :IRenderObject;
import :RenderObjectHandle;

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
		virtual RenderObjectHandle CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity) = 0;
		/// @brief Destroys a render object.
		/// @param handle Handle of the render object to destroy.
		virtual void DestroyObject(RenderObjectHandle handle) noexcept = 0;

		/// @brief Finds a render object by the @p handle.
		/// @param handle Render object handle.
		/// @return Render object if it's found; @a nullptr otherwise.
		[[nodiscard("Pure function")]]
		virtual IRenderObject* FindRenderObject(RenderObjectHandle handle) const noexcept = 0;
	};
}
