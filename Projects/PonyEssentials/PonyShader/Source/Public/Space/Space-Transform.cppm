/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyShader.Space:Transform;

import <cstdint>;

import PonyMath.Core;

export namespace PonyShader::Space
{
	class Transform final
	{
	public:
		static constexpr std::uint32_t ComponentCount = PonyMath::Core::Matrix4x4<float>::ComponentCount * 4;

		[[nodiscard("Pure constructor")]]
		Transform() noexcept;
		[[nodiscard("Pure constructor")]]
		Transform(const PonyMath::Core::Matrix4x4<float>& modelMatrix, const PonyMath::Core::Matrix4x4<float>& viewMatrix, const PonyMath::Core::Matrix4x4<float>& projectionMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform(const Transform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform(Transform&& other) noexcept = default;

		~Transform() noexcept = default;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept;
		void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& modelMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& ViewMatrix() const noexcept;
		void ViewMatrix(const PonyMath::Core::Matrix4x4<float>& viewMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& ProjectionMatrix() const noexcept;
		void ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& projectionMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<float>& MvpMatrix() const noexcept;

		Transform& operator =(const Transform& other) noexcept = default;
		Transform& operator =(Transform&& other) noexcept = default;

	private:
		void UpdateMvp() noexcept;

		PonyMath::Core::Matrix4x4<float> modelMatrix;
		PonyMath::Core::Matrix4x4<float> viewMatrix;
		PonyMath::Core::Matrix4x4<float> projectionMatrix;
		PonyMath::Core::Matrix4x4<float> mvpMatrix;
	};
}

namespace PonyShader::Space
{
	Transform::Transform() noexcept :
		modelMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		viewMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		projectionMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity),
		mvpMatrix(PonyMath::Core::Matrix4x4<float>::Predefined::Identity)
	{
	}

	Transform::Transform(const PonyMath::Core::Matrix4x4<float>& modelMatrix, const PonyMath::Core::Matrix4x4<float>& viewMatrix, const PonyMath::Core::Matrix4x4<float>& projectionMatrix) noexcept :
		modelMatrix{modelMatrix},
		viewMatrix{viewMatrix},
		projectionMatrix{projectionMatrix}
	{
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<float>& Transform::ModelMatrix() const noexcept
	{
		return modelMatrix;
	}

	void Transform::ModelMatrix(const PonyMath::Core::Matrix4x4<float>& modelMatrixToSet) noexcept
	{
		modelMatrix = modelMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<float>& Transform::ViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	void Transform::ViewMatrix(const PonyMath::Core::Matrix4x4<float>& viewMatrixToSet) noexcept
	{
		viewMatrix = viewMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<float>& Transform::ProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	void Transform::ProjectionMatrix(const PonyMath::Core::Matrix4x4<float>& projectionMatrixToSet) noexcept
	{
		projectionMatrix = projectionMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<float>& Transform::MvpMatrix() const noexcept
	{
		return mvpMatrix;
	}

	void Transform::UpdateMvp() noexcept
	{
		mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	}
}
