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

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputePipelineBinding;

import std;

import PonyEngine.RenderDevice;

import :CommandList;
import :ComputePipelineState;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Compute pipeline binding helper.
	class ComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComputePipelineBinding() noexcept;
		ComputePipelineBinding(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding(ComputePipelineBinding&&) = delete;

		~ComputePipelineBinding() noexcept = default;

		/// @brief Checks if a compute pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasPSO() const noexcept;
		/// @brief Gets a root signature of a currently bound pipeline state.
		/// @return Root signature or nullptr if there's no pso bound or it doesn't have a root signature.
		[[nodiscard("Pure function")]]
		const RootSignature* GetRootSignature() const noexcept;
		/// @brief Resets binding.
		void Reset() noexcept;

		/// @brief Binds the root signature of the @p pipeline state and binds it to the helper.
		/// @param pipelineState Pipeline state to bind.
		/// @param commandList Target command list.
		/// @remark Call the @p SetPipelineState() to set a pipeline state to the command list.
		void BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList);
		/// @brief Sets a current pipeline state to the command list.
		/// @param commandList Target command list.
		/// @note Must have a valid pso.
		void SetPipelineState(CommandList& commandList) const;

		ComputePipelineBinding& operator =(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding& operator =(ComputePipelineBinding&&) = delete;

	private:
		const ComputePipelineState* boundPSO; ///< Bound pso.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputePipelineBinding::ComputePipelineBinding() noexcept :
		boundPSO{nullptr}
	{
	}

	bool ComputePipelineBinding::HasPSO() const noexcept
	{
		return boundPSO;
	}

	const RootSignature* ComputePipelineBinding::GetRootSignature() const noexcept
	{
		return boundPSO ? static_cast<const RootSignature*>(boundPSO->Layout().get()) : nullptr;
	}

	void ComputePipelineBinding::Reset() noexcept
	{
		boundPSO = nullptr;
	}

	void ComputePipelineBinding::BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList)
	{
		if (!boundPSO || boundPSO->Layout() != pipelineState.Layout())
		{
			ID3D12RootSignature* const rootSig = pipelineState.Layout() ? &static_cast<const RootSignature&>(*pipelineState.Layout()).GetRootSignature() : nullptr;
			commandList.SetComputeRootSignature(rootSig);
		}

		boundPSO = &pipelineState;
	}

	void ComputePipelineBinding::SetPipelineState(CommandList& commandList) const
	{
		assert(boundPSO && "No pso is bound.");
		commandList.SetPipelineState(boundPSO->PipelineState());
	}
}
