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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsPipelineBinding;

import std;

import PonyEngine.RenderDevice;

import :CommandList;
import :GraphicsPipelineState;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Graphics pipeline binding helper.
	class GraphicsPipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsPipelineBinding() noexcept;
		GraphicsPipelineBinding(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding(GraphicsPipelineBinding&&) = delete;

		~GraphicsPipelineBinding() noexcept = default;

		/// @brief Checks if a graphics pipeline state is bound.
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
		void BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList);
		/// @brief Sets a current pipeline state to the command list.
		/// @param commandList Target command list.
		/// @note Must have a valid pso.
		void SetPipelineState(CommandList& commandList) const;

		GraphicsPipelineBinding& operator =(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding& operator =(GraphicsPipelineBinding&&) = delete;

	private:
		const GraphicsPipelineState* boundPSO; ///< Bound pso.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsPipelineBinding::GraphicsPipelineBinding() noexcept :
		boundPSO{nullptr}
	{
	}

	bool GraphicsPipelineBinding::HasPSO() const noexcept
	{
		return boundPSO;
	}

	const RootSignature* GraphicsPipelineBinding::GetRootSignature() const noexcept
	{
		return boundPSO ? static_cast<const RootSignature*>(boundPSO->Layout().get()) : nullptr;
	}

	void GraphicsPipelineBinding::Reset() noexcept
	{
		boundPSO = nullptr;
	}

	void GraphicsPipelineBinding::BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList)
	{
		if (!boundPSO || boundPSO->Layout() != pipelineState.Layout())
		{
			ID3D12RootSignature* const rootSig = pipelineState.Layout() ? &static_cast<const RootSignature&>(*pipelineState.Layout()).GetRootSignature() : nullptr;
			commandList.SetGraphicsRootSignature(rootSig);
		}

		boundPSO = &pipelineState;
	}

	void GraphicsPipelineBinding::SetPipelineState(CommandList& commandList) const
	{
		assert(boundPSO && "No pso is bound.");
		commandList.SetPipelineState(boundPSO->PipelineState());
	}
}
