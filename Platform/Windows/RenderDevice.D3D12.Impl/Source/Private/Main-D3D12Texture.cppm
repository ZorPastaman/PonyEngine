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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Texture;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :D3D12Resource;
import :D3D12Utility;
import :EngineUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12Texture final : public ITexture
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12Texture(ID3D12Resource2& resource, TextureFormatId format, std::span<const TextureFormatId> castableFormats,
			std::uint32_t width, std::uint32_t height, std::uint16_t depth, std::uint16_t mipCount, TextureDimension dimension, 
			enum SampleCount sampleCount, TextureUsage usage, bool srgbCompatible);
		[[nodiscard("Pure constructor")]]
		D3D12Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, TextureFormatId format, std::span<const TextureFormatId> castableFormats,
			std::uint32_t width, std::uint32_t height, std::uint16_t depth, std::uint16_t mipCount, TextureDimension dimension,
			enum SampleCount sampleCount, TextureUsage usage, bool srgbCompatible);
		D3D12Texture(const D3D12Texture&) = delete;
		D3D12Texture(D3D12Texture&&) = delete;

		~D3D12Texture() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual TextureDimension Dimension() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual TextureFormatId Format() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const TextureFormatId> CastableFormats() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Math::Vector3<std::uint32_t> Size() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::uint32_t MipCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::uint32_t ArraySize() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual enum SampleCount SampleCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual TextureUsage Usage() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool SRGBCompatible() const noexcept override;

		virtual void* Map(const SubTextureIndex& index) override;
		virtual void* Map(const SubTextureIndex& index, std::uint64_t offset, std::uint64_t length) override;
		virtual void Unmap(const SubTextureIndex& index) override;
		virtual void Unmap(const SubTextureIndex& index, std::uint64_t offset, std::uint64_t length) override;

		virtual void SetName(std::string_view name) override;

		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() const noexcept;

		D3D12Texture& operator =(const D3D12Texture&) = delete;
		D3D12Texture& operator =(D3D12Texture&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		UINT CalculateSubresourceIndex(std::uint32_t mipIndex, std::uint32_t arrayIndex, Aspect aspect) const;

		D3D12Resource resource;

		TextureFormatId format;
		std::size_t castableFormatCount;
		std::unique_ptr<TextureFormatId[]> castableFormats;
		std::uint32_t width;
		std::uint32_t height;
		std::uint16_t depth;
		std::uint16_t mipCount;
		TextureDimension dimension;
		enum SampleCount sampleCount;
		TextureUsage usage;
		bool srgbCompatible;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12Texture::D3D12Texture(ID3D12Resource2& resource, const TextureFormatId format, const std::span<const TextureFormatId> castableFormats,
		const std::uint32_t width, const std::uint32_t height, const std::uint16_t depth, const std::uint16_t mipCount, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage, const bool srgbCompatible) :
		resource(resource),
		format(format),
		castableFormatCount(castableFormats.size()),
		castableFormats(this->castableFormatCount > 0uz ? std::make_unique<TextureFormatId[]>(this->castableFormatCount) : nullptr),
		width{width},
		height{height},
		depth{depth},
		mipCount{mipCount},
		dimension{dimension},
		sampleCount{sampleCount},
		usage{usage},
		srgbCompatible{srgbCompatible}
	{
		if (this->castableFormatCount > 0uz)
		{
			std::memcpy(this->castableFormats.get(), castableFormats.data(), castableFormats.size_bytes());
		}
	}

	D3D12Texture::D3D12Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const TextureFormatId format, const std::span<const TextureFormatId> castableFormats,
		const std::uint32_t width, const std::uint32_t height, const std::uint16_t depth, const std::uint16_t mipCount, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage, const bool srgbCompatible) :
		resource(std::move(resource)),
		format(format),
		castableFormatCount(castableFormats.size()),
		castableFormats(this->castableFormatCount > 0uz ? std::make_unique<TextureFormatId[]>(this->castableFormatCount) : nullptr),
		width{width},
		height{height},
		depth{depth},
		mipCount{mipCount},
		dimension{dimension},
		sampleCount{sampleCount},
		usage{usage},
		srgbCompatible{srgbCompatible}
	{
		if (this->castableFormatCount > 0uz)
		{
			std::memcpy(this->castableFormats.get(), castableFormats.data(), castableFormats.size_bytes());
		}
	}

	TextureDimension D3D12Texture::Dimension() const noexcept
	{
		return dimension;
	}

	TextureFormatId D3D12Texture::Format() const noexcept
	{
		return format;
	}

	std::span<const TextureFormatId> D3D12Texture::CastableFormats() const noexcept
	{
		return castableFormatCount > 0uz
			? std::span<const TextureFormatId>(castableFormats.get(), castableFormatCount)
			: std::span<const TextureFormatId>();
	}

	Math::Vector3<std::uint32_t> D3D12Texture::Size() const noexcept
	{
		return dimension == TextureDimension::Texture3D
			? Math::Vector3<std::uint32_t>(width, height, depth)
			: Math::Vector3<std::uint32_t>(width, height, 1u);
	}

	std::uint32_t D3D12Texture::MipCount() const noexcept
	{
		return mipCount;
	}

	std::uint32_t D3D12Texture::ArraySize() const noexcept
	{
		return dimension == TextureDimension::Texture3D ? 1u : depth;
	}

	enum SampleCount D3D12Texture::SampleCount() const noexcept
	{
		return sampleCount;
	}

	TextureUsage D3D12Texture::Usage() const noexcept
	{
		return usage;
	}

	bool D3D12Texture::SRGBCompatible() const noexcept
	{
		return srgbCompatible;
	}

	void* D3D12Texture::Map(const SubTextureIndex& index)
	{
		return resource.Map(CalculateSubresourceIndex(index.mipIndex, index.arrayIndex, index.aspect));
	}

	void* D3D12Texture::Map(const SubTextureIndex& index, const std::uint64_t offset, const std::uint64_t length)
	{
		return resource.Map(CalculateSubresourceIndex(index.mipIndex, index.arrayIndex, index.aspect), static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
	}

	void D3D12Texture::Unmap(const SubTextureIndex& index)
	{
		resource.Unmap(CalculateSubresourceIndex(index.mipIndex, index.arrayIndex, index.aspect));
	}

	void D3D12Texture::Unmap(const SubTextureIndex& index, const std::uint64_t offset, const std::uint64_t length)
	{
		resource.Unmap(CalculateSubresourceIndex(index.mipIndex, index.arrayIndex, index.aspect), static_cast<SIZE_T>(offset), static_cast<SIZE_T>(length));
	}

	void D3D12Texture::SetName(const std::string_view name)
	{
		resource.SetName(name);
	}

	ID3D12Resource2& D3D12Texture::Resource() const noexcept
	{
		return resource.Resource();
	}

	UINT D3D12Texture::CalculateSubresourceIndex(const std::uint32_t mipIndex, const std::uint32_t arrayIndex, const Aspect aspect) const
	{
		if (mipIndex >= mipCount) [[unlikely]]
		{
			throw std::out_of_range("Mip index is out of range");
		}
		if (arrayIndex >= ArraySize()) [[unlikely]]
		{
			throw std::out_of_range("Array index is out of range");
		}
		const DXGI_FORMAT nativeFormat = resource.Resource().GetDesc1().Format;
		switch (aspect)
		{
		case Aspect::Color:
			if (IsDepthStencilFormat(nativeFormat)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		case Aspect::Depth:
			if (!IsDepthStencilFormat(nativeFormat)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		case Aspect::Stencil:
			if (GetStencilViewFormat(nativeFormat) == DXGI_FORMAT_UNKNOWN) [[unlikely]]
			{
				throw std::invalid_argument("Invalid aspect");
			}
			break;
		default: [[unlikely]]
			assert(false && "Invalid aspect");
			break;
		}

		return CalculateSubresource(static_cast<UINT16>(mipIndex), static_cast<UINT16>(arrayIndex), static_cast<UINT8>(ToPlaneIndex(aspect)),
			static_cast<UINT16>(mipCount), static_cast<UINT16>(ArraySize()));
	}
}
