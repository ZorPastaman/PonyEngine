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

import PonyEngine.Render;

import :ObjectUtility;
import :RootSignature;
import :Shader;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 material.
	class Material final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Material() noexcept;
		/// @brief Creates a @p Material.
		/// @param rootSignature Root signature. Mustn't be nullptr.
		/// @param pipelineState Pipeline state.
		[[nodiscard("Pure constructor")]]
		Material(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, bool isTransparent) noexcept;
		[[nodiscard("Pure constructor")]]
		Material(const Material& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		Material(Material&& other) noexcept = default;

		~Material() noexcept = default;

		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		class RootSignature* RootSignature() noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const class RootSignature* RootSignature() const noexcept;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState* PipelineState() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState* PipelineState() const noexcept;

		/// @brief Gets if the material is transparent.
		/// @return @a True if the material is transparent; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsTransparent() const noexcept;

		[[nodiscard("Pure function")]]
		struct ThreadGroupCounts& ThreadGroupCounts() noexcept;
		[[nodiscard("Pure function")]]
		const struct ThreadGroupCounts& ThreadGroupCounts() const noexcept;

		[[nodiscard("Pure function")]]
		std::int32_t& RenderQueue() noexcept;
		[[nodiscard("Pure function")]]
		const std::int32_t& RenderQueue() const noexcept;

		[[nodiscard("Pure function")]]
		bool& CameraCulling() noexcept;
		[[nodiscard("Pure function")]]
		const bool& CameraCulling() const noexcept;

		/// @brief Sets the name to the material components.
		/// @param name Name.
		void Name(std::string_view name);

		Material& operator =(const Material& other) noexcept = default;
		Material& operator =(Material&& other) noexcept = default;

	private:
		std::shared_ptr<class RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.

		struct ThreadGroupCounts threadGroupCounts;
		std::int32_t renderQueue;
		bool cameraCulling;

		bool isTransparent;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	Material::Material() noexcept :
		threadGroupCounts(),
		renderQueue{0},
		cameraCulling{true},
		isTransparent{true}
	{
	}

	Material::Material(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, const bool isTransparent) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState),
		threadGroupCounts(),
		renderQueue{0},
		cameraCulling{true},
		isTransparent{isTransparent}
	{
	}

	class RootSignature* Material::RootSignature() noexcept
	{
		return rootSignature.get();
	}

	const class RootSignature* Material::RootSignature() const noexcept
	{
		return rootSignature.get();
	}

	ID3D12PipelineState* Material::PipelineState() noexcept
	{
		return pipelineState.Get();
	}

	const ID3D12PipelineState* Material::PipelineState() const noexcept
	{
		return pipelineState.Get();
	}

	bool Material::IsTransparent() const noexcept
	{
		return isTransparent;
	}

	struct ThreadGroupCounts& Material::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	const struct ThreadGroupCounts& Material::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	std::int32_t& Material::RenderQueue() noexcept
	{
		return renderQueue;
	}

	const std::int32_t& Material::RenderQueue() const noexcept
	{
		return renderQueue;
	}

	bool& Material::CameraCulling() noexcept
	{
		return cameraCulling;
	}

	const bool& Material::CameraCulling() const noexcept
	{
		return cameraCulling;
	}

	void Material::Name(const std::string_view name)
	{
		SetName(*pipelineState.Get(), name);
	}
}
