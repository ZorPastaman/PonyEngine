/***************************************************
 * MIT License                                     *
 *                                                 *
 * right (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:CommandList;

import std;

import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :Buffer;
import :CommandListUtility;
import :ObjectUtility;
import :Texture;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class CommandList final
	{
	public:
		[[nodiscard("Pure constructor")]]
		CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList);
		[[nodiscard("Pure constructor")]]
		CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator, Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList);
		CommandList(const CommandList&) = delete;
		CommandList(CommandList&&) = delete;

		~CommandList() noexcept = default;

		[[nodiscard("Pure function")]]
		ID3D12GraphicsCommandList10& GetCommandList() const noexcept;

		void Reset();
		void Close();
		[[nodiscard("Pure function")]]
		bool IsOpen() const noexcept;

		void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers);

		void SetDepthBias(const DepthBias& bias) noexcept;
		void SetDepthBounds(float min, float max) noexcept;
		void SetStencilReference(const StencilReference& reference) noexcept;

		void DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept;

		void ExecuteBundle(ID3D12GraphicsCommandList10& bundle) noexcept;

		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;
		void Name(std::string_view name);

		CommandList& operator =(const CommandList&) = delete;
		CommandList& operator =(CommandList&&) = delete;

	private:
		void ToNativeBarriers(std::span<const BufferBarrier> bufferBarriers, std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers) noexcept;
		void ToNativeBarriers(std::span<const TextureBarrier> textureBarriers, std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers) noexcept;

		static void ValidateBarriers(std::span<const BufferBarrier> bufferBarriers);
		static void ValidateBarriers(std::span<const TextureBarrier> textureBarriers);

		Platform::Windows::ComPtr<ID3D12CommandAllocator> allocator;
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10> commandList;

		Memory::Arena arena;

		bool isOpen;

		std::string name;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	CommandList::CommandList(ID3D12CommandAllocator& allocator, ID3D12GraphicsCommandList10& commandList) :
		allocator(&allocator),
		commandList(&commandList),
		arena(0uz, 2048uz),
		isOpen{true}
	{
		Reset();
	}

	CommandList::CommandList(Platform::Windows::ComPtr<ID3D12CommandAllocator>&& allocator,
		Platform::Windows::ComPtr<ID3D12GraphicsCommandList10>&& commandList) :
		allocator(std::move(allocator)),
		commandList(std::move(commandList)),
		arena(0uz, 2048uz),
		isOpen{ true }
	{
		assert(this->allocator && "The allocator is nullptr.");
		assert(this->commandList && "The command list is nullptr.");

		Reset();
	}

	ID3D12GraphicsCommandList10& CommandList::GetCommandList() const noexcept
	{
		return *commandList;
	}

	void CommandList::Reset()
	{
		if (const HRESULT result = allocator->Reset(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command allocator: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
		if (const HRESULT result = commandList->Reset(allocator.Get(), nullptr); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to reset command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		isOpen = true;
	}

	void CommandList::Close()
	{
		if (const HRESULT result = commandList->Close(); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to close command list: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}

		isOpen = false;
	}

	bool CommandList::IsOpen() const noexcept
	{
		return isOpen;
	}

	void CommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const std::span<const TextureBarrier> textureBarriers)
	{
		ValidateBarriers(bufferBarriers);
		ValidateBarriers(textureBarriers);

		arena.Free();
		const Memory::Arena::Slice<D3D12_BUFFER_BARRIER> nativeBufferBarriers = arena.Allocate<D3D12_BUFFER_BARRIER>(bufferBarriers.size());
		const Memory::Arena::Slice<D3D12_TEXTURE_BARRIER> nativeTextureBarriers = arena.Allocate<D3D12_TEXTURE_BARRIER>(textureBarriers.size());
		const std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriersSpan = arena.Span(nativeBufferBarriers);
		const std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriersSpan = arena.Span(nativeTextureBarriers);
		ToNativeBarriers(bufferBarriers, nativeBufferBarriersSpan);
		ToNativeBarriers(textureBarriers, nativeTextureBarriersSpan);

		std::array<D3D12_BARRIER_GROUP, 2> barrierGroups;
		UINT32 groupCount = 0u;
		if (!nativeBufferBarriersSpan.empty())
		{
			barrierGroups[groupCount++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_BUFFER,
				.NumBarriers = static_cast<UINT32>(nativeBufferBarriersSpan.size()),
				.pBufferBarriers = nativeBufferBarriersSpan.data()
			};
		}
		if (!nativeTextureBarriersSpan.empty())
		{
			barrierGroups[groupCount++] = D3D12_BARRIER_GROUP
			{
				.Type = D3D12_BARRIER_TYPE_TEXTURE,
				.NumBarriers = static_cast<UINT32>(nativeTextureBarriersSpan.size()),
				.pTextureBarriers = nativeTextureBarriersSpan.data()
			};
		}

		if (groupCount > 0u) [[likely]]
		{
			commandList->Barrier(groupCount, barrierGroups.data());
		}
	}

	void CommandList::SetDepthBias(const DepthBias& bias) noexcept
	{
		commandList->RSSetDepthBias(bias.depthBias, bias.depthBiasClamp, bias.slopeScaledDepthBias);
	}

	void CommandList::SetDepthBounds(const float min, const float max) noexcept
	{
		commandList->OMSetDepthBounds(min, max);
	}

	void CommandList::SetStencilReference(const StencilReference& reference) noexcept
	{
		commandList->OMSetFrontAndBackStencilRef(reference.front, reference.back);
	}

	void CommandList::DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts) noexcept
	{
		commandList->DispatchMesh(threadGroupCounts.X(), threadGroupCounts.Y(), threadGroupCounts.Z());
	}

	void CommandList::ExecuteBundle(ID3D12GraphicsCommandList10& bundle) noexcept
	{
		commandList->ExecuteBundle(&bundle);
	}

	std::string_view CommandList::Name() const noexcept
	{
		return name;
	}

	void CommandList::Name(const std::string_view name)
	{
		SetObjectName(*allocator, name);

		try
		{
			SetObjectName(*commandList, name);

			try
			{
				this->name = name;
			}
			catch (...)
			{
				SetObjectName(*commandList, this->name);
				throw;
			}
		}
		catch (...)
		{
			SetObjectName(*allocator, this->name);
			throw;
		}
	}

	void CommandList::ToNativeBarriers(const std::span<const BufferBarrier> bufferBarriers, const std::span<D3D12_BUFFER_BARRIER> nativeBufferBarriers) noexcept
	{
		for (std::size_t i = 0uz; i < bufferBarriers.size(); ++i)
		{
			const BufferBarrier& barrier = bufferBarriers[i];
			nativeBufferBarriers[i] = D3D12_BUFFER_BARRIER
			{
				.SyncBefore = ToSync(barrier.beforeStages),
				.SyncAfter = ToSync(barrier.afterStages),
				.AccessBefore = ToAccess(barrier.beforeAccesses),
				.AccessAfter = ToAccess(barrier.afterAccesses),
				.pResource = &static_cast<Buffer*>(barrier.buffer)->Resource(),
				.Offset = 0ull,
				.Size = std::numeric_limits<UINT64>::max()
			};
		}
	}

	void CommandList::ToNativeBarriers(const std::span<const TextureBarrier> textureBarriers, const std::span<D3D12_TEXTURE_BARRIER> nativeTextureBarriers) noexcept
	{
		for (std::size_t i = 0uz; i < textureBarriers.size(); ++i)
		{
			const TextureBarrier& barrier = textureBarriers[i];
			const auto texture = static_cast<Texture*>(barrier.texture);
			nativeTextureBarriers[i] = D3D12_TEXTURE_BARRIER
			{
				.SyncBefore = ToSync(barrier.beforeStages),
				.SyncAfter = ToSync(barrier.afterStages),
				.AccessBefore = ToAccess(barrier.beforeAccesses),
				.AccessAfter = ToAccess(barrier.afterAccesses),
				.LayoutBefore = ToLayout(barrier.beforeLayout),
				.LayoutAfter = ToLayout(barrier.afterLayout),
				.pResource = &texture->Resource(),
				.Subresources = barrier.range 
					? ToSubresourceRange(barrier.range->mipRange, barrier.range->arrayRange, barrier.range->aspects, texture->MipCount(), texture->ArraySize())
					: static_cast<D3D12_BARRIER_SUBRESOURCE_RANGE>(D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES),
				.Flags = barrier.discard ? D3D12_TEXTURE_BARRIER_FLAG_DISCARD : D3D12_TEXTURE_BARRIER_FLAG_NONE
			};
		}
	}

	void CommandList::ValidateBarriers(const std::span<const BufferBarrier> bufferBarriers)
	{
#ifndef NDEBUG
		if (bufferBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many buffer barriers");
		}

		for (const BufferBarrier& barrier : bufferBarriers)
		{
			if (!barrier.buffer || typeid(*barrier.buffer) != typeid(Buffer)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid buffer");
			}
		}
#endif
	}

	void CommandList::ValidateBarriers(const std::span<const TextureBarrier> textureBarriers)
	{
#ifndef NDEBUG
		if (textureBarriers.size() > std::numeric_limits<UINT32>::max()) [[unlikely]]
		{
			throw std::invalid_argument("Too many texture barriers");
		}

		for (const TextureBarrier& barrier : textureBarriers)
		{
			if (!barrier.texture || typeid(*barrier.texture) != typeid(Texture)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid texture");
			}

			if (barrier.range)
			{
				const Texture* const texture = static_cast<Texture*>(barrier.texture);
				const MultiAspectSubTextureRange& range = *barrier.range;

				if (range.mipRange.mostDetailedMipIndex + range.mipRange.mipCount.value_or(1u) > texture->MipCount()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid mip range");
				}
				if (range.arrayRange.firstArrayIndex + range.arrayRange.arrayCount.value_or(1u) > texture->ArraySize()) [[unlikely]]
				{
					throw std::invalid_argument("Invalid array range");
				}
			}

			if (barrier.discard && barrier.beforeLayout != ResourceLayout::Undefined) [[unlikely]]
			{
				throw std::invalid_argument("Invalid discard flag");
			}
		}
#endif
	}
}
