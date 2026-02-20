/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsComputePipelineBinding;

import std;

import :ComputePipelineBinding;
import :GraphicsPipelineBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class GraphicsComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsComputePipelineBinding() noexcept = default;
		GraphicsComputePipelineBinding(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding(GraphicsComputePipelineBinding&&) = delete;

		~GraphicsComputePipelineBinding() noexcept = default;

		[[nodiscard("Pure function")]]
		bool HasGraphicsPSO() const noexcept;
		[[nodiscard("Pure function")]]
		bool HasComputePSO() const noexcept;
		[[nodiscard("Pure function")]]
		bool IsLastPSOGraphics() const noexcept;
		[[nodiscard("Pure function")]]
		bool IsLastPSOCompute() const noexcept;
		void Reset() noexcept;

		void SetPipelineState(const IGraphicsPipelineState& pipelineState, CommandList& commandList);
		void SetPipelineState(const IComputePipelineState& pipelineState, CommandList& commandList);

		GraphicsComputePipelineBinding& operator =(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding& operator =(GraphicsComputePipelineBinding&&) = delete;

	private:
		GraphicsPipelineBinding graphicsBinding;
		ComputePipelineBinding computeBinding;
		std::optional<bool> isLastBindingGraphics;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	bool GraphicsComputePipelineBinding::HasGraphicsPSO() const noexcept
	{
		return graphicsBinding.HasPSO();
	}

	bool GraphicsComputePipelineBinding::HasComputePSO() const noexcept
	{
		return computeBinding.HasPSO();
	}

	bool GraphicsComputePipelineBinding::IsLastPSOGraphics() const noexcept
	{
		return isLastBindingGraphics == true;
	}

	bool GraphicsComputePipelineBinding::IsLastPSOCompute() const noexcept
	{
		return isLastBindingGraphics == false;
	}

	void GraphicsComputePipelineBinding::Reset() noexcept
	{
		graphicsBinding.Reset();
		computeBinding.Reset();
		isLastBindingGraphics = std::nullopt;
	}

	void GraphicsComputePipelineBinding::SetPipelineState(const IGraphicsPipelineState& pipelineState, CommandList& commandList)
	{
		graphicsBinding.SetPipelineState(pipelineState, commandList, !IsLastPSOGraphics());
		isLastBindingGraphics = true;
	}

	void GraphicsComputePipelineBinding::SetPipelineState(const IComputePipelineState& pipelineState, CommandList& commandList)
	{
		computeBinding.SetPipelineState(pipelineState, commandList, !IsLastPSOCompute());
		isLastBindingGraphics = false;
	}
}
