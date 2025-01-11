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

export module PonyEngine.Render.Direct3D12.Detail:Transform;

import PonyMath.Core;

export namespace PonyEngine::Render::Direct3D12
{
	class Transform final
	{
	public:
		static constexpr UINT ComponentCount = PonyMath::Core::Matrix4x4<FLOAT>::ComponentCount * 4;

		[[nodiscard("Pure constructor")]]
		Transform() noexcept;
		[[nodiscard("Pure constructor")]]
		Transform(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		Transform(const Transform& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Transform(Transform&& other) noexcept = default;

		~Transform() noexcept = default;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& ModelMatrix() const noexcept;
		void ModelMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& ViewMatrix() const noexcept;
		void ViewMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& ProjectionMatrix() const noexcept;
		void ProjectionMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrixToSet) noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& MvpMatrix() const noexcept;

		[[nodiscard("Pure function")]]
		const FLOAT* Data() const noexcept;

		void Set(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrixToSet, const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrixToSet, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrixToSet) noexcept;

		Transform& operator =(const Transform& other) noexcept = default;
		Transform& operator =(Transform&& other) noexcept = default;

	private:
		void UpdateMvp() noexcept;

		PonyMath::Core::Matrix4x4<FLOAT> modelMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> viewMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> projectionMatrix;
		PonyMath::Core::Matrix4x4<FLOAT> mvpMatrix;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Transform::Transform() noexcept :
		Transform(PonyMath::Core::Matrix4x4<FLOAT>::Predefined::Identity, PonyMath::Core::Matrix4x4<FLOAT>::Predefined::Identity, PonyMath::Core::Matrix4x4<FLOAT>::Predefined::Identity)
	{
	}

	Transform::Transform(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrix, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrix) noexcept :
		modelMatrix{modelMatrix},
		viewMatrix{viewMatrix},
		projectionMatrix{projectionMatrix}
	{
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Transform::ModelMatrix() const noexcept
	{
		return modelMatrix;
	}

	void Transform::ModelMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrixToSet) noexcept
	{
		modelMatrix = modelMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Transform::ViewMatrix() const noexcept
	{
		return viewMatrix;
	}

	void Transform::ViewMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrixToSet) noexcept
	{
		viewMatrix = viewMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Transform::ProjectionMatrix() const noexcept
	{
		return projectionMatrix;
	}

	void Transform::ProjectionMatrix(const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrixToSet) noexcept
	{
		projectionMatrix = projectionMatrixToSet;
		UpdateMvp();
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Transform::MvpMatrix() const noexcept
	{
		return mvpMatrix;
	}

	const FLOAT* Transform::Data() const noexcept
	{
		return modelMatrix.Span().data();
	}

	void Transform::Set(const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrixToSet, const PonyMath::Core::Matrix4x4<FLOAT>& viewMatrixToSet, const PonyMath::Core::Matrix4x4<FLOAT>& projectionMatrixToSet) noexcept
	{
		modelMatrix = modelMatrixToSet;
		viewMatrix = viewMatrixToSet;
		projectionMatrix = projectionMatrixToSet;
		UpdateMvp();
	}

	void Transform::UpdateMvp() noexcept
	{
		mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	}
}
