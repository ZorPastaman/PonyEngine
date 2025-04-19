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

export module PonyEngine.Render.Direct3D12.Detail:PipelineState;

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
	/// @brief Direct3D12 pipeline state.
	class PipelineState final
	{
	public:
		[[nodiscard("Pure constructor")]]
		PipelineState() noexcept;
		/// @brief Creates a @p Pipeline state.
		/// @param rootSignature Root signature. Mustn't be nullptr.
		/// @param pipelineState Pipeline state.
		/// @param isTransparent Is transparent?
		[[nodiscard("Pure constructor")]]
		PipelineState(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, bool isTransparent) noexcept;
		[[nodiscard("Pure constructor")]]
		PipelineState(const PipelineState& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PipelineState(PipelineState&& other) noexcept = default;

		~PipelineState() noexcept = default;

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
		ID3D12PipelineState* State() noexcept;
		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		const ID3D12PipelineState* State() const noexcept;

		/// @brief Gets if the pipeline state is transparent.
		/// @return @a True if the pipeline state is transparent; @a false otherwise.
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

		/// @brief Sets the name to the pipeline state components.
		/// @param name Name.
		void Name(std::string_view name);

		PipelineState& operator =(const PipelineState& other) noexcept = default;
		PipelineState& operator =(PipelineState&& other) noexcept = default;

	private:
		std::shared_ptr<class RootSignature> rootSignature; ///< Root signature.
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState; ///< Pipeline state.
		bool isTransparent;

		struct ThreadGroupCounts threadGroupCounts;
		std::int32_t renderQueue;
		bool cameraCulling;
	};
}

namespace PonyEngine::Render::Direct3D12
{
	PipelineState::PipelineState() noexcept :
		isTransparent{true},
		threadGroupCounts(),
		renderQueue{0},
		cameraCulling{true}
	{
	}

	PipelineState::PipelineState(const std::shared_ptr<class RootSignature>& rootSignature, ID3D12PipelineState& pipelineState, const bool isTransparent) noexcept :
		rootSignature(rootSignature),
		pipelineState(&pipelineState),
		isTransparent{isTransparent},
		threadGroupCounts(),
		renderQueue{0},
		cameraCulling{true}
	{
	}

	class RootSignature* PipelineState::RootSignature() noexcept
	{
		return rootSignature.get();
	}

	const class RootSignature* PipelineState::RootSignature() const noexcept
	{
		return rootSignature.get();
	}

	ID3D12PipelineState* PipelineState::State() noexcept
	{
		return pipelineState.Get();
	}

	const ID3D12PipelineState* PipelineState::State() const noexcept
	{
		return pipelineState.Get();
	}

	bool PipelineState::IsTransparent() const noexcept
	{
		return isTransparent;
	}

	struct ThreadGroupCounts& PipelineState::ThreadGroupCounts() noexcept
	{
		return threadGroupCounts;
	}

	const struct ThreadGroupCounts& PipelineState::ThreadGroupCounts() const noexcept
	{
		return threadGroupCounts;
	}

	std::int32_t& PipelineState::RenderQueue() noexcept
	{
		return renderQueue;
	}

	const std::int32_t& PipelineState::RenderQueue() const noexcept
	{
		return renderQueue;
	}

	bool& PipelineState::CameraCulling() noexcept
	{
		return cameraCulling;
	}

	const bool& PipelineState::CameraCulling() const noexcept
	{
		return cameraCulling;
	}

	void PipelineState::Name(const std::string_view name)
	{
		SetName(*pipelineState.Get(), name);
	}
}
