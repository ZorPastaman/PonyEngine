/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Direct3D12.Detail:RenderObject;

import <memory>;
import <optional>;
import <string>;
import <string_view>;

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
		RenderObject(const std::shared_ptr<class Material>& material, const std::shared_ptr<class Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept;
		/// @brief Creates a @p RenderObject.
		/// @param material Material.
		/// @param mesh Mesh.
		/// @param modelMatrix Model matrix.
		[[nodiscard("Pure constructor")]]
		RenderObject(std::shared_ptr<class Material>&& material, std::shared_ptr<class Mesh>&& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		RenderObject(const RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		RenderObject(RenderObject&& other) noexcept = default;

		~RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelInverseMatrix() const noexcept override;

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
		class Mesh* Mesh() noexcept;
		/// @brief Gets the mesh.
		/// @return Mesh.
		[[nodiscard("Pure function")]]
		const class Mesh* Mesh() const noexcept;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		RenderObject& operator =(const RenderObject& other) noexcept = default;
		RenderObject& operator =(RenderObject&& other) noexcept = default;

	private:
		std::shared_ptr<class Material> material; ///< Pipeline state.
		std::shared_ptr<class Mesh> mesh; ///< Mesh.

		PonyMath::Core::Matrix4x4<float> modelMatrix; ///< Model matrix.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> modelInverseMatrix; ///< Inverse of the model matrix.

		std::string name; ///< Render object name.
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

	RenderObject::RenderObject(std::shared_ptr<class Material>&& material, std::shared_ptr<class Mesh>&& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept :
		material(std::move(material)),
		mesh(std::move(mesh)),
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
		modelInverseMatrix = std::nullopt;
	}

	const PonyMath::Core::Matrix4x4<float>& RenderObject::ModelInverseMatrix() const noexcept
	{
		if (!modelInverseMatrix)
		{
			modelInverseMatrix = modelMatrix.Inverse();
		}

		return modelInverseMatrix.value();
	}

	Material& RenderObject::Material() noexcept
	{
		return *material;
	}

	const Material& RenderObject::Material() const noexcept
	{
		return *material;
	}

	Mesh* RenderObject::Mesh() noexcept
	{
		return mesh.get();
	}

	const Mesh* RenderObject::Mesh() const noexcept
	{
		return mesh.get();
	}

	std::string_view RenderObject::Name() const noexcept
	{
		return name;
	}

	void RenderObject::Name(const std::string_view name)
	{
		this->name = name;
	}
}
