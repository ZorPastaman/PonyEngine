/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Core:RenderObject;

import <memory>;
import <optional>;
import <string>;
import <string_view>;

import PonyMath.Core;

import PonyEngine.Render;

export namespace PonyEngine::Render::Core
{
	/// @brief Render object.
	class RenderObject final : public IRenderObject
	{
	public:
		/// @brief Creates a render object.
		/// @param params Render object parameters.
		[[nodiscard("Pure constructor")]]
		explicit RenderObject(const RenderObjectParams& params) noexcept;
		RenderObject(const RenderObject&) = delete;
		RenderObject(RenderObject&&) = delete;

		~RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IMaterial>& Material() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IMesh> Mesh() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;
		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelInverseMatrix() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		RenderObject& operator =(const RenderObject&) = delete;
		RenderObject& operator =(RenderObject&&) = delete;

	private:
		std::shared_ptr<const IMaterial> material; ///< Render object material.
		std::shared_ptr<const IMesh> mesh; ///< Render object mesh.

		PonyMath::Core::Matrix4x4<float> modelMatrix; ///< Render object model matrix.
		mutable std::optional<PonyMath::Core::Matrix4x4<float>> modelInverseMatrix; ///< Inverse of the render object model matrix.

		std::string name; ///< Render object name.
	};
}

namespace PonyEngine::Render::Core
{
	RenderObject::RenderObject(const RenderObjectParams& params) noexcept :
		material(params.material),
		mesh(params.mesh),
		modelMatrix(params.modelMatrix),
		name(params.name)
	{
	}

	const std::shared_ptr<const IMaterial>& RenderObject::Material() const noexcept
	{
		return material;
	}

	const std::shared_ptr<const IMesh> RenderObject::Mesh() const noexcept
	{
		return mesh;
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

	std::string_view RenderObject::Name() const noexcept
	{
		return name;
	}

	void RenderObject::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
	}
}
