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

export module PonyEngine.Render:Texture;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <utility>;
import <vector>;

import PonyBase.Container;

import :ITextureObserver;
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

		/// @brief Gets the row size.
		/// @return Row size in bytes.
		[[nodiscard("Pure function")]]
		std::uint32_t RowSize() const noexcept;
		/// @brief Gets the row count.
		/// @return Row count.
		[[nodiscard("Pure function")]]
		std::uint32_t RowCount() const noexcept;
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
		std::uint32_t PixelCount() const noexcept;

		/// @brief Adds a texture observer.
		/// @param observer Texture observer to add.
		void AddObserver(ITextureObserver& observer) const;
		/// @brief Removes a texture observer.
		/// @param observer Texture observer to remove.
		void RemoveObserver(ITextureObserver& observer) const noexcept;

	protected:
		/// @brief Creates a texture.
		/// @param data Data buffer. Each stride must represent one row.
		/// @param dimension Texture dimension.
		/// @param format Texture format.
		[[nodiscard("Pure constructor")]]
		Texture(const PonyBase::Container::Buffer& data, TextureDimension dimension, TextureFormat format);
		/// @brief Creates a texture.
		/// @param data Data buffer. Each stride must represent one row.
		/// @param dimension Texture dimension.
		/// @param format Texture format.
		[[nodiscard("Pure constructor")]]
		Texture(PonyBase::Container::Buffer&& data, TextureDimension dimension, TextureFormat format) noexcept;
		[[nodiscard("Pure constructor")]]
		Texture(const Texture& other) = default;
		[[nodiscard("Pure constructor")]]
		Texture(Texture&& other) noexcept = default;

		/// @brief Calls @p OnTextureChanged() on each observer.
		void OnTextureChanged() const noexcept;

		Texture& operator =(const Texture& other) = default;
		Texture& operator =(Texture&& other) noexcept = default;

		PonyBase::Container::Buffer data; ///< Data buffer.

		TextureDimension dimension; ///< Texture dimension.
		TextureFormat format; ///< Texture format.

	private:
		mutable std::vector<ITextureObserver*> textureObservers; ///< Texture observers.

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

	std::uint32_t Texture::RowSize() const noexcept
	{
		return data.Stride();
	}

	std::uint32_t Texture::RowCount() const noexcept
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

	void Texture::AddObserver(ITextureObserver& observer) const
	{
		assert(std::ranges::find(textureObservers, &observer) == textureObservers.cend() && "The texture observer is already been added.");
		textureObservers.push_back(&observer);
	}

	void Texture::RemoveObserver(ITextureObserver& observer) const noexcept
	{
		if (const auto position = std::ranges::find(textureObservers, &observer); position != textureObservers.cend()) [[likely]]
		{
			textureObservers.erase(position);
		}
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

	void Texture::OnTextureChanged() const noexcept
	{
		for (ITextureObserver* const observer : textureObservers)
		{
			observer->OnTextureChanged();
		}
	}
}
