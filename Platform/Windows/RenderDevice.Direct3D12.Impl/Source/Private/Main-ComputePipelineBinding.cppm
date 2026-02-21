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

import PonyEngine.RenderDevice;

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
		[[nodiscard("Pure function")]]
		const RootSignature* GetRootSignature() const noexcept;
		void Reset() noexcept;

		void BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList);
		void SetPipelineState(CommandList& commandList);

		ComputePipelineBinding& operator =(const ComputePipelineBinding&) = delete;
		ComputePipelineBinding& operator =(ComputePipelineBinding&&) = delete;

	private:
		const ComputePipelineState* boundPSO;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputePipelineBinding::ComputePipelineBinding() noexcept :
		boundPSO{nullptr}
	{
	}

	bool ComputePipelineBinding::HasPSO() const noexcept
	{
		return boundPSO;
	}

	const RootSignature* ComputePipelineBinding::GetRootSignature() const noexcept
	{
		return boundPSO ? static_cast<const RootSignature*>(boundPSO->Layout().get()) : nullptr;
	}

	void ComputePipelineBinding::Reset() noexcept
	{
		boundPSO = nullptr;
	}

	void ComputePipelineBinding::BindPipelineState(const ComputePipelineState& pipelineState, CommandList& commandList)
	{
		if (!boundPSO || boundPSO->Layout() != pipelineState.Layout())
		{
			ID3D12RootSignature* const rootSig = pipelineState.Layout() ? &static_cast<const RootSignature&>(*pipelineState.Layout()).GetRootSignature() : nullptr;
			commandList.SetComputeRootSignature(rootSig);
		}

		boundPSO = &pipelineState;
	}

	void ComputePipelineBinding::SetPipelineState(CommandList& commandList)
	{
		commandList.SetPipelineState(boundPSO->PipelineState());
	}
}
