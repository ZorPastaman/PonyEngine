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

import PonyMath.Geometry;

import :IRenderObject;
import :RenderObjectHandle;

export namespace PonyEngine::Render
{
	class IRenderObjectManager
	{
		INTERFACE_BODY(IRenderObjectManager)

		virtual RenderObjectHandle CreateObject(const PonyMath::Geometry::Mesh& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix = PonyMath::Core::Matrix4x4<float>::Predefined::Identity) = 0;
		virtual void DestroyObject(RenderObjectHandle handle) noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual IRenderObject* FindRenderObject(RenderObjectHandle handle) const noexcept = 0;
	};
}
