/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Texture;

import <cstddef>;
import <cstdint>;
import <utility>;

import PonyBase.Container;

import :TextureDimension;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Texture.
	class Texture
	{
	public:
		virtual ~Texture() noexcept = default;

		/// @brief Gets the texture buffer.
		/// @return Texture buffer.
		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Data() const noexcept;

		/// @brief Gets the texture dimension.
		/// @return Texture dimension.
		[[nodiscard("Pure function")]]
		TextureDimension Dimension() const noexcept;
		/// @brief Gets the texture format.
		/// @return Texture format.
		[[nodiscard("Pure function")]]
		TextureFormat Format() const noexcept;

		/// @brief Gets the block size.
		/// @return Block size in bytes. For uncompressed textures it's a size of a pixel, for compressed textures it's unspecified.
		[[nodiscard("Pure function")]]
		std::uint32_t BlockSize() const noexcept;
		/// @brief Gets the block count.
		/// @return Block count. For uncompressed textures it's a pixel count, for compressed textures it's unspecified.
		[[nodiscard("Pure function")]]
		std::uint32_t BlockCount() const noexcept;
		/// @brief Gets the texture size.
		/// @return Texture size in bytes.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Gets the texture width.
		/// @return Width.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Width() const noexcept = 0;
		/// @brief Gets the texture height.
		/// @return Height.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Height() const noexcept = 0;
		/// @brief Gets the texture depth.
		/// @return Depth.
		[[nodiscard("Pure function")]]
		virtual std::uint16_t Depth() const noexcept = 0;
		/// @brief Gets the texture pixel count.
		/// @return Pixel count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t PixelCount() const noexcept;

	protected:
		/// @brief Creates a texture.
		/// @param data Data buffer.
		/// @param dimension Texture dimension.
		/// @param format Texture format.
		[[nodiscard("Pure constructor")]]
		Texture(const PonyBase::Container::Buffer& data, TextureDimension dimension, TextureFormat format);
		/// @brief Creates a texture.
		/// @param data Data buffer.
		/// @param dimension Texture dimension.
		/// @param format Texture format.
		[[nodiscard("Pure constructor")]]
		Texture(PonyBase::Container::Buffer&& data, TextureDimension dimension, TextureFormat format) noexcept;
		[[nodiscard("Pure constructor")]]
		Texture(const Texture& other) = default;
		[[nodiscard("Pure constructor")]]
		Texture(Texture&& other) noexcept = default;

		Texture& operator =(const Texture& other) = default;
		Texture& operator =(Texture&& other) noexcept = default;

		PonyBase::Container::Buffer data; ///< Data buffer.

		TextureDimension dimension; ///< Texture dimension.
		TextureFormat format; ///< Texture format.

		// TODO: Add mips
	};
}

namespace PonyEngine::Render
{
	const PonyBase::Container::Buffer& Texture::Data() const noexcept
	{
		return data;
	}

	TextureDimension Texture::Dimension() const noexcept
	{
		return dimension;
	}

	TextureFormat Texture::Format() const noexcept
	{
		return format;
	}

	std::uint32_t Texture::BlockSize() const noexcept
	{
		return data.Stride();
	}

	std::uint32_t Texture::BlockCount() const noexcept
	{
		return data.Count();
	}

	std::size_t Texture::Size() const noexcept
	{
		return data.Size();
	}

	std::uint32_t Texture::PixelCount() const noexcept
	{
		return Width() * Height() * Depth();
	}

	Texture::Texture(const PonyBase::Container::Buffer& data, const TextureDimension dimension, const TextureFormat format) :
		data(data),
		dimension{dimension},
		format{format}
	{
	}

	Texture::Texture(PonyBase::Container::Buffer&& data, const TextureDimension dimension, const TextureFormat format) noexcept :
		data(std::move(data)),
		dimension{dimension},
		format{format}
	{
	}
}
