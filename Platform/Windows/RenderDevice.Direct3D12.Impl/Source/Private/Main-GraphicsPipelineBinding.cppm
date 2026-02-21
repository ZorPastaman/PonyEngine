/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsPipelineBinding;

import std;

import PonyEngine.RenderDevice;

import :CommandList;
import :GraphicsPipelineState;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class GraphicsPipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsPipelineBinding() noexcept;
		GraphicsPipelineBinding(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding(GraphicsPipelineBinding&&) = delete;

		~GraphicsPipelineBinding() noexcept = default;

		[[nodiscard("Pure function")]]
		bool HasPSO() const noexcept;
		[[nodiscard("Pure function")]]
		const RootSignature* BoundRootSignature() const noexcept;
		void Reset() noexcept;

		void BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList);
		void SetPipelineState(CommandList& commandList);

		GraphicsPipelineBinding& operator =(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding& operator =(GraphicsPipelineBinding&&) = delete;

	private:
		const GraphicsPipelineState* boundPSO;
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

	const RootSignature* GraphicsPipelineBinding::BoundRootSignature() const noexcept
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

	void GraphicsPipelineBinding::SetPipelineState(CommandList& commandList)
	{
		commandList.SetPipelineState(boundPSO->PipelineState());
	}
}
