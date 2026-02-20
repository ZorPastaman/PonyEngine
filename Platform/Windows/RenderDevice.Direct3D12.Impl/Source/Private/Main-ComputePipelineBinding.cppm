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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputePipelineBinding;

import std;

import :CommandList;
import :ComputePipelineState;
import :RootSignature;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class ComputePipelineBinding final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComputePipelineBinding() noexcept;
		ComputePipelineBinding(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding(ComputePipelineBinding&&) = delete;

		~ComputePipelineBinding() noexcept = default;

		[[nodiscard("Pure function")]]
		bool HasPSO() const noexcept;
		void Reset() noexcept;

		void SetPipelineState(const IComputePipelineState& pipelineState, CommandList& commandList, bool forceUpdatePipeline = false);

		ComputePipelineBinding& operator =(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding& operator =(ComputePipelineBinding&&) = delete;

	private:
		static void ValidatePipelineState(const IComputePipelineState& pipelineState);

		const ComputePipelineState* lastComputePSO;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputePipelineBinding::ComputePipelineBinding() noexcept :
		lastComputePSO{nullptr}
	{
	}

	bool ComputePipelineBinding::HasPSO() const noexcept
	{
		return lastComputePSO;
	}

	void ComputePipelineBinding::Reset() noexcept
	{
		lastComputePSO = nullptr;
	}

	void ComputePipelineBinding::SetPipelineState(const IComputePipelineState& pipelineState, CommandList& commandList, const bool forceUpdatePipeline)
	{
		ValidatePipelineState(pipelineState);

		if (!forceUpdatePipeline && lastComputePSO == &pipelineState)
		{
			return;
		}

		const auto& pso = static_cast<const ComputePipelineState&>(pipelineState);
		if (!lastComputePSO || lastComputePSO->Layout() != pso.Layout())
		{
			ID3D12RootSignature* const rootSig = pso.Layout() ? &static_cast<const RootSignature&>(*pso.Layout()).GetRootSignature() : nullptr;
			commandList.SetComputeRootSignature(rootSig);
		}
		commandList.SetPipelineState(pso.PipelineState());

		lastComputePSO = &pso;
	}

	void ComputePipelineBinding::ValidatePipelineState(const IComputePipelineState& pipelineState)
	{
#ifndef NDEBUG
		if (typeid(pipelineState) != typeid(ComputePipelineState)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}
}
