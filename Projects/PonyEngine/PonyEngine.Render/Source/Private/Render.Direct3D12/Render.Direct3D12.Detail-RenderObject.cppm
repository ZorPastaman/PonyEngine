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
import <string>;
import <string_view>;

import PonyEngine.Render.Direct3D12;

import PonyMath.Core;

import :Mesh;
import :PipelineState;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 render object.
	class RenderObject final : public IRenderObject
	{
	public:
		/// @brief Creates a @p RenderObject.
		/// @param pipelineState Pipeline state.
		/// @param mesh Mesh.
		/// @param modelMatrix Model matrix.
		[[nodiscard("Pure constructor")]]
		RenderObject(const std::shared_ptr<PipelineState>& pipelineState, const std::shared_ptr<Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept;
		[[nodiscard("Pure constructor")]]
		RenderObject(const RenderObject& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		RenderObject(RenderObject&& other) noexcept = default;

		~RenderObject() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Core::Matrix4x4<float>& ModelMatrix() const noexcept override;
		virtual void ModelMatrix(const PonyMath::Core::Matrix4x4<float>& matrix) noexcept override;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		class PipelineState& PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const class PipelineState& PipelineState() const noexcept;

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
		std::shared_ptr<class PipelineState> pipelineState; ///< Pipeline state.
		std::shared_ptr<class Mesh> mesh; ///< Mesh.
		PonyMath::Core::Matrix4x4<float> modelMatrix; ///< Model matrix.

		std::string name;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	RenderObject::RenderObject(const std::shared_ptr<class PipelineState>& pipelineState, const std::shared_ptr<class Mesh>& mesh, const PonyMath::Core::Matrix4x4<float>& modelMatrix) noexcept :
		pipelineState(pipelineState),
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

	PipelineState& RenderObject::PipelineState() noexcept
	{
		return *pipelineState;
	}

	const PipelineState& RenderObject::PipelineState() const noexcept
	{
		return *pipelineState;
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
