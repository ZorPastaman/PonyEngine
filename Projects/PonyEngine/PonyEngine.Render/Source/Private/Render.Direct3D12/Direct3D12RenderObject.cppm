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

export module PonyEngine.Render.Direct3D12:Direct3D12RenderObject;

import PonyBase.Math;

import :Direct3D12Mesh;

export namespace PonyEngine::Render
{
	class Direct3D12RenderObject final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit Direct3D12RenderObject(const Direct3D12Mesh& meshResource, const PonyBase::Math::Matrix4x4<FLOAT>& trs) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(const Direct3D12RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12RenderObject(Direct3D12RenderObject&& other) noexcept = default;

		~Direct3D12RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		const Direct3D12Mesh& RenderMesh() const noexcept;

		[[nodiscard("Pure function")]]
		PonyBase::Math::Matrix4x4<FLOAT>& TrsMatrix() noexcept;
		[[nodiscard("Pure function")]]
		const PonyBase::Math::Matrix4x4<FLOAT>& TrsMatrix() const noexcept;

		Direct3D12RenderObject& operator =(const Direct3D12RenderObject& other) noexcept = default;
		Direct3D12RenderObject& operator =(Direct3D12RenderObject&& other) noexcept = default;

	private:
		Direct3D12Mesh meshResource;
		PonyBase::Math::Matrix4x4<FLOAT> trsMatrix;
	};
}

namespace PonyEngine::Render
{
	Direct3D12RenderObject::Direct3D12RenderObject(const Direct3D12Mesh& meshResource, const PonyBase::Math::Matrix4x4<FLOAT>& trs) noexcept :
		meshResource(meshResource),
		trsMatrix(trs)
	{
	}

	const Direct3D12Mesh& Direct3D12RenderObject::RenderMesh() const noexcept
	{
		return meshResource;
	}

	PonyBase::Math::Matrix4x4<FLOAT>& Direct3D12RenderObject::TrsMatrix() noexcept
	{
		return trsMatrix;
	}

	const PonyBase::Math::Matrix4x4<FLOAT>& Direct3D12RenderObject::TrsMatrix() const noexcept
	{
		return trsMatrix;
	}
}
