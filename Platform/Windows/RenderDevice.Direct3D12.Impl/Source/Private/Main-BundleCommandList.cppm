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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BundleCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;
import :GraphicsComputePipelineBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class BundleCommandList final : public ISecondaryGraphicsCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		BundleCommandList(const BundleCommandList&) = delete;
		BundleCommandList(BundleCommandList&&) = delete;

		~BundleCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]] 
		virtual bool IsOpen() const noexcept override;

		virtual void SetPipelineState(const IGraphicsPipelineState& pipelineState) override;
		virtual void SetPipelineState(const IComputePipelineState& pipelineState) override;

		virtual void SetDepthBias(const DepthBias& bias) override;
		virtual void SetDepthBounds(const DepthRange& range) override;
		virtual void SetStencilReference(const StencilReference& reference) override;

		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) override;

		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		BundleCommandList& operator =(const BundleCommandList&) = delete;
		BundleCommandList& operator =(BundleCommandList&&) = delete;

	private:
		void ValidateState() const;

		void ValidatePipelineStateForGraphics() const;
		void ValidatePipelineStateForCompute() const;

		class CommandList commandList;
		GraphicsComputePipelineBinding pipelineBinding;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	BundleCommandList::BundleCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList)
	{
	}

	BundleCommandList::BundleCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void BundleCommandList::Reset()
	{
		commandList.Reset();
		pipelineBinding.Reset();
	}

	void BundleCommandList::Close()
	{
		commandList.Close();
	}

	bool BundleCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void BundleCommandList::SetPipelineState(const IGraphicsPipelineState& pipelineState)
	{
		ValidateState();
		pipelineBinding.SetPipelineState(pipelineState, commandList);
	}

	void BundleCommandList::SetPipelineState(const IComputePipelineState& pipelineState)
	{
		ValidateState();
		pipelineBinding.SetPipelineState(pipelineState, commandList);
	}

	void BundleCommandList::SetDepthBias(const DepthBias& bias)
	{
		commandList.SetDepthBias(bias);
	}

	void BundleCommandList::SetDepthBounds(const DepthRange& range)
	{
		commandList.SetDepthBounds(range);
	}

	void BundleCommandList::SetStencilReference(const StencilReference& reference)
	{
		commandList.SetStencilReference(reference);
	}

	void BundleCommandList::SetBlendFactor(const Math::ColorRGBA<float>& factor)
	{
		commandList.SetBlendFactor(factor);
	}

	void BundleCommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchGraphics(threadGroupCounts);
	}

	void BundleCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchCompute(threadGroupCounts);
	}

	std::string_view BundleCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void BundleCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& BundleCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}

	void BundleCommandList::ValidateState() const
	{
#ifndef NDEBUG
		if (!commandList.IsOpen())
		{
			throw std::logic_error("Command list is closed");
		}
#endif
	}

	void BundleCommandList::ValidatePipelineStateForGraphics() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.IsLastPSOGraphics())
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}

	void BundleCommandList::ValidatePipelineStateForCompute() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.IsLastPSOCompute())
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}
}
