/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Texture;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;
import <string>;
import <string_view>;
import <utility>;

import PonyBase.Container;

import PonyMath.Color;
import PonyMath.Core;

import PonyEngine.Render;
import PonyEngine.Render.Detail.PixelHandlers;

import :TextureDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Texture.
	class Texture final : public ITexture
	{
	public:
		/// @brief Creates a texture.
		/// @param params Texture parameters.
		/// @param bufferParams Buffer parameters.
		/// @param pixelHandler Pixel handler.
		[[nodiscard("Pure constructor")]]
		Texture(const TextureParams& params, PonyBase::Container::BufferParams bufferParams, const IPixelHandler& pixelHandler);
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		~Texture() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual TextureDimension Dimension() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual TextureFormat Format() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t BlockSize() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint64_t BlockCount() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Width() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Height() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Depth() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data() const noexcept override;
		virtual void Data(std::span<const std::byte> data) override;

		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Block(std::uint64_t index) const noexcept override;
		virtual void Block(std::uint64_t index, std::span<const std::byte> data) override;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(std::uint32_t x, std::uint32_t y, std::uint32_t z) const override;
		virtual void Color(const PonyMath::Color::RGBA<float>& color, std::uint32_t x, std::uint32_t y, std::uint32_t z) override;

		[[nodiscard("Pure function")]]
		virtual std::pair<float, std::uint8_t> DepthStencil(std::uint32_t x, std::uint32_t y, std::uint32_t z) const override;
		virtual void DepthStencil(const std::pair<float, std::uint8_t>& depthStencil, std::uint32_t x, std::uint32_t y, std::uint32_t z) override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		/// @brief Gets the dirty flags.
		/// @return Dirty flags.
		[[nodiscard("Pure function")]]
		TextureDirtyFlag DirtyFlags() const noexcept;
		/// @brief Resets the dirty flags.
		void ResetDirty() noexcept;

		Texture& operator =(const Texture&) = delete;
		Texture& operator =(Texture&&) = delete;

	private:
		PonyBase::Container::Buffer buffer; ///< Data buffer.

		TextureDimension dimension; ///< Texture dimension.
		TextureFormat format; ///< Texture format.

		PonyMath::Core::Vector3<std::uint32_t> size; ///< Texture size.

		std::string name; ///< Texture name.

		const IPixelHandler* pixelHandler; ///< Pixel handler.

		TextureDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render
{
	Texture::Texture(const TextureParams& params, const PonyBase::Container::BufferParams bufferParams, const IPixelHandler& pixelHandler) :
		buffer(bufferParams),
		dimension{params.dimension},
		format{params.format},
		size(params.width, params.height, params.depth),
		name(params.name),
		pixelHandler{&pixelHandler},
		dirtyFlags{TextureDirtyFlag::All}
	{
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
		return static_cast<std::uint32_t>(buffer.Stride());
	}

	std::uint64_t Texture::BlockCount() const noexcept
	{
		return static_cast<std::uint64_t>(buffer.Count());
	}

	std::size_t Texture::Size() const noexcept
	{
		return buffer.Size();
	}

	std::uint32_t Texture::Width() const noexcept
	{
		return size.X();
	}

	std::uint32_t Texture::Height() const noexcept
	{
		return size.Y();
	}

	std::uint32_t Texture::Depth() const noexcept
	{
		return size.Z();
	}

	std::span<const std::byte> Texture::Data() const noexcept
	{
		return buffer.Span();
	}

	void Texture::Data(const std::span<const std::byte> data)
	{
		const std::span<std::byte> span = buffer.Span();
		if (data.size() != span.size()) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect size. Must be equal the buffer size.");
		}

		std::ranges::copy(data, span.data());
		dirtyFlags |= TextureDirtyFlag::Data;
	}

	std::span<const std::byte> Texture::Block(const std::uint64_t index) const noexcept
	{
		return buffer.Span(static_cast<std::size_t>(index));
	}

	void Texture::Block(const std::uint64_t index, const std::span<const std::byte> data)
	{
		const std::span<std::byte> span = buffer.Span(static_cast<std::size_t>(index));
		if (data.size() != span.size()) [[unlikely]]
		{
			throw std::invalid_argument("Incorrect size. Must be equal the buffer stride.");
		}

		std::ranges::copy(data, span.data());
		dirtyFlags |= TextureDirtyFlag::Data;
	}

	PonyMath::Color::RGBA<float> Texture::Color(const std::uint32_t x, const std::uint32_t y, const std::uint32_t z) const
	{
		return pixelHandler->Color(buffer, size, PonyMath::Core::Vector3<std::uint32_t>(x, y, z));
	}

	void Texture::Color(const PonyMath::Color::RGBA<float>& color, const std::uint32_t x, const std::uint32_t y, const std::uint32_t z)
	{
		pixelHandler->Color(buffer, size, PonyMath::Core::Vector3<std::uint32_t>(x, y, z), color);
		dirtyFlags |= TextureDirtyFlag::Data;
	}

	std::pair<float, std::uint8_t> Texture::DepthStencil(const std::uint32_t x, const std::uint32_t y, const std::uint32_t z) const
	{
		return pixelHandler->DepthStencil(buffer, size, PonyMath::Core::Vector3<std::uint32_t>(x, y, z));
	}

	void Texture::DepthStencil(const std::pair<float, std::uint8_t>& depthStencil, const std::uint32_t x, const std::uint32_t y, const std::uint32_t z)
	{
		pixelHandler->DepthStencil(buffer, size, PonyMath::Core::Vector3<std::uint32_t>(x, y, z), depthStencil);
		dirtyFlags |= TextureDirtyFlag::Data;
	}

	std::string_view Texture::Name() const noexcept
	{
		return name;
	}

	void Texture::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		dirtyFlags |= TextureDirtyFlag::Name;
	}

	TextureDirtyFlag Texture::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void Texture::ResetDirty() noexcept
	{
		dirtyFlags = TextureDirtyFlag::None;
	}
}
