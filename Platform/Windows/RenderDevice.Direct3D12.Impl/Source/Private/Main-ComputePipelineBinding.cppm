/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputePipelineBinding;

import :ComputePipelineState;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Compute pipeline binding.
	class ComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComputePipelineBinding() noexcept;
		ComputePipelineBinding(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding(ComputePipelineBinding&&) = delete;

		~ComputePipelineBinding() noexcept = default;

		/// @brief Resets binding.
		void Reset() noexcept;

		/// @brief Checks if a compute pipeline state is bound.
		/// @return @a True if its bound; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasPSO() const noexcept;
		/// @brief Gets the currently bound PSO.
		/// @return PSO.
		[[nodiscard("Pure function")]]
		const ComputePipelineState* GetPSO() const noexcept;
		/// @brief Sets the PSO.
		/// @param pso PSO to set.
		void SetPSO(const ComputePipelineState* pso) noexcept;

		ComputePipelineBinding& operator =(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding& operator =(ComputePipelineBinding&&) = delete;

	private:
		const ComputePipelineState* boundPSO; ///< Bound PSO.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputePipelineBinding::ComputePipelineBinding() noexcept :
		boundPSO{nullptr}
	{
	}

	void ComputePipelineBinding::Reset() noexcept
	{
		boundPSO = nullptr;
	}

	bool ComputePipelineBinding::HasPSO() const noexcept
	{
		return boundPSO;
	}

	const ComputePipelineState* ComputePipelineBinding::GetPSO() const noexcept
	{
		return boundPSO;
	}

	void ComputePipelineBinding::SetPSO(const ComputePipelineState* const pso) noexcept
	{
		boundPSO = pso;
	}
}
