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

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:DescriptorHeapVisibility;

import <cstdint>;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Descriptor heap visibility.
	enum class DescriptorHeapVisibility : std::uint8_t
	{
		CPU,
		GPU
	};

	/// @brief Converts visibility to heap flags.
	/// @param visibility Visibility.
	/// @return Heap flags.
	[[nodiscard("Pure function")]]
	D3D12_DESCRIPTOR_HEAP_FLAGS ToHeapFlags(DescriptorHeapVisibility visibility) noexcept;
}

namespace PonyEngine::Render::Direct3D12
{
	D3D12_DESCRIPTOR_HEAP_FLAGS ToHeapFlags(const DescriptorHeapVisibility visibility) noexcept
	{
		switch (visibility)
		{
		case DescriptorHeapVisibility::CPU:
			return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		case DescriptorHeapVisibility::GPU:
			return D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		default: [[unlikely]]
			assert(false && "The visibility is incorrect.");
			return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		}
	}
}
