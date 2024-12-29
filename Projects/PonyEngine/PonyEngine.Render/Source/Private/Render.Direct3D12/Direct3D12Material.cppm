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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Material;

import <memory>;
import <optional>;
import <string>;
import <string_view>;

import :Direct3D12ObjectUtility;
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
		[[nodiscard("Pure constructor")]]
		Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState) noexcept;
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
		ID3D12PipelineState& PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& PipelineState() const noexcept;

		/// @brief Gets vertex slot.
		/// @return Vertex slot.
		[[nodiscard("Pure function")]]
		UINT VertexSlot() const noexcept;
		/// @brief Gets vertex color slot.
		/// @return Vertex color slot. It's @a nullopt if the material doesn't support it.
		[[nodiscard("Pure function")]]
		std::optional<UINT> VertexColorSlot() const noexcept;

		/// @brief Sets the name to the material components.
		/// @param name Name.
		void Name(std::string_view name);

		Direct3D12Material& operator =(const Direct3D12Material& other) noexcept = default;
		Direct3D12Material& operator =(Direct3D12Material&& other) noexcept = default;

	private:
		std::shared_ptr<Direct3D12RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.
	};
}

namespace PonyEngine::Render
{
	Direct3D12Material::Direct3D12Material(const std::shared_ptr<Direct3D12RootSignature>& rootSignature, ID3D12PipelineState& pipelineState) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState)
	{
	}

	Direct3D12RootSignature& Direct3D12Material::RootSignature() noexcept
	{
		return *rootSignature;
	}

	const Direct3D12RootSignature& Direct3D12Material::RootSignature() const noexcept
	{
		return *rootSignature;
	}

	ID3D12PipelineState& Direct3D12Material::PipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& Direct3D12Material::PipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	void Direct3D12Material::Name(const std::string_view name)
	{
		constexpr std::string_view pipelineStateName = " - PipelineState";
		auto componentName = std::string();
		componentName.reserve(name.size() + pipelineStateName.size());
		componentName.append(name).append(pipelineStateName);
		SetName(*pipelineState.Get(), componentName);
	}
}
