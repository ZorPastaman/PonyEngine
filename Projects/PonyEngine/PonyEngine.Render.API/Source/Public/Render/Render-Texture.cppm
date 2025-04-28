/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Texture;

import <utility>;

import PonyBase.Container;

import :TextureDimension;
import :TextureFormat;

export namespace PonyEngine::Render
{
	class Texture
	{
	public:
		virtual ~Texture() noexcept = default;

		[[nodiscard("Pure function")]]
		const PonyBase::Container::Buffer& Data() const noexcept;

		[[nodiscard("Pure function")]]
		TextureDimension Dimension() const noexcept;
		[[nodiscard("Pure function")]]
		TextureFormat Format() const noexcept;

	protected:
		[[nodiscard("Pure constructor")]]
		Texture(const PonyBase::Container::Buffer& data, TextureDimension dimension, TextureFormat format);
		[[nodiscard("Pure constructor")]]
		Texture(PonyBase::Container::Buffer&& data, TextureDimension dimension, TextureFormat format) noexcept;
		[[nodiscard("Pure constructor")]]
		Texture(const Texture& other) = default;
		[[nodiscard("Pure constructor")]]
		Texture(Texture&& other) noexcept = default;

		Texture& operator =(const Texture& other) = default;
		Texture& operator =(Texture&& other) noexcept = default;

		PonyBase::Container::Buffer data; ///< Texture data.

		TextureDimension dimension;
		TextureFormat format;

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
