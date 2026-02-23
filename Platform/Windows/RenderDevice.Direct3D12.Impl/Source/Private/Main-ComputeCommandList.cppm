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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:ComputeCommandList;

import std;

import PonyEngine.Math;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;
import :ComputePipelineBinding;
import :ContainerBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class ComputeCommandList final : public IComputeCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		ComputeCommandList(const ComputeCommandList&) = delete;
		ComputeCommandList(ComputeCommandList&&) = delete;

		~ComputeCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]] 
		virtual bool IsOpen() const noexcept override;

		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) override;

		virtual void BindContainers(const IShaderDataContainer* shaderDataContainer, const ISamplerContainer* samplerContainer) override;
		virtual void BindPipelineState(const IComputePipelineState& pipelineState) override;
		virtual void BindCompute(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) override;

		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;

		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;

		virtual void Copy(const IBuffer& source, IBuffer& destination) override;
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size) override;
		virtual void Copy(const ITexture& source, ITexture& destination) override;
		virtual void Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range) override;
		virtual void Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		ComputeCommandList& operator =(const ComputeCommandList&) = delete;
		ComputeCommandList& operator =(ComputeCommandList&&) = delete;

	private:
		void ValidatePipelineStateForCompute() const;
		void ValidateComputeBindings(std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) const;
		void ValidateBindings(const RootSignature* rootSig, std::span<const ShaderDataBinding> shaderDataBindings, std::span<const SamplerBinding> samplerBindings) const;

		class CommandList commandList;
		ComputePipelineBinding pipelineBinding;
		ContainerBinding containerBinding;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputeCommandList::ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList)
	{
	}

	ComputeCommandList::ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void ComputeCommandList::Reset()
	{
		commandList.Reset();
		pipelineBinding.Reset();
		containerBinding.Reset();
	}

	void ComputeCommandList::Close()
	{
		commandList.Close();
	}

	bool ComputeCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void ComputeCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		commandList.Barrier(bufferBarriers, textureBarriers);
	}

	void ComputeCommandList::BindContainers(const IShaderDataContainer* const shaderDataContainer, const ISamplerContainer* const samplerContainer)
	{
		commandList.ValidateContainers(shaderDataContainer, samplerContainer);
		containerBinding.SetContainers(static_cast<const ShaderDataContainer*>(shaderDataContainer), static_cast<const SamplerContainer*>(samplerContainer), commandList);
	}

	void ComputeCommandList::BindPipelineState(const IComputePipelineState& pipelineState)
	{
		commandList.ValidatePipelineState(pipelineState);

		pipelineBinding.BindPipelineState(static_cast<const ComputePipelineState&>(pipelineState), commandList);
		pipelineBinding.SetPipelineState(commandList);
	}

	void ComputeCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.ValidateState();
		ValidateComputeBindings(shaderDataBindings, samplerBindings);

		containerBinding.BindComputeShaderData(shaderDataBindings, commandList);
		containerBinding.BindComputeSampler(samplerBindings, commandList);
	}

	void ComputeCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.ValidateState();
		ValidatePipelineStateForCompute();

		commandList.DispatchCompute(threadGroupCounts);
	}

	void ComputeCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
#ifndef NDEBUG
		if (!containerBinding.HasShaderDataContainer()) [[unlikely]]
		{
			throw std::logic_error("No shader data container bound");
		}
#endif

		commandList.ClearUAV(buffer, *containerBinding.GetShaderDataContainer(), gpuViewIndex, cpuContainer, cpuViewIndex, values, rects);
	}

	void ComputeCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
#ifndef NDEBUG
		if (!containerBinding.HasShaderDataContainer()) [[unlikely]]
		{
			throw std::logic_error("No shader data container bound");
		}
#endif

		commandList.ClearUAV(texture, *containerBinding.GetShaderDataContainer(), gpuViewIndex, cpuContainer, cpuViewIndex, values, rects);
	}

	void ComputeCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
#ifndef NDEBUG
		if (!containerBinding.HasShaderDataContainer()) [[unlikely]]
		{
			throw std::logic_error("No shader data container bound");
		}
#endif

		commandList.ClearUAV(buffer, *containerBinding.GetShaderDataContainer(), gpuViewIndex, cpuContainer, cpuViewIndex, values, rects);
	}

	void ComputeCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
#ifndef NDEBUG
		if (!containerBinding.HasShaderDataContainer()) [[unlikely]]
		{
			throw std::logic_error("No shader data container bound");
		}
#endif

		commandList.ClearUAV(texture, *containerBinding.GetShaderDataContainer(), gpuViewIndex, cpuContainer, cpuViewIndex, values, rects);
	}

	void ComputeCommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		commandList.Copy(source, destination);
	}

	void ComputeCommandList::Copy(const IBuffer& source, IBuffer& destination, const std::uint64_t sourceOffset, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		commandList.Copy(source, destination, sourceOffset, destinationOffset, size);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination)
	{
		commandList.Copy(source, destination);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void ComputeCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void ComputeCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void ComputeCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void ComputeCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void ComputeCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void ComputeCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	std::string_view ComputeCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void ComputeCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& ComputeCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}

	void ComputeCommandList::ValidatePipelineStateForCompute() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.HasPSO())
		{
			throw std::logic_error("No compute pipeline state bound");
		}
#endif
	}

	void ComputeCommandList::ValidateComputeBindings(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings) const
	{
#ifndef NDEBUG
		ValidateBindings(pipelineBinding.GetRootSignature(), shaderDataBindings, samplerBindings);
#endif
	}

	void ComputeCommandList::ValidateBindings(const RootSignature* const rootSig, 
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
