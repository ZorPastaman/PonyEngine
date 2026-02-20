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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:GraphicsCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :BundleCommandList;
import :CommandList;
import :GraphicsComputePipelineBinding;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class GraphicsCommandList final : public IGraphicsCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		GraphicsCommandList(const GraphicsCommandList&) = delete;
		GraphicsCommandList(GraphicsCommandList&&) = delete;

		~GraphicsCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]]
		virtual bool IsOpen() const noexcept override;

		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) override;

		virtual void SetRasterRegions(std::span<const RasterRegion> regions) override;

		virtual void SetPipelineState(const IGraphicsPipelineState& pipelineState) override;
		virtual void SetPipelineState(const IComputePipelineState& pipelineState) override;

		virtual void SetDepthBias(const DepthBias& bias) override;
		virtual void SetDepthBounds(const DepthRange& range) override;
		virtual void SetStencilReference(const StencilReference& reference) override;

		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) override;

		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) override;

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

		virtual void Resolve(const ITexture& source, ITexture& destination, ResolveMode mode) override;
		virtual void Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, ResolveMode mode) override;
		virtual void Resolve(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range, ResolveMode mode) override;

		virtual void Execute(const ISecondaryGraphicsCommandList& secondary) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& CommandList() const noexcept;

		GraphicsCommandList& operator =(const GraphicsCommandList&) = delete;
		GraphicsCommandList& operator =(GraphicsCommandList&&) = delete;

	private:
		void ValidateState() const;

		void ValidatePipelineStateForGraphics() const;
		void ValidatePipelineStateForCompute() const;

		static void ValidateBundle(const ISecondaryGraphicsCommandList& secondary);

		class CommandList commandList;
		GraphicsComputePipelineBinding pipelineBinding;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	GraphicsCommandList::GraphicsCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList)
	{
	}

	GraphicsCommandList::GraphicsCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, 
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void GraphicsCommandList::Reset()
	{
		commandList.Reset();
		pipelineBinding.Reset();
	}

	void GraphicsCommandList::Close()
	{
		commandList.Close();
	}

	bool GraphicsCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void GraphicsCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		commandList.Barrier(bufferBarriers, textureBarriers);
	}

	void GraphicsCommandList::SetRasterRegions(const std::span<const RasterRegion> regions)
	{
		commandList.SetRasterRegions(regions);
	}

	void GraphicsCommandList::SetPipelineState(const IGraphicsPipelineState& pipelineState)
	{
		ValidateState();
		pipelineBinding.SetPipelineState(pipelineState, commandList);
	}

	void GraphicsCommandList::SetPipelineState(const IComputePipelineState& pipelineState)
	{
		ValidateState();
		pipelineBinding.SetPipelineState(pipelineState, commandList);
	}

	void GraphicsCommandList::SetDepthBias(const DepthBias& bias)
	{
		commandList.SetDepthBias(bias);
	}

	void GraphicsCommandList::SetDepthBounds(const DepthRange& range)
	{
		commandList.SetDepthBounds(range);
	}

	void GraphicsCommandList::SetStencilReference(const StencilReference& reference)
	{
		commandList.SetStencilReference(reference);
	}

	void GraphicsCommandList::SetBlendFactor(const Math::ColorRGBA<float>& factor)
	{
		commandList.SetBlendFactor(factor);
	}

	void GraphicsCommandList::DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		ValidatePipelineStateForGraphics();
		commandList.DispatchGraphics(threadGroupCounts);
	}

	void GraphicsCommandList::DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts)
	{
		ValidatePipelineStateForCompute();
		commandList.DispatchCompute(threadGroupCounts);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		commandList.Copy(source, destination);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, IBuffer& destination, const std::uint64_t sourceOffset, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		commandList.Copy(source, destination, sourceOffset, destinationOffset, size);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination)
	{
		commandList.Copy(source, destination);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void GraphicsCommandList::Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void GraphicsCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void GraphicsCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void GraphicsCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void GraphicsCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, mode);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const CopySubTextureRange& range, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, range, mode);
	}

	void GraphicsCommandList::Resolve(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range, const ResolveMode mode)
	{
		commandList.Resolve(source, destination, range, mode);
	}

	void GraphicsCommandList::Execute(const ISecondaryGraphicsCommandList& secondary)
	{
		ValidateBundle(secondary);

		const auto& bundle = static_cast<const BundleCommandList&>(secondary);
		commandList.ExecuteBundle(bundle.CommandList());
	}

	std::string_view GraphicsCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void GraphicsCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& GraphicsCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}

	void GraphicsCommandList::ValidateState() const
	{
#ifndef NDEBUG
		if (!commandList.IsOpen())
		{
			throw std::logic_error("Command list is closed");
		}
#endif
	}

	void GraphicsCommandList::ValidatePipelineStateForGraphics() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.IsLastPSOGraphics())
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}

	void GraphicsCommandList::ValidatePipelineStateForCompute() const
	{
#ifndef NDEBUG
		if (!pipelineBinding.IsLastPSOCompute())
		{
			throw std::invalid_argument("Invalid pipeline state");
		}
#endif
	}

	void GraphicsCommandList::ValidateBundle(const ISecondaryGraphicsCommandList& secondary)
	{
#ifndef NDEBUG
		if (typeid(secondary) != typeid(BundleCommandList)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid secondary graphics command list");
		}

		const auto& bundle = static_cast<const BundleCommandList&>(secondary);
		if (bundle.IsOpen()) [[unlikely]]
		{
			throw std::invalid_argument("Secondary graphics command list is open");
		}
#endif
	}
}
