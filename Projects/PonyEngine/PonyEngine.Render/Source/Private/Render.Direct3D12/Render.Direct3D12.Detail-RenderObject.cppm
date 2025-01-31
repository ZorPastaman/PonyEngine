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

export module PonyEngine.Render.Direct3D12.Detail:RenderObject;

import <memory>;

import PonyEngine.Render.Direct3D12;

import PonyMath.Core;

import :Material;
import :Mesh;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render object.
	class RenderObject final : public IRenderObject
	{
	public:
		/// @brief Creates a @p RenderObject.
		/// @param material Material.
		/// @param mesh Mesh.
		/// @param modelMatrix Model matrix.
		[[nodiscard("Pure constructor")]]
		RenderObject(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		RenderObject(const RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		RenderObject(RenderObject&& other) noexcept = default;

		~RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		/// @brief Gets the material.
		/// @return Material.
		[[nodiscard("Pure function")]]
		class Material& Material() noexcept;
		/// @brief Gets the material.
		/// @return Material.
		[[nodiscard("Pure function")]]
		const class Material& Material() const noexcept;

		/// @brief Gets the mesh.
		/// @return Mesh.
		[[nodiscard("Pure function")]]
		class Mesh& Mesh() noexcept;
		/// @brief Gets the mesh.
		/// @return Mesh.
		[[nodiscard("Pure function")]]
		const class Mesh& Mesh() const noexcept;

		RenderObject& operator =(const RenderObject& other) noexcept = default;
		RenderObject& operator =(RenderObject&& other) noexcept = default;

	private:
		std::shared_ptr<class Material> material; ///< Material.
		std::shared_ptr<class Mesh> mesh; ///< Mesh.
		PonyMath::Core::Matrix4x4<float> modelMatrix; ///< Model matrix.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RenderObject::RenderObject(const std::shared_ptr<class Material>& material, const std::shared_ptr<class Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept :
		material(material),
		mesh(mesh),
		modelMatrix(modelMatrix)
	{
	}

	const PonyMath::Core::Matrix4x4<float>& RenderObject::ModelMatrix() const noexcept
	{
		return modelMatrix;
	}

	void RenderObject::ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		modelMatrix = matrix;
	}

	Material& RenderObject::Material() noexcept
	{
		return *material;
	}

	const Material& RenderObject::Material() const noexcept
	{
		return *material;
	}

	Mesh& RenderObject::Mesh() noexcept
	{
		return *mesh;
	}

	const Mesh& RenderObject::Mesh() const noexcept
	{
		return *mesh;
	}
}
