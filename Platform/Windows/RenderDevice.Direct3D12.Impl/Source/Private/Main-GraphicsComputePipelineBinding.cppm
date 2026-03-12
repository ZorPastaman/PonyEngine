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

import :CommandList;
import :ComputePipelineBinding;
import :GraphicsPipelineBinding;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Graphics and compute pipeline binding helper.
	class GraphicsComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsComputePipelineBinding() noexcept = default;
		GraphicsComputePipelineBinding(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding(GraphicsComputePipelineBinding&&) = delete;

		~GraphicsComputePipelineBinding() noexcept = default;

		/// @brief Checks if a graphics pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasGraphicsPSO() const noexcept;
		/// @brief Checks if a compute pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasComputePSO() const noexcept;
		/// @brief Checks if the last set pipeline state is graphics.
		/// @return @a True if it's graphics; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsLastPSOGraphics() const noexcept;
		/// @brief Checks if the last set pipeline state is compute.
		/// @return @a True if it's compute; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsLastPSOCompute() const noexcept;
		/// @brief Gets a root signature of a currently bound graphics pipeline state.
		/// @return Root signature or nullptr if there's no graphics pso bound or it doesn't have a root signature.
		[[nodiscard("Pure function")]]
		const RootSignature* GraphicsRootSignature() const noexcept;
		/// @brief Gets a root signature of a currently bound compute pipeline state.
		/// @return Root signature or nullptr if there's no compute pso bound or it doesn't have a root signature.
		[[nodiscard("Pure function")]]
		const RootSignature* ComputeRootSignature() const noexcept;
		/// @brief Resets binding.
		void Reset() noexcept;

		/// @brief Binds the root signature of the @p pipeline state and binds it to the helper.
		/// @param pipelineState Pipeline state to bind.
		/// @param commandList Target command list.
		/// @remark Call the @p SetPipelineState() to set a pipeline state to the command list.
		void BindPipelineState(const GraphicsPipelineState& pipelineState, CommandList& commandList);
		/// @brief Binds the root signature of the @p pipeline state and binds it to the helper.
		/// @param pipelineState Pipeline state to bind.
		/// @param commandList Target command list.
		/// @remark Call the @p SetPipelineState() to set a pipeline state to the command list.
		void BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList);

		/// @brief Sets a current graphics pipeline state to the command list.
		/// @param commandList Target command list.
		/// @note Must have a valid graphics pso.
		void SetGraphicsPipelineState(CommandList& commandList);
		/// @brief Sets a current compute pipeline state to the command list.
		/// @param commandList Target command list.
		/// @note Must have a valid compute pso.
		void SetComputePipelineState(CommandList& commandList);

		GraphicsComputePipelineBinding& operator =(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding& operator =(GraphicsComputePipelineBinding&&) = delete;

	private:
		GraphicsPipelineBinding graphicsBinding; ///< Graphics pipeline binding helper.
		ComputePipelineBinding computeBinding; ///< Compute pipeline binding helper.
		std::optional<bool> isLastBindingGraphics; ///< @a True if the last bound pso is graphics; @a false if the last bound pso is compute; nullopt if no pso is bound.
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
		return graphicsBinding.GetRootSignature();
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
		if (IsLastPSOGraphics())
		{
			return;
		}

		graphicsBinding.SetPipelineState(commandList);
		isLastBindingGraphics = true;
	}

	void GraphicsComputePipelineBinding::SetComputePipelineState(CommandList& commandList)
	{
		if (IsLastPSOCompute())
		{
			return;
		}

		computeBinding.SetPipelineState(commandList);
		isLastBindingGraphics = false;
	}
}
