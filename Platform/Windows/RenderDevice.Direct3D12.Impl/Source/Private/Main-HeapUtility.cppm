/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:HeapUtility;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Makes heap properties.
	/// @param heapType Heap type.
	/// @return Heap properties.
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_PROPERTIES MakeHeapProperties(HeapType heapType) noexcept;
	/// @brief Casts the engine heap type to a native heap type.
	/// @param heapType Engine heap type.
	/// @return Native heap type.
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_TYPE ToHeapType(HeapType heapType) noexcept;

	/// @brief Gets heap flags.
	/// @param usage Buffer usage.
	/// @param notZeroed Is the heap not zeroed?
	/// @return Heap flags.
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_FLAGS GetHeapFlags(BufferUsage usage, bool notZeroed) noexcept;
	/// @brief Gets heap flags.
	/// @param usage Texture usage.
	/// @param notZeroed Is the heap not zeroed?
	/// @return Heap flags.
	[[nodiscard("Pure function")]]
	constexpr D3D12_HEAP_FLAGS MakeHeapFlags(TextureUsage usage, bool notZeroed) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr D3D12_HEAP_PROPERTIES MakeHeapProperties(const HeapType heapType) noexcept
	{
		return D3D12_HEAP_PROPERTIES
		{
			.Type = ToHeapType(heapType),
			.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
			.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
			.CreationNodeMask = 0u,
			.VisibleNodeMask = 0u
		};
	}

	constexpr D3D12_HEAP_TYPE ToHeapType(const HeapType heapType) noexcept
	{
		switch (heapType)
		{
		case HeapType::Default:
			return D3D12_HEAP_TYPE_DEFAULT;
		case HeapType::Upload:
			return D3D12_HEAP_TYPE_UPLOAD;
		case HeapType::Download:
			return D3D12_HEAP_TYPE_READBACK;
		default: [[unlikely]]
			assert(false && "Invalid heap type.");
			return D3D12_HEAP_TYPE_DEFAULT;
		}
	}

	constexpr D3D12_HEAP_FLAGS GetHeapFlags(const BufferUsage usage, const bool notZeroed) noexcept
	{
		auto flags = D3D12_HEAP_FLAG_NONE;
		if (notZeroed)
		{
			flags |= D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
		}
		if (Any(BufferUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
		}

		return flags;
	}

	constexpr D3D12_HEAP_FLAGS MakeHeapFlags(const TextureUsage usage, const bool notZeroed) noexcept
	{
		auto flags = D3D12_HEAP_FLAG_NONE;
		if (notZeroed)
		{
			flags |= D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
		}
		if (Any(TextureUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS;
		}

		return flags;
	}
}
