/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsPipelineBinding;

import :GraphicsPipelineState;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Graphics pipeline binding.
	class GraphicsPipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsPipelineBinding() noexcept;
		GraphicsPipelineBinding(const GraphicsPipelineBinding&) = delete;
		GraphicsPipelineBinding(GraphicsPipelineBinding&&) = delete;

		~GraphicsPipelineBinding() noexcept = default;

		/// @brief Resets binding.
		void Reset() noexcept;

		/// @brief Checks if a graphics pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasPSO() const noexcept;
		/// @brief Gets the currently bound PSO.
		/// @return PSO.
		[[nodiscard("Pure function")]]
		const GraphicsPipelineState* GetPSO() const noexcept;
		/// @brief Sets the PSO.
		/// @param pso PSO to set.
		void SetPSO(const GraphicsPipelineState* pso) noexcept;

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

	void GraphicsPipelineBinding::Reset() noexcept
	{
		boundPSO = nullptr;
	}

	bool GraphicsPipelineBinding::HasPSO() const noexcept
	{
		return boundPSO;
	}

	const GraphicsPipelineState* GraphicsPipelineBinding::GetPSO() const noexcept
	{
		return boundPSO;
	}

	void GraphicsPipelineBinding::SetPSO(const GraphicsPipelineState* const pso) noexcept
	{
		boundPSO = pso;
	}
}
