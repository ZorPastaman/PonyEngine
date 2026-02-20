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
		void Reset() noexcept;

		void SetPipelineState(const IGraphicsPipelineState& pipelineState, CommandList& commandList, bool forceUpdatePipeline = false);

		GraphicsPipelineBinding& operator =(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding& operator =(GraphicsPipelineBinding&&) = delete;

	private:
		static void ValidatePipelineState(const IGraphicsPipelineState& pipelineState);

		const GraphicsPipelineState* lastGraphicsPSO;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsPipelineBinding::GraphicsPipelineBinding() noexcept :
		lastGraphicsPSO{nullptr}
	{
	}

	bool GraphicsPipelineBinding::HasPSO() const noexcept
	{
		return lastGraphicsPSO;
	}

	void GraphicsPipelineBinding::Reset() noexcept
	{
		lastGraphicsPSO = nullptr;
	}

	void GraphicsPipelineBinding::SetPipelineState(const IGraphicsPipelineState& pipelineState, CommandList& commandList, const bool forceUpdatePipeline)
	{
		ValidatePipelineState(pipelineState);

		if (!forceUpdatePipeline && lastGraphicsPSO == &pipelineState)
		{
			return;
		}

		const auto& pso = static_cast<const GraphicsPipelineState&>(pipelineState);
		if (!lastGraphicsPSO || lastGraphicsPSO->Layout() != pso.Layout())
		{
			ID3D12RootSignature* const rootSig = pso.Layout() ? &static_cast<const RootSignature&>(*pso.Layout()).GetRootSignature() : nullptr;
			commandList.SetGraphicsRootSignature(rootSig);
		}
		commandList.SetPipelineState(pso.PipelineState());

		lastGraphicsPSO = &pso;
	}

	void GraphicsPipelineBinding::ValidatePipelineState(const IGraphicsPipelineState& pipelineState)
	{
#ifndef NDEBUG
		if (typeid(pipelineState) != typeid(GraphicsPipelineState)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}
}
