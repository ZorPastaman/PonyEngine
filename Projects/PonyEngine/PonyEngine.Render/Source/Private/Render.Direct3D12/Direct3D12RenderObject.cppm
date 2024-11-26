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

import <memory>;

import PonyMath.Core;

import PonyEngine.Render.Direct3D12;

import :Direct3D12Material;
import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final : public IDirect3D12RenderObject
	{
	public:
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const std::shared_ptr<Direct3D12Material>& material, const std::shared_ptr<Direct3D12Mesh>& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept = default;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Core::Matrix4x4<float> ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<FLOAT>& ModelMatrixD3D12() const noexcept override;
		virtual void ModelMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept override;

		[[nodiscard("Pure function")]]
		Direct3D12Material& Material() noexcept;
		[[nodiscard("Pure function")]]
		const Direct3D12Material& Material() const noexcept;

		[[nodiscard("Pure function")]]
		Direct3D12Mesh& Mesh() noexcept;
		[[nodiscard("Pure function")]]
		const Direct3D12Mesh& Mesh() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept = default;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept = default;

	private:
		std::shared_ptr<Direct3D12Material> material;
		std::shared_ptr<Direct3D12Mesh> mesh;
		PonyMath::Core::Matrix4x4<FLOAT> modelMatrix;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const std::shared_ptr<Direct3D12Material>& material, const std::shared_ptr<Direct3D12Mesh>& mesh, const PonyMath::Core::Matrix4x4<FLOAT>& modelMatrix) noexcept :
		material(material),
		mesh(mesh),
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

	const PonyMath::Core::Matrix4x4<FLOAT>& Direct3D12RenderObject::ModelMatrixD3D12() const noexcept
	{
		return modelMatrix;
	}

	void Direct3D12RenderObject::ModelMatrixD3D12(const PonyMath::Core::Matrix4x4<FLOAT>& matrix) noexcept
	{
		modelMatrix = matrix;
	}

	Direct3D12Material& Direct3D12RenderObject::Material() noexcept
	{
		return *material;
	}

	Direct3D12Mesh& Direct3D12RenderObject::Mesh() noexcept
	{
		return *mesh;
	}

	const Direct3D12Material& Direct3D12RenderObject::Material() const noexcept
	{
		return *material;
	}

	const Direct3D12Mesh& Direct3D12RenderObject::Mesh() const noexcept
	{
		return *mesh;
	}
}
