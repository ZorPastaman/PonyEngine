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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12RenderObject;

import PonyMath.Core;

import PonyEngine.Render.Direct3D12;

import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final : public IDirect3D12RenderObject
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObject(const Direct3D12Mesh& meshResource, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept = default;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		const Direct3D12Mesh& RenderMesh() const noexcept;

		[[nodiscard("Pure function")]]
		const PonyMath::Core::Matrix4x4<FLOAT>& TargetModelMatrix() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept = default;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept = default;

	private:
		Direct3D12Mesh meshResource;
		PonyMath::Core::Matrix4x4<FLOAT> modelMatrix;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12Mesh& meshResource, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix) noexcept :
		meshResource(meshResource),
		modelMatrix(modelMatrix)
	{
	}

	PonyMath::Core::Matrix4x4<float> Direct3D12RenderObject::ModelMatrix() const noexcept
	{
		return static_cast<PonyMath::Core::Matrix4x4<float>>(modelMatrix);
	}

	void Direct3D12RenderObject::ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept
	{
		modelMatrix = static_cast<PonyMath::Core::Matrix4x4<FLOAT>>(matrix);
	}

	const Direct3D12Mesh& Direct3D12RenderObject::RenderMesh() const noexcept
	{
		return meshResource;
	}

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderObject::TargetModelMatrix() const noexcept
	{
		return modelMatrix;
	}
}
