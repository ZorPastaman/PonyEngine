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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:Texture;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

import :Resource;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Texture wrapper.
	class Texture final : public ITexture
	{
	public:
		/// @brief Creates a texture wrapper.
		/// @param resource Texture resource.
		/// @param format Engine format.
		/// @param nativeFormat Native format.
		/// @param castableFormats Castable formats.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		/// @param mipCount Mip count.
		/// @param dimension Texture dimension.
		/// @param sampleCount Sample count.
		/// @param usage Texture usage.
		/// @param srgbCompatible Is the texture SRGB-compatible?
		[[nodiscard("Pure constructor")]]
		Texture(ID3D12Resource2& resource, TextureFormatId format, DXGI_FORMAT nativeFormat, std::span<const TextureFormatId> castableFormats,
			std::uint32_t width, std::uint32_t height, std::uint16_t depth, std::uint8_t mipCount, TextureDimension dimension, 
			enum SampleCount sampleCount, TextureUsage usage, bool srgbCompatible);
		/// @brief Creates a texture wrapper.
		/// @param resource Texture resource.
		/// @param format Engine format.
		/// @param nativeFormat Native format.
		/// @param castableFormats Castable formats.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		/// @param mipCount Mip count.
		/// @param dimension Texture dimension.
		/// @param sampleCount Sample count.
		/// @param usage Texture usage.
		/// @param srgbCompatible Is the texture SRGB-compatible?
		[[nodiscard("Pure constructor")]]
		Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, TextureFormatId format, DXGI_FORMAT nativeFormat, std::span<const TextureFormatId> castableFormats,
			std::uint32_t width, std::uint32_t height, std::uint16_t depth, std::uint8_t mipCount, TextureDimension dimension,
			enum SampleCount sampleCount, TextureUsage usage, bool srgbCompatible);
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		~Texture() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual TextureDimension Dimension() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual TextureFormatId Format() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const TextureFormatId> CastableFormats() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Math::Vector3<std::uint32_t> Size() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::uint8_t MipCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::uint16_t ArraySize() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual enum SampleCount SampleCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual TextureUsage Usage() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool SRGBCompatible() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the texture resource.
		/// @return Texture resource.
		[[nodiscard("Pure function")]]
		ID3D12Resource2& Resource() const noexcept;
		/// @brief Gets the native format.
		/// @return Native format.
		[[nodiscard("Pure function")]]
		DXGI_FORMAT NativeFormat() const noexcept;

		Texture& operator =(const Texture&) = delete;
		Texture& operator =(Texture&&) = delete;

	private:
		class Resource resource; ///< Resource.

		TextureFormatId format; ///< Engine format.
		DXGI_FORMAT nativeFormat; ///< Native format.
		std::uint32_t castableFormatCount; ///< Castable format count.
		std::unique_ptr<TextureFormatId[]> castableFormats; ///< Castable formats.
		std::uint32_t width; ///< Width.
		std::uint32_t height; ///< Height.
		std::uint16_t depth; ///< Depth.
		std::uint8_t mipCount; ///< Mip count.
		TextureDimension dimension; ///< Texture dimension.
		enum SampleCount sampleCount; ///< Sample count.
		TextureUsage usage; ///< Texture usage.
		bool srgbCompatible; ///< Is the texture SRGB-compatible?
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	Texture::Texture(ID3D12Resource2& resource, const TextureFormatId format, const DXGI_FORMAT nativeFormat, const std::span<const TextureFormatId> castableFormats,
		const std::uint32_t width, const std::uint32_t height, const std::uint16_t depth, const std::uint8_t mipCount, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage, const bool srgbCompatible) :
		resource(resource),
		format(format),
		nativeFormat{nativeFormat},
		castableFormatCount{static_cast<std::uint32_t>(castableFormats.size())},
		castableFormats(this->castableFormatCount > 0u ? std::make_unique<TextureFormatId[]>(this->castableFormatCount) : nullptr),
		width{width},
		height{height},
		depth{depth},
		mipCount{mipCount},
		dimension{dimension},
		sampleCount{sampleCount},
		usage{usage},
		srgbCompatible{srgbCompatible}
	{
		assert(castableFormats.size() <= std::numeric_limits<std::uint32_t>::max() && "Castable format count is too great.");

		if (this->castableFormatCount > 0uz)
		{
			std::memcpy(this->castableFormats.get(), castableFormats.data(), castableFormats.size_bytes());
		}
	}

	Texture::Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const TextureFormatId format, const DXGI_FORMAT nativeFormat, 
		const std::span<const TextureFormatId> castableFormats,
		const std::uint32_t width, const std::uint32_t height, const std::uint16_t depth, const std::uint8_t mipCount, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage, const bool srgbCompatible) :
		resource(std::move(resource)),
		format(format),
		nativeFormat{nativeFormat},
		castableFormatCount{static_cast<std::uint32_t>(castableFormats.size())},
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
		assert(castableFormats.size() <= std::numeric_limits<std::uint32_t>::max() && "Castable format count is too great.");

		if (this->castableFormatCount > 0uz)
		{
			std::memcpy(this->castableFormats.get(), castableFormats.data(), castableFormats.size_bytes());
		}
	}

	TextureDimension Texture::Dimension() const noexcept
	{
		return dimension;
	}

	TextureFormatId Texture::Format() const noexcept
	{
		return format;
	}

	std::span<const TextureFormatId> Texture::CastableFormats() const noexcept
	{
		return castableFormatCount > 0uz
			? std::span<const TextureFormatId>(castableFormats.get(), castableFormatCount)
			: std::span<const TextureFormatId>();
	}

	Math::Vector3<std::uint32_t> Texture::Size() const noexcept
	{
		return dimension == TextureDimension::Texture3D
			? Math::Vector3<std::uint32_t>(width, height, depth)
			: Math::Vector3<std::uint32_t>(width, height, 1u);
	}

	std::uint8_t Texture::MipCount() const noexcept
	{
		return mipCount;
	}

	std::uint16_t Texture::ArraySize() const noexcept
	{
		return dimension == TextureDimension::Texture3D ? 1u : depth;
	}

	enum SampleCount Texture::SampleCount() const noexcept
	{
		return sampleCount;
	}

	TextureUsage Texture::Usage() const noexcept
	{
		return usage;
	}

	bool Texture::SRGBCompatible() const noexcept
	{
		return srgbCompatible;
	}

	std::string_view Texture::Name() const noexcept
	{
		return resource.Name();
	}

	void Texture::Name(const std::string_view name)
	{
		resource.Name(name);
	}

	ID3D12Resource2& Texture::Resource() const noexcept
	{
		return resource.GetResource();
	}

	DXGI_FORMAT Texture::NativeFormat() const noexcept
	{
		return nativeFormat;
	}
}
