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

export module PonyEngine.Render.Direct3D12.Detail:Material;

import <array>;
import <memory>;
import <optional>;
import <span>;
import <string>;
import <string_view>;

import :ObjectUtility;
import :RootSignature;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material.
	class Material final
	{
	public:
		/// @brief Creates a @p Material.
		/// @param rootSignature Root signature. Mustn't be nullptr.
		/// @param pipelineState Pipeline state.
		[[nodiscard("Pure constructor")]]
		Material(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState) noexcept;
		[[nodiscard("Pure constructor")]]
		Material(const Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept = default;

		~Material() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		class RootSignature& RootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const class RootSignature& RootSignature() const noexcept;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState& PipelineState() const noexcept;

		/// @brief Gets if the material is transparent.
		/// @return @a True if the material is transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsTransparent() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const UINT, 3> ThreadGroupCounts() const noexcept;

		/// @brief Sets the name to the material components.
		/// @param name Name.
		void Name(std::string_view name);

		Material& operator =(const Material& other) noexcept = default;
		Material& operator =(Material&& other) noexcept = default;

	private:
		std::shared_ptr<class RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.

		std::array<UINT, 3> threadGroupCounts = {1u, 1u, 1u};
		bool isTransparent = false; // TODO: Support material params.
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Material::Material(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState)
	{
	}

	class RootSignature& Material::RootSignature() noexcept
	{
		return *rootSignature;
	}

	const class RootSignature& Material::RootSignature() const noexcept
	{
		return *rootSignature;
	}

	ID3D12PipelineState& Material::PipelineState() noexcept
	{
		return *pipelineState.Get();
	}

	const ID3D12PipelineState& Material::PipelineState() const noexcept
	{
		return *pipelineState.Get();
	}

	bool Material::IsTransparent() const noexcept
	{
		return isTransparent;
	}

	std::span<const UINT, 3> Material::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	void Material::Name(const std::string_view name)
	{
		SetName(*pipelineState.Get(), name);
	}
}
