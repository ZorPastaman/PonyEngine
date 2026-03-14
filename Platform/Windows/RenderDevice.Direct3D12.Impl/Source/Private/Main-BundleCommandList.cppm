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

import PonyEngine.Math;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;
import :ContainerBinding;
import :DescriptorHeapUtility;
import :GraphicsComputePipelineBinding;
import :PipelineStateUtility;
import :SamplerContainer;
import :ShaderDataContainer;

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

		virtual void SetDepthBias(const DepthBias& bias) override;
		virtual void SetDepthBounds(const DepthRange& range) override;
		virtual void SetStencilReference(const StencilReference& reference) override;
		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) override;

		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) override;
		virtual void BindPipelineState(const IGraphicsPipelineState& pipelineState) override;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) override;
		virtual void BindGraphics(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) override;
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) override;

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
		void ValidatePipelineStateForGraphics() const;
		void ValidatePipelineStateForCompute() const;
		void ValidateGraphicsBindings(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) const;
		void ValidateComputeBindings(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) const;
		void ValidateBindings(const RootSignature* rootSig, std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) const;

		class CommandList commandList;
		GraphicsComputePipelineBinding pipelineBinding;
		ContainerBinding containerBinding;
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
		containerBinding.Reset();
	}

	void BundleCommandList::Close()
	{
		commandList.Close();
	}

	bool BundleCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
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

	void BundleCommandList::BindContainers(const IShaderDataContainer* const shaderDataContainer, const ISamplerContainer* const samplerContainer)
	{
		commandList.ValidateState();
		containerBinding.SetContainers(ToNativeContainer(shaderDataContainer), ToNativeContainer(samplerContainer), commandList);
	}

	void BundleCommandList::BindPipelineState(const IGraphicsPipelineState& pipelineState)
	{
		commandList.ValidateState();
		pipelineBinding.BindPipelineState(ToNativePipelineState(pipelineState), commandList);
	}

	void BundleCommandList::BindPipelineState(const IComputePipelineState& pipelineState)
	{
		commandList.ValidateState();
		pipelineBinding.BindPipelineState(ToNativePipelineState(pipelineState), commandList);
	}

	void BundleCommandList::BindGraphics(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.ValidateState();
		ValidateGraphicsBindings(shaderDataBindings, samplerBindings);

		containerBinding.BindGraphicsShaderData(shaderDataBindings, commandList);
		containerBinding.BindGraphicsSampler(samplerBindings, commandList);
	}

	void BundleCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.ValidateState();
		ValidateComputeBindings(shaderDataBindings, samplerBindings);

		containerBinding.BindComputeShaderData(shaderDataBindings, commandList);
		containerBinding.BindComputeSampler(samplerBindings, commandList);
	}

	void BundleCommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.ValidateState();
		ValidatePipelineStateForGraphics();

		pipelineBinding.SetGraphicsPipelineState(commandList);
		commandList.DispatchGraphics(threadGroupCounts);
	}

	void BundleCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.ValidateState();
		ValidatePipelineStateForCompute();

		pipelineBinding.SetComputePipelineState(commandList);
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

	void BundleCommandList::ValidatePipelineStateForGraphics() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.HasGraphicsPSO())
		{
			throw std::logic_error("No graphics pipeline state bound");
		}
#endif
	}

	void BundleCommandList::ValidatePipelineStateForCompute() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.HasComputePSO())
		{
			throw std::logic_error("Nn compute pipeline state bound");
		}
#endif
	}

	void BundleCommandList::ValidateGraphicsBindings(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings) const
	{
#ifndef NDEBUG
		ValidateBindings(pipelineBinding.GraphicsRootSignature(), shaderDataBindings, samplerBindings);
#endif
	}

	void BundleCommandList::ValidateComputeBindings(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings) const
	{
#ifndef NDEBUG
		ValidateBindings(pipelineBinding.ComputeRootSignature(), shaderDataBindings, samplerBindings);
#endif
	}

	void BundleCommandList::ValidateBindings(const RootSignature* const rootSig,
		const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings) const
	{
#ifndef NDEBUG
		if (!rootSig) [[unlikely]]
		{
			throw std::logic_error("Empty pipeline layout");
		}

		for (const ShaderDataBinding& binding : shaderDataBindings)
		{
			containerBinding.ValidateShaderData(*rootSig, binding.layoutSetIndex, binding.containerIndex);
		}

		for (const SamplerBinding& binding : samplerBindings)
		{
			containerBinding.ValidateSamplerData(*rootSig, binding.layoutSetIndex, binding.containerIndex);
		}
#endif
	}
}
