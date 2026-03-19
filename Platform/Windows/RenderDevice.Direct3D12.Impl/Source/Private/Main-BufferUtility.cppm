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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:BufferUtility;

import std;

import PonyEngine.RenderDevice;

import :Buffer;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	Buffer& ToNativeBuffer(IBuffer& buffer);
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	const Buffer& ToNativeBuffer(const IBuffer& buffer);
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	Buffer* ToNativeBuffer(IBuffer* buffer);
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	const Buffer* ToNativeBuffer(const IBuffer* buffer);
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	Buffer* ToNativeBufferNotNullptr(IBuffer* buffer);
	/// @brief Casts to a native buffer.
	/// @param buffer Engine buffer.
	/// @return Native buffer.
	[[nodiscard("Pure function")]]
	const Buffer* ToNativeBufferNotNullptr(const IBuffer* buffer);

	/// @brief Makes a resource description.
	/// @param params Buffer parameters.
	/// @return Resource description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_DESC1 MakeResourceDesc(const BufferParams& params) noexcept;
	/// @brief Gets resource flags.
	/// @param usage Buffer usage.
	/// @return Resource flags.
	[[nodiscard("Pure function")]]
	constexpr D3D12_RESOURCE_FLAGS GetResourceFlags(BufferUsage usage) noexcept;

	/// @brief Makes a constants buffer view description.
	/// @param address Basic address.
	/// @param params Constant buffer view parameters.
	/// @return Constants buffer view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_CONSTANT_BUFFER_VIEW_DESC MakeCBVDesc(D3D12_GPU_VIRTUAL_ADDRESS address, const CBVParams& params) noexcept;
	/// @brief Makes a shader resource view description.
	/// @param params Buffer shader resource view parameters.
	/// @return Shader resource view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC MakeSRVDesc(const BufferSRVParams& params) noexcept;
	/// @brief Makes an unordered access view description.
	/// @param params Buffer unordered access view parameters.
	/// @return Unordered access view description.
	[[nodiscard("Pure function")]]
	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC MakeUAVDesc(const BufferUAVParams& params) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Buffer& ToNativeBuffer(IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<Buffer&>(buffer);
	}

	const Buffer& ToNativeBuffer(const IBuffer& buffer)
	{
#ifndef NDEBUG
		if (typeid(buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const Buffer&>(buffer);
	}

	Buffer* ToNativeBuffer(IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (buffer && typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<Buffer*>(buffer);
	}

	const Buffer* ToNativeBuffer(const IBuffer* buffer)
	{
#ifndef NDEBUG
		if (buffer && typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const Buffer*>(buffer);
	}

	Buffer* ToNativeBufferNotNullptr(IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (!buffer || typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<Buffer*>(buffer);
	}

	const Buffer* ToNativeBufferNotNullptr(const IBuffer* const buffer)
	{
#ifndef NDEBUG
		if (!buffer || typeid(*buffer) != typeid(Buffer)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid buffer");
		}
#endif

		return static_cast<const Buffer*>(buffer);
	}

	constexpr D3D12_RESOURCE_DESC1 MakeResourceDesc(const BufferParams& params) noexcept
	{
		return D3D12_RESOURCE_DESC1
		{
			.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
			.Alignment = 0ull,
			.Width = params.size,
			.Height = 1u,
			.DepthOrArraySize = 1u,
			.MipLevels = 1u,
			.Format = DXGI_FORMAT_UNKNOWN,
			.SampleDesc = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u},
			.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
			.Flags = GetResourceFlags(params.usage),
			.SamplerFeedbackMipRegion = D3D12_MIP_REGION{}
		};
	}

	constexpr D3D12_RESOURCE_FLAGS GetResourceFlags(const BufferUsage usage) noexcept
	{
		auto flags = D3D12_RESOURCE_FLAG_NONE;
		if (Any(BufferUsage::UnorderedAccess, usage))
		{
			flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		}

		return flags;
	}

	constexpr D3D12_CONSTANT_BUFFER_VIEW_DESC MakeCBVDesc(const D3D12_GPU_VIRTUAL_ADDRESS address, const CBVParams& params) noexcept
	{
		return D3D12_CONSTANT_BUFFER_VIEW_DESC
		{
			.BufferLocation = address + params.offset,
			.SizeInBytes = params.size
		};
	}

	constexpr D3D12_SHADER_RESOURCE_VIEW_DESC MakeSRVDesc(const BufferSRVParams& params) noexcept
	{
		return D3D12_SHADER_RESOURCE_VIEW_DESC
		{
			.Format = DXGI_FORMAT_UNKNOWN,
			.ViewDimension = D3D12_SRV_DIMENSION_BUFFER,
			.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
			.Buffer = D3D12_BUFFER_SRV
			{
				.FirstElement = params.firstElementIndex,
				.NumElements = params.elementCount,
				.StructureByteStride = params.stride,
				.Flags = D3D12_BUFFER_SRV_FLAG_NONE
			}
		};
	}

	constexpr D3D12_UNORDERED_ACCESS_VIEW_DESC MakeUAVDesc(const BufferUAVParams& params) noexcept
	{
		return D3D12_UNORDERED_ACCESS_VIEW_DESC
		{
			.Format = DXGI_FORMAT_UNKNOWN,
			.ViewDimension = D3D12_UAV_DIMENSION_BUFFER,
			.Buffer = D3D12_BUFFER_UAV
			{
				.FirstElement = params.firstElementIndex,
				.NumElements = params.elementCount,
				.StructureByteStride = params.stride,
				.CounterOffsetInBytes = 0ull,
				.Flags = D3D12_BUFFER_UAV_FLAG_NONE
			}
		};
	}
}
