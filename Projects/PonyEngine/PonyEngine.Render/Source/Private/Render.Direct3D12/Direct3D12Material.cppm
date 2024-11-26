/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Material;

import <memory>;
import <optional>;

import :Direct3D12MaterialParams;
import :Direct3D12RootSignature;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 material.
	class Direct3D12Material final
	{
	public:
		/// @brief Creates a @p Direct3D12Material.
		/// @param rootSignature Root signature. Mustn't be nullptr.
		/// @param pipelineState Pipeline state.
		/// @param params Material parameters. They must be synced with the @p rootSignature and @p pipelineState.
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, const Direct3D12MaterialParams& params) noexcept;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const Direct3D12Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(Direct3D12Material&& other) noexcept = default;

		~Direct3D12Material() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		Direct3D12RootSignature& RootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const Direct3D12RootSignature& RootSignature() const noexcept;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& GetPipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& GetPipelineState() const noexcept;
		/// @brief Gets the primitive topology.
		/// @return Primitive topology.
		[[nodiscard("Pure function")]]
		D3D_PRIMITIVE_TOPOLOGY PrimitiveTopology() const noexcept;

		/// @brief Gets vertex slot.
		/// @return Vertex slot.
		[[nodiscard("Pure function")]]
		UINT VertexSlot() const noexcept;
		/// @brief Gets vertex color slot.
		/// @return Vertex color slot. It's @a nullopt if the material doesn't support it.
		[[nodiscard("Pure function")]]
		std::optional<UINT> VertexColorSlot() const noexcept;

		Direct3D12Material& operator =(const Direct3D12Material& other) noexcept = default;
		Direct3D12Material& operator =(Direct3D12Material&& other) noexcept = default;

	private:
		std::shared_ptr<Direct3D12RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.
		D3D_PRIMITIVE_TOPOLOGY primitiveTopology; ///< Primitive topology.

		UINT vertexSlot; ///< Vertex slot.
		std::optional<UINT> vertexColorSlot; ///< Vertex color slot.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Material::Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, const Direct3D12MaterialParams& params) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState),
		primitiveTopology{params.primitiveTopology},
		vertexSlot{params.vertexSlot},
		vertexColorSlot(params.vertexColorSlot)
	{
		assert(this->rootSignature && "The root signature is nullptr.");
	}

	Direct3D12RootSignature& Direct3D12Material::RootSignature() noexcept
	{
		return *rootSignature;
	}

	const Direct3D12RootSignature& Direct3D12Material::RootSignature() const noexcept
	{
		return *rootSignature;
	}

	ID3D12PipelineState& Direct3D12Material::GetPipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& Direct3D12Material::GetPipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	D3D_PRIMITIVE_TOPOLOGY Direct3D12Material::PrimitiveTopology() const noexcept
	{
		return primitiveTopology;
	}

	UINT Direct3D12Material::VertexSlot() const noexcept
	{
		return vertexSlot;
	}

	std::optional<UINT> Direct3D12Material::VertexColorSlot() const noexcept
	{
		return vertexColorSlot;
	}
}
