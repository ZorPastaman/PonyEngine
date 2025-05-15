/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render:ITexture;

import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;
import <string_view>;
import <utility>;

import PonyMath.Color;

import :TextureFormat;
import :TextureDimension;

export namespace PonyEngine::Render
{
	/// @brief Texture.
	class ITexture
	{
		INTERFACE_BODY(ITexture)

		/// @brief Gets the dimension.
		/// @return Dimension.
		[[nodiscard("Pure function")]]
		virtual TextureDimension Dimension() const noexcept = 0;
		/// @brief Gets the format.
		/// @return Format.
		[[nodiscard("Pure function")]]
		virtual TextureFormat Format() const noexcept = 0;

		/// @brief Gets the block size.
		/// @return Block size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t BlockSize() const noexcept = 0;
		/// @brief Gets the block count.
		/// @return Block count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t BlockCount() const noexcept = 0;
		/// @brief Gets the texture size.
		/// @return Texture size in bytes.
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept = 0;

		/// @brief Gets the width.
		/// @return Width in pixels.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Width() const noexcept = 0;
		/// @brief Gets the height.
		/// @return Height in pixels.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Height() const noexcept = 0;
		/// @brief Gets the depth or an array size.
		/// @return Depth in pixels or array size.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Depth() const noexcept = 0;

		/// @brief Gets the raw data.
		/// @return Raw data.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Data() const noexcept = 0;
		/// @brief Gets the raw data.
		/// @tparam T Data type. Its size must be the same as the block size.
		/// @return Raw data.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Data() const;
		/// @brief Sets the raw data.
		/// @param data Data to sets. Its size must be the same as the texture size.
		virtual void Data(std::span<const std::byte> data) = 0;
		/// @brief Sets the raw data.
		/// @tparam T Data type. Its size must be the same as the block size.
		/// @param data Data to sets. Its size must be the same as the texture size.
		template<typename T>
		void Data(std::span<const T> data);

		/// @brief Gets a raw block.
		/// @param index Block index.
		/// @return Raw block.
		[[nodiscard("Pure function")]]
		virtual std::span<const std::byte> Block(std::uint64_t index) const noexcept = 0;
		/// @brief Gets a raw block.
		/// @tparam T Data type. Its size must be the same as the block size.
		/// @param index Block index.
		/// @return Raw block.
		template<typename T> [[nodiscard("Pure function")]]
		std::span<const T> Block(std::uint64_t index) const;
		/// @brief Sets a raw block.
		/// @param index Block index.
		/// @param data Data to set. Its size must be the same as the block size.
		virtual void Block(std::uint64_t index, std::span<const std::byte> data) = 0;
		/// @brief Sets a raw block.
		/// @tparam T Data type. Its size must be the same as the block size.
		/// @param index Block index.
		/// @param data Data to set. Its size must be the same as the block size.
		template<typename T>
		void Block(std::uint64_t index, std::span<const T> data);

		/// @brief Gets a pixel color.
		/// @note Texture format must be pixel accessible and color type.
		/// @param x X-coordinate.
		/// @param y Y-coordinate. Texture1D ignores this value. Texture1D interprets this as an array element.
		/// @param z Z-coordinate. Texture1D, Texture1DArray and Texture2D ignore this value.
		/// @return Color.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(std::uint32_t x, std::uint32_t y = 0u, std::uint32_t z = 0u) const = 0;
		/// @brief Sets a pixel color.
		/// @note Texture format must be pixel accessible and color type.
		/// @param color Color to set.
		/// @param x X-coordinate.
		/// @param y Y-coordinate. Texture1D ignores this value. Texture1D interprets this as an array element.
		/// @param z Z-coordinate. Texture1D, Texture1DArray and Texture2D ignore this value.
		virtual void Color(const PonyMath::Color::RGBA<float>& color, std::uint32_t x, std::uint32_t y = 0u, std::uint32_t z = 0u) = 0;

		/// @brief Gets a pixel depth stencil.
		/// @note Texture format must be pixel accessible and depth type.
		/// @param x X-coordinate.
		/// @param y Y-coordinate. Texture1D ignores this value.
		/// @param z Z-coordinate. Texture1D, Texture1DArray and Texture2D ignore this value.
		/// @return Color.
		[[nodiscard("Pure function")]]
		virtual std::pair<float, std::uint8_t> DepthStencil(std::uint32_t x, std::uint32_t y = 0u, std::uint32_t z = 0u) const = 0;
		/// @brief Sets a pixel depth stencil.
		/// @note Texture format must be pixel accessible and depth type.
		/// @param depthStencil Depth stencil to set.
		/// @param x X-coordinate.
		/// @param y Y-coordinate. Texture1D ignores this value. Texture1D interprets this as an array element.
		/// @param z Z-coordinate. Texture1D, Texture1DArray and Texture2D ignore this value.
		virtual void DepthStencil(const std::pair<float, std::uint8_t>& depthStencil, std::uint32_t x, std::uint32_t y = 0u, std::uint32_t z = 0u) = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}

namespace PonyEngine::Render
{
	template <typename T>
	std::span<const T> ITexture::Data() const
	{
		if (sizeof(T) != BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Data();

		return std::span<const T>(reinterpret_cast<const T*>(span.data()), span.size() / sizeof(T));
	}

	template <typename T>
	void ITexture::Data(const std::span<const T> data)
	{
		if (sizeof(T) != BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		Data(std::span<const std::byte>(reinterpret_cast<const std::byte*>(data.data()), data.size() * sizeof(T)));
	}

	template <typename T>
	std::span<const T> ITexture::Block(const std::uint64_t index) const
	{
		if (sizeof(T) != BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		const std::span<const std::byte> span = Block(index);

		return std::span<const T>(reinterpret_cast<const T*>(span.data()), span.size() / sizeof(T));
	}

	template <typename T>
	void ITexture::Block(const std::uint64_t index, const std::span<const T> data)
	{
		if (sizeof(T) != BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Incompatible type.");
		}

		Block(index, std::span<const std::byte>(reinterpret_cast<std::byte*>(data.data()), data.size() * sizeof(T)));
	}
}
