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
import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;
import :ComputePipelineBinding;
import :ContainerBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Compute command list wrapper.
	class ComputeCommandList final : public IComputeCommandList
	{
	public:
		/// @brief Creates a compute command list wrapper.
		/// @param allocator Compute command allocator.
		/// @param commandList Compute command list.
		[[nodiscard("Pure constructor")]]
		ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		/// @brief Creates a compute command list wrapper.
		/// @param allocator Compute command allocator.
		/// @param commandList Compute command list.
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
			const Math::Vector4<std::uint32_t>& values) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<std::uint32_t>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;
		virtual void ClearUAV(const IBuffer& buffer, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values) override;
		virtual void ClearUAV(const ITexture& texture, std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, std::uint32_t cpuViewIndex,
			const Math::Vector4<float>& values, std::span<const Math::CornerRect<std::uint32_t>> rects) override;

		virtual void Copy(const IBuffer& source, IBuffer& destination) override;
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges) override;
		virtual void Copy(const ITexture& source, ITexture& destination) override;
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures) override;
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) override;
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the command list.
		/// @return Command list.
		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		ComputeCommandList& operator =(const ComputeCommandList&) = delete;
		ComputeCommandList& operator =(ComputeCommandList&&) = delete;

	private:
		class CommandList commandList; ///< Command list.
		ComputePipelineBinding pipelineBinding; ///< Pipeline binding.
		ContainerBinding containerBinding; ///< Container binding.
		Memory::Arena arena; ///< Arena.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	ComputeCommandList::ComputeCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList),
		arena(0uz, 128uz)
	{
	}

	ComputeCommandList::ComputeCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList)),
		arena(0uz, 128uz)
	{
	}

	void ComputeCommandList::Reset()
	{
		commandList.Reset(containerBinding, pipelineBinding);
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
		commandList.Barrier(bufferBarriers, textureBarriers, arena);
	}

	void ComputeCommandList::BindContainers(const IShaderDataContainer* const shaderDataContainer, const ISamplerContainer* const samplerContainer)
	{
		commandList.SetContainers(shaderDataContainer, samplerContainer, containerBinding);
	}

	void ComputeCommandList::BindPipelineState(const IComputePipelineState& pipelineState)
	{
		commandList.SetPipelineState(pipelineState, pipelineBinding);
	}

	void ComputeCommandList::BindCompute(const std::span<const ShaderDataBinding> shaderDataBindings, const std::span<const SamplerBinding> samplerBindings)
	{
		commandList.SetComputeBindings(shaderDataBindings, samplerBindings, containerBinding, pipelineBinding);
	}

	void ComputeCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		commandList.DispatchCompute(threadGroupCounts, pipelineBinding);
	}

	void ComputeCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values)
	{
		commandList.ClearUAV(buffer, gpuViewIndex, cpuContainer, cpuViewIndex, values, containerBinding);
	}

	void ComputeCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<std::uint32_t>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearUAV(texture, gpuViewIndex, cpuContainer, cpuViewIndex, values, rects, containerBinding, arena);
	}

	void ComputeCommandList::ClearUAV(const IBuffer& buffer, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex,
		const Math::Vector4<float>& values)
	{
		commandList.ClearUAV(buffer, gpuViewIndex, cpuContainer, cpuViewIndex, values, containerBinding);
	}

	void ComputeCommandList::ClearUAV(const ITexture& texture, const std::uint32_t gpuViewIndex, const IShaderDataContainer& cpuContainer, const std::uint32_t cpuViewIndex, 
		const Math::Vector4<float>& values, const std::span<const Math::CornerRect<std::uint32_t>> rects)
	{
		commandList.ClearUAV(texture, gpuViewIndex, cpuContainer, cpuViewIndex, values, rects, containerBinding, arena);
	}

	void ComputeCommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		commandList.Copy(source, destination);
	}

	void ComputeCommandList::Copy(const IBuffer& source, IBuffer& destination, const std::span<const CopyBufferRange> ranges)
	{
		commandList.Copy(source, destination, ranges);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination)
	{
		commandList.Copy(source, destination);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures)
	{
		commandList.Copy(source, destination, subTextures);
	}

	void ComputeCommandList::Copy(const ITexture& source, ITexture& destination, const std::span<const CopySubTextureIndex> subTextures, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, subTextures, boxes);
	}

	void ComputeCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void ComputeCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, footprints, boxes);
	}

	void ComputeCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void ComputeCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const std::span<const CopySubTextureBox> boxes)
	{
		commandList.Copy(source, destination, footprints, boxes);
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
}
