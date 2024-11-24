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

export module PonyEngine.Render.Direct3D12:IDirect3D12RenderObject;

import PonyEngine.Render;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 render object.
	class IDirect3D12RenderObject : public IRenderObject
	{
		INTERFACE_BODY(IDirect3D12RenderObject)

		/// @brief Gets the translation-rotation-scaling matrix of the object.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ModelMatrixD3D12() const noexcept = 0;
		/// @brief Sets the translation-rotation-scaling matrix of the object.
		/// @param matrix Translation-rotation-scaling matrix.
		virtual void ModelMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept = 0;
	};
}
