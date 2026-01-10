/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Texture;

import std;

import PonyEngine.Platform.Windows;
import PonyEngine.RenderDevice;

export namespace PonyEngine::Render::Windows
{
	class D3D12Texture final : public ITexture
	{
	public:
		[[nodiscard("Pure constructor")]]
		D3D12Texture(ID3D12Resource2& resource, TextureFormatId format, std::span<const TextureFormatId> castableFormats,
			const Math::Vector3<std::uint32_t>& size, std::uint32_t mipCount, std::uint32_t arraySize, TextureDimension dimension, 
			enum SampleCount sampleCount, TextureUsage usage) noexcept;
		[[nodiscard("Pure constructor")]]
		D3D12Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, TextureFormatId format, std::span<const TextureFormatId> castableFormats,
			const Math::Vector3<std::uint32_t>& size, std::uint32_t mipCount, std::uint32_t arraySize, TextureDimension dimension,
			enum SampleCount sampleCount, TextureUsage usage) noexcept;
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
		ID3D12Resource2& Resource() noexcept;
		[[nodiscard("Pure function")]]
		const ID3D12Resource2& Resource() const noexcept;

		D3D12Texture& operator =(const D3D12Texture&) = delete;
		D3D12Texture& operator =(D3D12Texture&&) = delete;

	private:
		Platform::Windows::ComPtr<ID3D12Resource2> resource;

		TextureFormatId format;
		std::vector<TextureFormatId> castableFormats;
		Math::Vector3<std::uint32_t> size;
		std::uint32_t mipCount;
		std::uint32_t arraySize;
		TextureDimension dimension;
		enum SampleCount sampleCount;
		TextureUsage usage;
	};
}

namespace PonyEngine::Render::Windows
{
	D3D12Texture::D3D12Texture(ID3D12Resource2& resource, const TextureFormatId format, const std::span<const TextureFormatId> castableFormats,
		const Math::Vector3<std::uint32_t>& size, const std::uint32_t mipCount, const std::uint32_t arraySize, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage) noexcept :
		resource(&resource),
		format(format),
		castableFormats(castableFormats.cbegin(), castableFormats.cend()),
		size(size),
		mipCount{mipCount},
		arraySize{arraySize},
		dimension{dimension},
		sampleCount{sampleCount},
		usage{usage}
	{
	}

	D3D12Texture::D3D12Texture(Platform::Windows::ComPtr<ID3D12Resource2>&& resource, const TextureFormatId format, const std::span<const TextureFormatId> castableFormats,
		const Math::Vector3<std::uint32_t>& size, const std::uint32_t mipCount, const std::uint32_t arraySize, const TextureDimension dimension,
		const enum SampleCount sampleCount, const TextureUsage usage) noexcept :
		resource(std::move(resource)),
		format(format),
		castableFormats(castableFormats.cbegin(), castableFormats.cend()),
		size(size),
		mipCount{mipCount},
		arraySize{arraySize},
		dimension{dimension},
		sampleCount{sampleCount},
		usage{usage}
	{
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
		return castableFormats;
	}

	Math::Vector3<std::uint32_t> D3D12Texture::Size() const noexcept
	{
		return size;
	}

	std::uint32_t D3D12Texture::MipCount() const noexcept
	{
		return mipCount;
	}

	std::uint32_t D3D12Texture::ArraySize() const noexcept
	{
		return arraySize;
	}

	enum SampleCount D3D12Texture::SampleCount() const noexcept
	{
		return sampleCount;
	}

	TextureUsage D3D12Texture::Usage() const noexcept
	{
		return usage;
	}

	ID3D12Resource2& D3D12Texture::Resource() noexcept
	{
		return *resource;
	}

	const ID3D12Resource2& D3D12Texture::Resource() const noexcept
	{
		return *resource;
	}
}
