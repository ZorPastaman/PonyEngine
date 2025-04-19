/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Space:Transform;

import PonyMath.Core;

export namespace PonyShader::Space
{
	/// @brief Render transform. It corresponds to @p Pony_Transform in PonyShader/Space/Transform.hlsli on the HLSL side.
	/// @details It contains model, view and projection matrices. And it always has an actual mvp matrix as well.
	class alignas(256) Transform final
	{
	public:
		/// @brief Creates an identity transform.
		[[nodiscard("Pure constructor")]]
		constexpr Transform() noexcept;
		/// @brief Creates transform.
		/// @param modelMatrix Model matrix.
		/// @param viewMatrix View matrix.
		/// @param projectionMatrix Projection matrix.
		[[nodiscard("Pure constructor")]]
		constexpr Transform(const PonyMath::Core::Matrix4x4<float>& modelMatrix, const PonyMath::Core::Matrix4x4<float>& viewMatrix, const PonyMath::Core::Matrix4x4<float>& projectionMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		constexpr Transform(const Transform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr Transform(Transform&& other) noexcept = default;

		constexpr ~Transform() noexcept = default;

		/// @brief Gets the model matrix.
		/// @return Model matrix.
		[[nodiscard("Pure function")]]
		constexpr const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept;
		/// @brief Gets the model matrix.
		/// @return Model matrix.
		constexpr void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept;

		/// @brief Gets the view matrix.
		/// @return View matrix.
		[[nodiscard("Pure function")]]
		constexpr const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept;
		/// @brief Gets the view matrix.
		/// @return View matrix.
		constexpr void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept;

		/// @brief Gets the projection matrix.
		/// @return Projection matrix.
		[[nodiscard("Pure function")]]
		constexpr const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept;
		/// @brief Gets the projection matrix.
		/// @return Projection matrix.
		constexpr void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept;

		/// @brief Gets the mvp matrix.
		/// @return MVP matrix.
		[[nodiscard("Pure function")]]
		constexpr const PonyMath::Core::Matrix4x4<float>& MvpMatrix() const noexcept;

		constexpr Transform& operator =(const Transform& other) noexcept = default;
		constexpr Transform& operator =(Transform&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const Transform& other) const noexcept;

	private:
		/// @brief Update mvp matrix by current model, view and projection matrices.
		constexpr void UpdateMvp() noexcept;

		PonyMath::Core::Matrix4x4<float> modelMatrix; ///< Model matrix.
		PonyMath::Core::Matrix4x4<float> viewMatrix; ///< View matrix.
		PonyMath::Core::Matrix4x4<float> projectionMatrix; ///< Projection matrix.
		PonyMath::Core::Matrix4x4<float> mvpMatrix; ///< MVP matrix. 
	};

	/// @brief Checks if the two transforms are almost equal with the tolerance value.
	/// @param left Left transform.
	/// @param right Right transform.
	/// @param tolerance Tolerance. Must be positive.
	/// @return @a True if they are almost equal; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool AreAlmostEqual(const Transform& left, const Transform& right, float tolerance = 0.00001f) noexcept;
}

namespace PonyShader::Space
{
	constexpr Transform::Transform() noexcept :
		modelMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		viewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		projectionMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		mvpMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity)
	{
	}

	constexpr Transform::Transform(const PonyMath::Core::Matrix4x4<float>& modelMatrix, const PonyMath::Core::Matrix4x4<float>& viewMatrix, const PonyMath::Core::Matrix4x4<float>& projectionMatrix) noexcept :
		modelMatrix(modelMatrix),
		viewMatrix(viewMatrix),
		projectionMatrix(projectionMatrix)
	{
		UpdateMvp();
	}

	constexpr const PonyMath::Core::Matrix4x4<float>& Transform::ModelMatrix() const noexcept
	{
		return modelMatrix;
	}

	constexpr void Transform::ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		modelMatrix = matrix;
		UpdateMvp();
	}

	constexpr const PonyMath::Core::Matrix4x4<float>& Transform::ViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	constexpr void Transform::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		viewMatrix = matrix;
		UpdateMvp();
	}

	constexpr const PonyMath::Core::Matrix4x4<float>& Transform::ProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	constexpr void Transform::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		projectionMatrix = matrix;
		UpdateMvp();
	}

	constexpr const PonyMath::Core::Matrix4x4<float>& Transform::MvpMatrix() const noexcept
	{
		return mvpMatrix;
	}

	constexpr void Transform::UpdateMvp() noexcept
	{
		mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	}

	constexpr bool Transform::operator ==(const Transform& other) const noexcept
	{
		return modelMatrix == other.modelMatrix && viewMatrix == other.viewMatrix && projectionMatrix == other.projectionMatrix;
	}

	constexpr bool AreAlmostEqual(const Transform& left, const Transform& right, const float tolerance) noexcept
	{
		return PonyMath::Core::AreAlmostEqual(left.ModelMatrix(), right.ModelMatrix(), tolerance) &&
			PonyMath::Core::AreAlmostEqual(left.ViewMatrix(), right.ViewMatrix(), tolerance) &&
			PonyMath::Core::AreAlmostEqual(left.ProjectionMatrix(), right.ProjectionMatrix(), tolerance);
	}
}
