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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputePipelineState;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :PipelineState;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Compute pipeline state wrapper.
	class ComputePipelineState final : public IComputePipelineState
	{
	public:
		/// @brief Creates a compute pipeline state wrapper.
		/// @param pipelineState Pipeline state.
		/// @param layout Pipeline layout.
		[[nodiscard("Pure constructor")]]
		ComputePipelineState(ID3D12PipelineState& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout) noexcept;
		/// @brief Creates a compute pipeline state wrapper.
		/// @param pipelineState Pipeline state.
		/// @param layout Pipeline layout.
		[[nodiscard("Pure constructor")]]
		ComputePipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout) noexcept;
		ComputePipelineState(const ComputePipelineState&) = delete;
		ComputePipelineState(ComputePipelineState&&) = delete;

		~ComputePipelineState() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineLayout>& Layout() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the pipeline state.
		/// @return Pipeline state.
		[[nodiscard("Pure function")]]
		ID3D12PipelineState& PipelineState() const noexcept;
		/// @brief Gets the root signature.
		/// @return Root signature.
		[[nodiscard("Pure function")]]
		const RootSignature* RootSignature() const noexcept;

		ComputePipelineState& operator =(const ComputePipelineState&) = delete;
		ComputePipelineState& operator =(ComputePipelineState&&) = delete;

	private:
		class PipelineState pipelineState; ///< Pipeline state.
		std::shared_ptr<const IPipelineLayout> layout; ///< Pipeline layout.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputePipelineState::ComputePipelineState(ID3D12PipelineState& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout) noexcept :
		pipelineState(pipelineState),
		layout(layout)
	{
	}

	ComputePipelineState::ComputePipelineState(Platform::Windows::ComPtr<ID3D12PipelineState>&& pipelineState, const std::shared_ptr<const IPipelineLayout>& layout) noexcept :
		pipelineState(std::move(pipelineState)),
		layout(layout)
	{
	}

	const std::shared_ptr<const IPipelineLayout>& ComputePipelineState::Layout() const noexcept
	{
		return layout;
	}

	std::string_view ComputePipelineState::Name() const noexcept
	{
		return pipelineState.Name();
	}

	void ComputePipelineState::Name(const std::string_view name)
	{
		pipelineState.Name(name);
	}

	ID3D12PipelineState& ComputePipelineState::PipelineState() const noexcept
	{
		return pipelineState.GetPipelineState();
	}

	const RootSignature* ComputePipelineState::RootSignature() const noexcept
	{
		return layout ? static_cast<const class RootSignature*>(layout.get()) : nullptr;
	}
}
