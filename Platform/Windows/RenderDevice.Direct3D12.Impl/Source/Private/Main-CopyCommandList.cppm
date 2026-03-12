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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CopyCommandList;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :CommandList;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class CopyCommandList final : public ICopyCommandList
	{
	public:
		[[nodiscard("Pure constructor")]]
		CopyCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		CopyCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		CopyCommandList(const CopyCommandList&) = delete;
		CopyCommandList(CopyCommandList&&) = delete;

		~CopyCommandList() noexcept = default;

		virtual void Reset() override;
		virtual void Close() override;
		[[nodiscard("Pure function")]] 
		virtual bool IsOpen() const noexcept override;

		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) override;

		virtual void Copy(const IBuffer& source, IBuffer& destination) override;
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges) override;
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

		CopyCommandList& operator =(const CopyCommandList&) = delete;
		CopyCommandList& operator =(CopyCommandList&&) = delete;

	private:
		class CommandList commandList;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CopyCommandList::CopyCommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		commandList(allocator, commandList)
	{
	}

	CopyCommandList::CopyCommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		commandList(std::move(allocator), std::move(commandList))
	{
	}

	void CopyCommandList::Reset()
	{
		commandList.Reset();
	}

	void CopyCommandList::Close()
	{
		commandList.Close();
	}

	bool CopyCommandList::IsOpen() const noexcept
	{
		return commandList.IsOpen();
	}

	void CopyCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		commandList.Barrier(bufferBarriers, textureBarriers);
	}

	void CopyCommandList::Copy(const IBuffer& source, IBuffer& destination)
	{
		commandList.Copy(source, destination);
	}

	void CopyCommandList::Copy(const IBuffer& source, IBuffer& destination, const std::span<const CopyBufferRange> ranges)
	{
		commandList.Copy(source, destination, ranges);
	}

	void CopyCommandList::Copy(const ITexture& source, ITexture& destination)
	{
		commandList.Copy(source, destination);
	}

	void CopyCommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void CopyCommandList::Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, range);
	}

	void CopyCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void CopyCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void CopyCommandList::Copy(const IBuffer& source, ITexture& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void CopyCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints)
	{
		commandList.Copy(source, destination, footprints);
	}

	void CopyCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	void CopyCommandList::Copy(const ITexture& source, IBuffer& destination, const std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range)
	{
		commandList.Copy(source, destination, footprints, range);
	}

	std::string_view CopyCommandList::Name() const noexcept
	{
		return commandList.Name();
	}

	void CopyCommandList::Name(const std::string_view name)
	{
		commandList.Name(name);
	}

	ID3D12GraphicsCommandList10& CopyCommandList::CommandList() const noexcept
	{
		return commandList.GetCommandList();
	}
}
