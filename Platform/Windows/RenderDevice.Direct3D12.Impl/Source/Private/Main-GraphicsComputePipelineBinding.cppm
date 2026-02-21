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

import PonyEngine.RenderDevice;

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
		[[nodiscard("Pure function")]]
		const RootSignature* GraphicsRootSignature() const noexcept;
		[[nodiscard("Pure function")]]
		const RootSignature* ComputeRootSignature() const noexcept;
		void Reset() noexcept;

		void BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList);
		void BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList);

		void SetGraphicsPipelineState(CommandList& commandList);
		void SetComputePipelineState(CommandList& commandList);

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

	const RootSignature* GraphicsComputePipelineBinding::GraphicsRootSignature() const noexcept
	{
		return graphicsBinding.BoundRootSignature();
	}

	const RootSignature* GraphicsComputePipelineBinding::ComputeRootSignature() const noexcept
	{
		return computeBinding.GetRootSignature();
	}

	void GraphicsComputePipelineBinding::Reset() noexcept
	{
		graphicsBinding.Reset();
		computeBinding.Reset();
		isLastBindingGraphics = std::nullopt;
	}

	void GraphicsComputePipelineBinding::BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList)
	{
		graphicsBinding.BindPipelineState(pipelineState, commandList);

		if (IsLastPSOGraphics())
		{
			isLastBindingGraphics = std::nullopt;
		}
	}

	void GraphicsComputePipelineBinding::BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList)
	{
		computeBinding.BindPipelineState(pipelineState, commandList);

		if (IsLastPSOCompute())
		{
			isLastBindingGraphics = std::nullopt;
		}
	}

	void GraphicsComputePipelineBinding::SetGraphicsPipelineState(CommandList& commandList)
	{
		if (IsLastPSOGraphics()) [[likely]]
		{
			return;
		}

		graphicsBinding.SetPipelineState(commandList);
		isLastBindingGraphics = true;
	}

	void GraphicsComputePipelineBinding::SetComputePipelineState(CommandList& commandList)
	{
		if (IsLastPSOCompute()) [[likely]]
		{
			return;
		}

		computeBinding.SetPipelineState(commandList);
		isLastBindingGraphics = false;
	}
}
