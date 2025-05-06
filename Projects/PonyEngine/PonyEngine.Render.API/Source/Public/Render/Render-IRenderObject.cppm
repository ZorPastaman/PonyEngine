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

export module PonyEngine.Render:IRenderObject;

import <string_view>;

import PonyMath.Core;

import :IMaterial;
import :IMesh;

export namespace PonyEngine::Render
{
	/// @brief Render object.
	class IRenderObject
	{
		INTERFACE_BODY(IRenderObject)

		/// @brief Gets the material.
		/// @return Material.
		[[nodiscard("Pure function")]]
		virtual IMaterial& Material() const noexcept = 0;
		/// @brief Gets the mesh.
		/// @return Mesh.
		[[nodiscard("Pure function")]]
		virtual IMesh* Mesh() const noexcept = 0;

		/// @brief Gets the translation-rotation-scaling matrix of the object.
		/// @return Translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept = 0;
		/// @brief Sets the translation-rotation-scaling matrix of the object.
		/// @param matrix Translation-rotation-scaling matrix.
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept = 0;
		/// @brief Gets the inverse of the translation-rotation-scaling matrix of the object.
		/// @return Inverse of the translation-rotation-scaling matrix.
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelInverseMatrix() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
