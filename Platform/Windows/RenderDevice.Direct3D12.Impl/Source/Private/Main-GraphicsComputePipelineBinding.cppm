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
	/// @brief Graphics and compute pipeline binding.
	class GraphicsComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsComputePipelineBinding() noexcept = default;
		GraphicsComputePipelineBinding(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding(GraphicsComputePipelineBinding&&) = delete;

		~GraphicsComputePipelineBinding() noexcept = default;

		/// @brief Resets binding.
		void Reset() noexcept;

		/// @brief Checks if a graphics pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasGraphicsPSO() const noexcept;
		/// @brief Checks if a compute pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasComputePSO() const noexcept;
		/// @brief Gets the currently bound graphics PSO.
		/// @return Graphics PSO.
		[[nodiscard("Pure function")]]
		const GraphicsPipelineState* GetGraphicsPSO() const noexcept;
		/// @brief Sets the graphics PSO.
		/// @param pso Graphics PSO to set.
		void SetGraphicsPSO(const GraphicsPipelineState* pso) noexcept;
		/// @brief Gets the currently bound compute PSO.
		/// @return PSO.
		[[nodiscard("Pure function")]]
		const ComputePipelineState* GetComputePSO() const noexcept;
		/// @brief Sets the compute PSO.
		/// @param pso Compute PSO to set.
		void SetComputePSO(const ComputePipelineState* pso) noexcept;

		/// @brief Checks if the last set pipeline state is graphics.
		/// @return @a True if it's graphics; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsLastPSOGraphics() const noexcept;
		/// @brief Checks if the last set pipeline state is compute.
		/// @return @a True if it's compute; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsLastPSOCompute() const noexcept;
		/// @brief Sets last PSO to graphics.
		void SetLastPSOGraphics() noexcept;
		/// @brief Sets last PSO to compute.
		void SetLastPSOCompute() noexcept;
		/// @brief Sets last PSO to none.
		void SetLastPSONone() noexcept;

		GraphicsComputePipelineBinding& operator =(const GraphicsComputePipelineBinding&) = delete;
		GraphicsComputePipelineBinding& operator =(GraphicsComputePipelineBinding&&) = delete;

	private:
		GraphicsPipelineBinding graphicsBinding; ///< Graphics pipeline binding helper.
		ComputePipelineBinding computeBinding; ///< Compute pipeline binding helper.
		std::optional<bool> isLastBindingGraphics; ///< @a True if the last bound PSO is graphics; @a false if the last bound PSO is compute; nullopt if no pso is bound.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	void GraphicsComputePipelineBinding::Reset() noexcept
	{
		graphicsBinding.Reset();
		computeBinding.Reset();
		isLastBindingGraphics = std::nullopt;
	}

	bool GraphicsComputePipelineBinding::HasGraphicsPSO() const noexcept
	{
		return graphicsBinding.HasPSO();
	}

	bool GraphicsComputePipelineBinding::HasComputePSO() const noexcept
	{
		return computeBinding.HasPSO();
	}

	const GraphicsPipelineState* GraphicsComputePipelineBinding::GetGraphicsPSO() const noexcept
	{
		return graphicsBinding.GetPSO();
	}

	void GraphicsComputePipelineBinding::SetGraphicsPSO(const GraphicsPipelineState* const pso) noexcept
	{
		graphicsBinding.SetPSO(pso);
	}

	const ComputePipelineState* GraphicsComputePipelineBinding::GetComputePSO() const noexcept
	{
		return computeBinding.GetPSO();
	}

	void GraphicsComputePipelineBinding::SetComputePSO(const ComputePipelineState* const pso) noexcept
	{
		computeBinding.SetPSO(pso);
	}

	bool GraphicsComputePipelineBinding::IsLastPSOGraphics() const noexcept
	{
		return isLastBindingGraphics == true;
	}

	bool GraphicsComputePipelineBinding::IsLastPSOCompute() const noexcept
	{
		return isLastBindingGraphics == false;
	}

	void GraphicsComputePipelineBinding::SetLastPSOGraphics() noexcept
	{
		isLastBindingGraphics = true;
	}

	void GraphicsComputePipelineBinding::SetLastPSOCompute() noexcept
	{
		isLastBindingGraphics = false;
	}

	void GraphicsComputePipelineBinding::SetLastPSONone() noexcept
	{
		isLastBindingGraphics = std::nullopt;
	}
}
