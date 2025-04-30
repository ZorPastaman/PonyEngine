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

export module PonyEngine.Render:TextureFormat;

import <concepts>;
import <cstddef>;
import <cstdint>;
import <limits>;
import <unordered_map>;
import <unordered_set>;
import <utility>;

import PonyBase.Core;

import PonyMath.Color;
import PonyMath.Core;

export namespace PonyEngine::Render
{
	/// @brief Texture format.
	enum class TextureFormat : std::uint8_t
	{
		Unknown,
		R32G32B32A32_Float,
		R32G32B32A32_Uint,
		R32G32B32A32_Sint,
		R32G32B32_Float,
		R32G32B32_Uint,
		R32G32B32_Sint,
		R16G16B16A16_Float,
		R16G16B16A16_Unorm,
		R16G16B16A16_Uint,
		R16G16B16A16_Snorm,
		R16G16B16A16_Sint,
		R32G32_Float,
		R32G32_Uint,
		R32G32_Sint,
		D32_Float_S8X24_Uint,
		R8G8B8A8_Unorm,
		R8G8B8A8_Uint,
		R8G8B8A8_Snorm,
		R8G8B8A8_Sint,
		R16G16_Float,
		R16G16_Unorm,
		R16G16_Uint,
		R16G16_Snorm,
		R16G16_Sint,
		D32_Float,
		R32_Float,
		R32_Uint,
		R32_Sint,
		D24_Unorm_S8_Uint,
		R8G8_Unorm,
		R8G8_Uint,
		R8G8_Snorm,
		R8G8_Sint,
		R16_Float,
		D16_Unorm,
		R16_Unorm,
		R16_Uint,
		R16_Snorm,
		R16_Sint,
		R8_Unorm,
		R8_Uint,
		R8_Snorm,
		R8_Sint,
		A8_Unorm,
		R1_Unorm,
		BC1_Unorm,
		BC2_Unorm,
		BC3_Unorm,
		BC4_Unorm,
		BC4_Snorm,
		BC5_Unorm,
		BC5_Snorm,
		B8G8R8A8_Unorm,
		B8G8R8X8_Unorm,
		BC6H_UF16,
		BC6H_SF16,
		BC7_Unorm
	};

	/// @brief Pixel data types.
	enum class PixelDataType : std::uint8_t
	{
		Unknown,
		Snorm,
		Unorm,
		Sint,
		Uint,
		Float
	};

	/// @brief Gets a pixel size by the texture format.
	/// @param format Texture format. Mustn't be compressed.
	/// @return Pixel size in bytes.
	[[nodiscard("Pure function")]]
	std::uint32_t PixelSize(TextureFormat format) noexcept;
	/// @brief Gets a pixel data type.
	/// @param format Texture format. Mustn't be compressed. Mustn't be a depth stencil format.
	/// @return Pixel data type.
	[[nodiscard("Pure function")]]
	PixelDataType PixelType(TextureFormat format) noexcept;

	/// @brief Is the texture format a color format?
	/// @param format Texture format.
	/// @return @a True if it's a color format; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool IsColor(TextureFormat format) noexcept;
	/// @brief Is the texture format a depth stencil format?
	/// @param format Texture format.
	/// @return @a True if it's a depth stencil format; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool IsDepthStencil(TextureFormat format) noexcept;
	/// @brief Is the texture format compressed?
	/// @param format Texture format.
	/// @return @a True if it's compressed; @a false otherwise.
	[[nodiscard("Pure function")]]
	bool IsCompressed(TextureFormat format) noexcept;

	/// @brief Gets a pixel color.
	/// @details Snorm and unorm colors are returned in correct ranges: [-1, 1] and [0, 1].
	/// @tparam T Color component type.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format.
	/// @return Color.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	PonyMath::Color::RGBA<T> GetPixelColor(const std::byte* data, TextureFormat format) noexcept;
	/// @brief Gets a pixel color.
	/// @tparam T Color component type.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format. Must be a float or unorm as well.
	/// @return Color.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	PonyMath::Color::RGBAInt<T> GetPixelColor(const std::byte* data, TextureFormat format) noexcept;
	/// @brief Gets a raw-like pixel color.
	/// @details All the data is returned as is, without conversion.
	/// @tparam T Color component type.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format.
	/// @return Color.
	template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
	PonyMath::Core::Vector4<T> GetPixelColorData(const std::byte* data, TextureFormat format) noexcept;
	/// @brief Gets a pixel depth stencil.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be a depth stencil format.
	/// @return Depth stencil.
	std::pair<float, std::uint8_t> GetPixelDepthStencil(const std::byte* data, TextureFormat format) noexcept;

	/// @brief Sets a pixel color.
	/// @details Snorm and unorm colors must be in correct ranges: [-1, 1] and [0, 1].
	/// @tparam T Color component type.
	/// @param color Color source.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format.
	template<std::floating_point T> [[nodiscard("Pure function")]]
	void SetPixelColor(const PonyMath::Color::RGBA<T>& color, std::byte* data, TextureFormat format) noexcept;
	/// @brief Sets a pixel color.
	/// @tparam T Color component type.
	/// @param color Color source.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format. Must be a float or unorm as well.
	/// @return Color.
	template<std::unsigned_integral T> [[nodiscard("Pure function")]]
	void SetPixelColor(const PonyMath::Color::RGBAInt<T>& color, std::byte* data, TextureFormat format) noexcept;
	/// @brief Sets a raw-like pixel color.
	/// @details All the data is returned as is, without conversion.
	/// @tparam T Color component type.
	/// @param color Raw-like pixel color.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be an uncompressed color format.
	template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
	void SetPixelColorData(const PonyMath::Core::Vector4<T>& color, std::byte* data, TextureFormat format) noexcept;
	/// @brief Sets a pixel depth stencil.
	/// @param depth Depth.
	/// @param stencil Stencil.
	/// @param data Raw pixel data.
	/// @param format Texture format. Must be a depth stencil format.
	/// @return Depth stencil.
	void SetPixelDepthStencil(float depth, std::uint8_t stencil, std::byte* data, TextureFormat format) noexcept;
}

namespace PonyEngine::Render
{
	/// @brief Pixel sizes.
	const std::unordered_map<TextureFormat, std::uint32_t> PixelSizes
	{
		{ TextureFormat::R32G32B32A32_Float, 16 },
		{ TextureFormat::R32G32B32A32_Uint, 16 },
		{ TextureFormat::R32G32B32A32_Sint, 16 },
		{ TextureFormat::R32G32B32_Float, 12 },
		{ TextureFormat::R32G32B32_Uint, 12 },
		{ TextureFormat::R32G32B32_Sint, 12 },
		{ TextureFormat::R16G16B16A16_Float, 8 },
		{ TextureFormat::R16G16B16A16_Unorm, 8 },
		{ TextureFormat::R16G16B16A16_Uint, 8 },
		{ TextureFormat::R16G16B16A16_Snorm, 8 },
		{ TextureFormat::R16G16B16A16_Sint, 8 },
		{ TextureFormat::R32G32_Float, 8 },
		{ TextureFormat::R32G32_Uint, 8 },
		{ TextureFormat::R32G32_Sint, 8 },
		{ TextureFormat::D32_Float_S8X24_Uint, 8 },
		{ TextureFormat::R8G8B8A8_Unorm, 4 },
		{ TextureFormat::R8G8B8A8_Uint, 4 },
		{ TextureFormat::R8G8B8A8_Snorm, 4 },
		{ TextureFormat::R8G8B8A8_Sint, 4 },
		{ TextureFormat::R16G16_Float, 4 },
		{ TextureFormat::R16G16_Unorm, 4 },
		{ TextureFormat::R16G16_Uint, 4 },
		{ TextureFormat::R16G16_Snorm, 4 },
		{ TextureFormat::R16G16_Sint, 4 },
		{ TextureFormat::D32_Float, 4 },
		{ TextureFormat::R32_Float, 4 },
		{ TextureFormat::R32_Uint, 4 },
		{ TextureFormat::R32_Sint, 4 },
		{ TextureFormat::D24_Unorm_S8_Uint, 4 },
		{ TextureFormat::R8G8_Unorm, 2 },
		{ TextureFormat::R8G8_Uint, 2 },
		{ TextureFormat::R8G8_Snorm, 2 },
		{ TextureFormat::R8G8_Sint, 2 },
		{ TextureFormat::R16_Float, 2 },
		{ TextureFormat::D16_Unorm, 2 },
		{ TextureFormat::R16_Unorm, 2 },
		{ TextureFormat::R16_Uint, 2 },
		{ TextureFormat::R16_Snorm, 2 },
		{ TextureFormat::R16_Sint, 2 },
		{ TextureFormat::R8_Unorm, 1 },
		{ TextureFormat::R8_Uint, 1 },
		{ TextureFormat::R8_Snorm, 1 },
		{ TextureFormat::R8_Sint, 1 },
		{ TextureFormat::A8_Unorm, 1 },
		{ TextureFormat::R1_Unorm, 1 },
		{ TextureFormat::B8G8R8A8_Unorm, 4 },
		{ TextureFormat::B8G8R8X8_Unorm, 4 }
	};

	/// @brief Pixel data types.
	const std::unordered_map<TextureFormat, PixelDataType> PixelTypes
	{
	   { TextureFormat::R32G32B32A32_Float, PixelDataType::Float },
	   { TextureFormat::R32G32B32A32_Uint, PixelDataType::Uint },
	   { TextureFormat::R32G32B32A32_Sint, PixelDataType::Sint },
	   { TextureFormat::R32G32B32_Float, PixelDataType::Float },
	   { TextureFormat::R32G32B32_Uint, PixelDataType::Uint },
	   { TextureFormat::R32G32B32_Sint, PixelDataType::Sint },
	   { TextureFormat::R16G16B16A16_Float, PixelDataType::Float },
	   { TextureFormat::R16G16B16A16_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R16G16B16A16_Uint, PixelDataType::Uint },
	   { TextureFormat::R16G16B16A16_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R16G16B16A16_Sint, PixelDataType::Sint },
	   { TextureFormat::R32G32_Float, PixelDataType::Float },
	   { TextureFormat::R32G32_Uint, PixelDataType::Uint },
	   { TextureFormat::R32G32_Sint, PixelDataType::Sint },
	   { TextureFormat::R8G8B8A8_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R8G8B8A8_Uint, PixelDataType::Uint },
	   { TextureFormat::R8G8B8A8_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R8G8B8A8_Sint, PixelDataType::Sint },
	   { TextureFormat::R16G16_Float, PixelDataType::Float },
	   { TextureFormat::R16G16_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R16G16_Uint, PixelDataType::Uint },
	   { TextureFormat::R16G16_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R16G16_Sint, PixelDataType::Sint },
	   { TextureFormat::R32_Float, PixelDataType::Float },
	   { TextureFormat::R32_Uint, PixelDataType::Uint },
	   { TextureFormat::R32_Sint, PixelDataType::Sint },
	   { TextureFormat::R8G8_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R8G8_Uint, PixelDataType::Uint },
	   { TextureFormat::R8G8_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R8G8_Sint, PixelDataType::Sint },
	   { TextureFormat::R16_Float, PixelDataType::Float },
	   { TextureFormat::R16_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R16_Uint, PixelDataType::Uint },
	   { TextureFormat::R16_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R16_Sint, PixelDataType::Sint },
	   { TextureFormat::R8_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R8_Uint, PixelDataType::Uint },
	   { TextureFormat::R8_Snorm, PixelDataType::Snorm },
	   { TextureFormat::R8_Sint, PixelDataType::Sint },
	   { TextureFormat::A8_Unorm, PixelDataType::Unorm },
	   { TextureFormat::R1_Unorm, PixelDataType::Unorm },
	   { TextureFormat::B8G8R8A8_Unorm, PixelDataType::Unorm },
	   { TextureFormat::B8G8R8X8_Unorm, PixelDataType::Unorm }
	};

	/// @brief Depth stencil formats.
	const std::unordered_set<TextureFormat> DepthStencilFormats
	{
		TextureFormat::D32_Float_S8X24_Uint,
		TextureFormat::D32_Float,
		TextureFormat::D24_Unorm_S8_Uint,
		TextureFormat::D16_Unorm
	};

	/// @brief Compressed formats.
	const std::unordered_set<TextureFormat> CompressedFormats
	{
		TextureFormat::BC1_Unorm,
		TextureFormat::BC2_Unorm,
		TextureFormat::BC3_Unorm,
		TextureFormat::BC4_Unorm,
		TextureFormat::BC4_Snorm,
		TextureFormat::BC5_Unorm,
		TextureFormat::BC5_Snorm,
		TextureFormat::BC6H_UF16,
		TextureFormat::BC6H_SF16,
		TextureFormat::BC7_Unorm
	};

	std::uint32_t PixelSize(const TextureFormat format) noexcept
	{
		if (const auto position = PixelSizes.find(format); position != PixelSizes.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Invalid texture format.");

		return 1u;
	}

	PixelDataType PixelType(const TextureFormat format) noexcept
	{
		if (const auto position = PixelTypes.find(format); position != PixelTypes.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Invalid texture format.");

		return PixelDataType::Unknown;
	}

	bool IsColor(const TextureFormat format) noexcept
	{
		return !DepthStencilFormats.contains(format);
	}

	bool IsDepthStencil(const TextureFormat format) noexcept
	{
		return DepthStencilFormats.contains(format);
	}

	bool IsCompressed(const TextureFormat format) noexcept
	{
		return CompressedFormats.contains(format);
	}

	template <std::floating_point T>
	PonyMath::Color::RGBA<T> GetPixelColor(const std::byte* const data, const TextureFormat format) noexcept
	{
		auto answer = PonyMath::Color::RGBA<T>::Predefined::Black;
		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
		case TextureFormat::R32G32B32A32_Uint:
		case TextureFormat::R32G32B32A32_Sint:
		case TextureFormat::R16G16B16A16_Float:
		case TextureFormat::R16G16B16A16_Uint:
		case TextureFormat::R16G16B16A16_Sint:
		case TextureFormat::R8G8B8A8_Uint:
		case TextureFormat::R8G8B8A8_Sint:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format));
			break;
		case TextureFormat::R32G32B32_Float:
		case TextureFormat::R32G32B32_Uint:
		case TextureFormat::R32G32B32_Sint:
		case TextureFormat::R32G32_Float:
		case TextureFormat::R32G32_Uint:
		case TextureFormat::R32G32_Sint:
		case TextureFormat::R16G16_Float:
		case TextureFormat::R16G16_Uint:
		case TextureFormat::R16G16_Sint:
		case TextureFormat::R32_Float:
		case TextureFormat::R32_Uint:
		case TextureFormat::R32_Sint:
		case TextureFormat::R8G8_Uint:
		case TextureFormat::R8G8_Sint:
		case TextureFormat::R16_Float:
		case TextureFormat::R16_Uint:
		case TextureFormat::R16_Sint:
		case TextureFormat::R8_Uint:
		case TextureFormat::R8_Sint:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format));
			answer.A() = 1.f;
			break;
		case TextureFormat::R16G16B16A16_Unorm:
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16_Unorm:
			answer = static_cast<PonyMath::Color::RGBA<T>>(GetPixelColor<std::uint16_t>(data, format));
			break;
		case TextureFormat::R16G16B16A16_Snorm:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format)) * (T{1} / std::numeric_limits<std::int16_t>::max());
			answer = PonyMath::Color::Clamp(answer, PonyMath::Color::RGBA<T>(-1.f, -1.f, -1.f, -1.f), PonyMath::Color::RGBA<T>(1.f, 1.f, 1.f, 1.f));
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8_Unorm:
		case TextureFormat::A8_Unorm:
		case TextureFormat::B8G8R8A8_Unorm:
		case TextureFormat::B8G8R8X8_Unorm:
			answer = static_cast<PonyMath::Color::RGBA<T>>(GetPixelColor<std::uint8_t>(data, format));
			break;
		case TextureFormat::R8G8B8A8_Snorm:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format)) * (T{1} / std::numeric_limits<std::int8_t>::max());
			answer = PonyMath::Color::Clamp(answer, PonyMath::Color::RGBA<T>(-1.f, -1.f, -1.f, -1.f), PonyMath::Color::RGBA<T>(1.f, 1.f, 1.f, 1.f));
			break;
		case TextureFormat::R16G16_Snorm:
		case TextureFormat::R16_Snorm:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format)) * (T{1} / std::numeric_limits<std::int16_t>::max());
			answer = PonyMath::Color::Clamp(answer, PonyMath::Color::RGBA<T>(-1.f, -1.f, -1.f, -1.f), PonyMath::Color::RGBA<T>(1.f, 1.f, 1.f, 1.f));
			answer.A() = 1.f;
			break;
		case TextureFormat::R8G8_Snorm:
		case TextureFormat::R8_Snorm:
			answer = PonyMath::Color::RGBA<T>(GetPixelColorData<T>(data, format)) * (T{1} / std::numeric_limits<std::int8_t>::max());
			answer = PonyMath::Color::Clamp(answer, PonyMath::Color::RGBA<T>(-1.f, -1.f, -1.f, -1.f), PonyMath::Color::RGBA<T>(1.f, 1.f, 1.f, 1.f));
			answer.A() = 1.f;
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}

		return answer;
	}

	template <std::unsigned_integral T>
	PonyMath::Color::RGBAInt<T> GetPixelColor(const std::byte* const data, const TextureFormat format) noexcept
	{
		auto answer = PonyMath::Color::RGBAInt<T>::Predefined::Black;

		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
		case TextureFormat::R32G32B32_Float:
		case TextureFormat::R16G16B16A16_Float:
		case TextureFormat::R32G32_Float:
		case TextureFormat::R16G16_Float:
		case TextureFormat::R32_Float:
		case TextureFormat::R16_Float:
			answer = static_cast<PonyMath::Color::RGBAInt<T>>(GetPixelColor<float>(data, format));
			break;
		case TextureFormat::R16G16B16A16_Unorm:
			answer = static_cast<PonyMath::Color::RGBAInt<T>>(PonyMath::Color::RGBAInt(GetPixelColorData<std::uint16_t>(data, format)));
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::A8_Unorm:
		case TextureFormat::B8G8R8A8_Unorm:
			answer = static_cast<PonyMath::Color::RGBAInt<T>>(PonyMath::Color::RGBAInt(GetPixelColorData<std::uint8_t>(data, format)));
			break;
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16_Unorm:
			answer = static_cast<PonyMath::Color::RGBAInt<T>>(PonyMath::Color::RGBAInt(GetPixelColorData<std::uint16_t>(data, format)));
			answer.A() = std::numeric_limits<T>::max();
			break;
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8_Unorm:
		case TextureFormat::B8G8R8X8_Unorm:
			answer = static_cast<PonyMath::Color::RGBAInt<T>>(PonyMath::Color::RGBAInt(GetPixelColorData<std::uint8_t>(data, format)));
			answer.A() = std::numeric_limits<T>::max();
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}

		return answer;
	}

	template <PonyMath::Core::Arithmetic T>
	PonyMath::Core::Vector4<T> GetPixelColorData(const std::byte* const data, const TextureFormat format) noexcept
	{
		auto answer = PonyMath::Core::Vector4<T>::Predefined::Zero;
		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
			answer.W() = static_cast<T>(reinterpret_cast<const float*>(data)[3]);
		case TextureFormat::R32G32B32_Float:
			answer.Z() = static_cast<T>(reinterpret_cast<const float*>(data)[2]);
		case TextureFormat::R32G32_Float:
			answer.Y() = static_cast<T>(reinterpret_cast<const float*>(data)[1]);
		case TextureFormat::R32_Float:
			answer.X() = static_cast<T>(reinterpret_cast<const float*>(data)[0]);
			break;
		case TextureFormat::R32G32B32A32_Uint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::uint32_t*>(data)[3]);
		case TextureFormat::R32G32B32_Uint:
			answer.Z() = static_cast<T>(reinterpret_cast<const std::uint32_t*>(data)[2]);
		case TextureFormat::R32G32_Uint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::uint32_t*>(data)[1]);
		case TextureFormat::R32_Uint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::uint32_t*>(data)[0]);
			break;
		case TextureFormat::R32G32B32A32_Sint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::int32_t*>(data)[3]);
		case TextureFormat::R32G32B32_Sint:
			answer.Z() = static_cast<T>(reinterpret_cast<const std::int32_t*>(data)[2]);
		case TextureFormat::R32G32_Sint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::int32_t*>(data)[1]);
		case TextureFormat::R32_Sint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::int32_t*>(data)[0]);
			break;
		case TextureFormat::R16G16B16A16_Float:
			answer.W() = static_cast<T>(PonyBase::Core::ToFloat32(reinterpret_cast<const std::uint16_t*>(data)[3]));
			answer.Z() = static_cast<T>(PonyBase::Core::ToFloat32(reinterpret_cast<const std::uint16_t*>(data)[2]));
		case TextureFormat::R16G16_Float:
			answer.Y() = static_cast<T>(PonyBase::Core::ToFloat32(reinterpret_cast<const std::uint16_t*>(data)[1]));
		case TextureFormat::R16_Float:
			answer.X() = static_cast<T>(PonyBase::Core::ToFloat32(reinterpret_cast<const std::uint16_t*>(data)[0]));
			break;
		case TextureFormat::R16G16B16A16_Unorm:
		case TextureFormat::R16G16B16A16_Uint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::uint16_t*>(data)[3]);
			answer.Z() = static_cast<T>(reinterpret_cast<const std::uint16_t*>(data)[2]);
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16G16_Uint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::uint16_t*>(data)[1]);
		case TextureFormat::R16_Unorm:
		case TextureFormat::R16_Uint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::uint16_t*>(data)[0]);
			break;
		case TextureFormat::R16G16B16A16_Snorm:
		case TextureFormat::R16G16B16A16_Sint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::int16_t*>(data)[3]);
			answer.Z() = static_cast<T>(reinterpret_cast<const std::int16_t*>(data)[2]);
		case TextureFormat::R16G16_Snorm:
		case TextureFormat::R16G16_Sint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::int16_t*>(data)[1]);
		case TextureFormat::R16_Snorm:
		case TextureFormat::R16_Sint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::int16_t*>(data)[0]);
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::R8G8B8A8_Uint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[3]);
			answer.Z() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[2]);
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8G8_Uint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[1]);
		case TextureFormat::R8_Unorm:
		case TextureFormat::R8_Uint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[0]);
			break;
		case TextureFormat::R8G8B8A8_Snorm:
		case TextureFormat::R8G8B8A8_Sint:
			answer.W() = static_cast<T>(reinterpret_cast<const std::int8_t*>(data)[3]);
			answer.Z() = static_cast<T>(reinterpret_cast<const std::int8_t*>(data)[2]);
		case TextureFormat::R8G8_Snorm:
		case TextureFormat::R8G8_Sint:
			answer.Y() = static_cast<T>(reinterpret_cast<const std::int8_t*>(data)[1]);
		case TextureFormat::R8_Snorm:
		case TextureFormat::R8_Sint:
			answer.X() = static_cast<T>(reinterpret_cast<const std::int8_t*>(data)[0]);
			break;
		case TextureFormat::A8_Unorm:
			answer.W() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[0]);
			break;
		case TextureFormat::B8G8R8A8_Unorm:
			answer.W() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[3]);
		case TextureFormat::B8G8R8X8_Unorm:
			answer.X() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[2]);
			answer.Y() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[1]);
			answer.Z() = static_cast<T>(reinterpret_cast<const std::uint8_t*>(data)[0]);
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}

		return answer;
	}

	std::pair<float, std::uint8_t> GetPixelDepthStencil(const std::byte* const data, const TextureFormat format) noexcept
	{
		auto answer = std::pair<float, std::uint8_t>(0.f, 0u);

		switch (format)
		{
		case TextureFormat::D32_Float_S8X24_Uint:
			answer.second = reinterpret_cast<const std::uint8_t*>(data)[4];
		case TextureFormat::D32_Float:
			answer.first = reinterpret_cast<const float*>(data)[0];
			break;
		case TextureFormat::D24_Unorm_S8_Uint:
			answer.first = static_cast<float>(reinterpret_cast<const std::uint32_t*>(data)[0]) / 0xFFFFFF;
			answer.second = reinterpret_cast<const std::uint8_t*>(data)[3];
			break;
		case TextureFormat::D16_Unorm:
			answer.first = static_cast<float>(reinterpret_cast<const std::uint16_t*>(data)[0]) / 0xFFFF;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}

		return answer;
	}

	template <std::floating_point T>
	void SetPixelColor(const PonyMath::Color::RGBA<T>& color, std::byte* const data, const TextureFormat format) noexcept
	{
		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
		case TextureFormat::R32G32B32A32_Uint:
		case TextureFormat::R32G32B32A32_Sint:
		case TextureFormat::R16G16B16A16_Float:
		case TextureFormat::R16G16B16A16_Uint:
		case TextureFormat::R16G16B16A16_Sint:
		case TextureFormat::R8G8B8A8_Uint:
		case TextureFormat::R8G8B8A8_Sint:
		case TextureFormat::R32G32B32_Float:
		case TextureFormat::R32G32B32_Uint:
		case TextureFormat::R32G32B32_Sint:
		case TextureFormat::R32G32_Float:
		case TextureFormat::R32G32_Uint:
		case TextureFormat::R32G32_Sint:
		case TextureFormat::R16G16_Float:
		case TextureFormat::R16G16_Uint:
		case TextureFormat::R16G16_Sint:
		case TextureFormat::R32_Float:
		case TextureFormat::R32_Uint:
		case TextureFormat::R32_Sint:
		case TextureFormat::R8G8_Uint:
		case TextureFormat::R8G8_Sint:
		case TextureFormat::R16_Float:
		case TextureFormat::R16_Uint:
		case TextureFormat::R16_Sint:
		case TextureFormat::R8_Uint:
		case TextureFormat::R8_Sint:
			SetPixelColorData(static_cast<PonyMath::Core::Vector4<T>>(color), data, format);
			break;
		case TextureFormat::R16G16B16A16_Unorm:
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16_Unorm:
			SetPixelColor(static_cast<PonyMath::Color::RGBAInt<std::uint16_t>>(color), data, format);
			break;
		case TextureFormat::R16G16B16A16_Snorm:
		case TextureFormat::R16G16_Snorm:
		case TextureFormat::R16_Snorm:
			SetPixelColorData(static_cast<PonyMath::Core::Vector4<std::int16_t>>(static_cast<PonyMath::Core::Vector4<T>>(color * -std::numeric_limits<std::int16_t>::min())), data, format);
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8_Unorm:
		case TextureFormat::A8_Unorm:
		case TextureFormat::B8G8R8A8_Unorm:
		case TextureFormat::B8G8R8X8_Unorm:
			SetPixelColor(static_cast<PonyMath::Color::RGBAInt<std::uint8_t>>(color), data, format);
			break;
		case TextureFormat::R8G8B8A8_Snorm:
			SetPixelColorData(static_cast<PonyMath::Core::Vector4<std::int16_t>>(static_cast<PonyMath::Core::Vector4<T>>(color * -std::numeric_limits<std::int8_t>::min())), data, format);
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}
	}

	template <std::unsigned_integral T>
	void SetPixelColor(const PonyMath::Color::RGBAInt<T>& color, std::byte* const data, const TextureFormat format) noexcept
	{
		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
		case TextureFormat::R32G32B32_Float:
		case TextureFormat::R16G16B16A16_Float:
		case TextureFormat::R32G32_Float:
		case TextureFormat::R16G16_Float:
		case TextureFormat::R32_Float:
		case TextureFormat::R16_Float:
			SetPixelColor(static_cast<PonyMath::Color::RGBA<float>>(color), data, format);
			break;
		case TextureFormat::R16G16B16A16_Unorm:
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16_Unorm:
			SetPixelColorData(static_cast<PonyMath::Core::Vector4<std::uint16_t>>(static_cast<PonyMath::Color::RGBAInt<std::uint16_t>>(color)), data, format);
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::A8_Unorm:
		case TextureFormat::B8G8R8A8_Unorm:
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8_Unorm:
		case TextureFormat::B8G8R8X8_Unorm:
			SetPixelColorData(static_cast<PonyMath::Core::Vector4<std::uint8_t>>(static_cast<PonyMath::Color::RGBAInt<std::uint8_t>>(color)), data, format);
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}
	}

	template <PonyMath::Core::Arithmetic T>
	void SetPixelColorData(const PonyMath::Core::Vector4<T>& color, std::byte* const data, const TextureFormat format) noexcept
	{
		switch (format)
		{
		case TextureFormat::R32G32B32A32_Float:
			reinterpret_cast<float*>(data)[3] = static_cast<float>(color.W());
		case TextureFormat::R32G32B32_Float:
			reinterpret_cast<float*>(data)[2] = static_cast<float>(color.Z());
		case TextureFormat::R32G32_Float:
			reinterpret_cast<float*>(data)[1] = static_cast<float>(color.Y());
		case TextureFormat::R32_Float:
			reinterpret_cast<float*>(data)[0] = static_cast<float>(color.X());
			break;
		case TextureFormat::R32G32B32A32_Uint:
			reinterpret_cast<std::uint32_t*>(data)[3] = static_cast<std::uint32_t>(color.W());
		case TextureFormat::R32G32B32_Uint:
			reinterpret_cast<std::uint32_t*>(data)[2] = static_cast<std::uint32_t>(color.Z());
		case TextureFormat::R32G32_Uint:
			reinterpret_cast<std::uint32_t*>(data)[1] = static_cast<std::uint32_t>(color.Y());
		case TextureFormat::R32_Uint:
			reinterpret_cast<std::uint32_t*>(data)[0] = static_cast<std::uint32_t>(color.X());
			break;
		case TextureFormat::R32G32B32A32_Sint:
			reinterpret_cast<std::int32_t*>(data)[3] = static_cast<std::int32_t>(color.W());
		case TextureFormat::R32G32B32_Sint:
			reinterpret_cast<std::int32_t*>(data)[2] = static_cast<std::int32_t>(color.Z());
		case TextureFormat::R32G32_Sint:
			reinterpret_cast<std::int32_t*>(data)[1] = static_cast<std::int32_t>(color.Y());
		case TextureFormat::R32_Sint:
			reinterpret_cast<std::int32_t*>(data)[0] = static_cast<std::int32_t>(color.X());
			break;
		case TextureFormat::R16G16B16A16_Float:
			reinterpret_cast<std::uint16_t*>(data)[3] = PonyBase::Core::ToFloat16(color.W());
			reinterpret_cast<std::uint16_t*>(data)[2] = PonyBase::Core::ToFloat16(color.Z());
		case TextureFormat::R16G16_Float:
			reinterpret_cast<std::uint16_t*>(data)[1] = PonyBase::Core::ToFloat16(color.Y());
		case TextureFormat::R16_Float:
			reinterpret_cast<std::uint16_t*>(data)[0] = PonyBase::Core::ToFloat16(color.X());
			break;
		case TextureFormat::R16G16B16A16_Unorm:
		case TextureFormat::R16G16B16A16_Uint:
			reinterpret_cast<std::uint16_t*>(data)[3] = static_cast<std::uint16_t>(color.W());
			reinterpret_cast<std::uint16_t*>(data)[2] = static_cast<std::uint16_t>(color.Z());
		case TextureFormat::R16G16_Unorm:
		case TextureFormat::R16G16_Uint:
			reinterpret_cast<std::uint16_t*>(data)[1] = static_cast<std::uint16_t>(color.Y());
		case TextureFormat::R16_Unorm:
		case TextureFormat::R16_Uint:
			reinterpret_cast<std::uint16_t*>(data)[0] = static_cast<std::uint16_t>(color.X());
			break;
		case TextureFormat::R16G16B16A16_Snorm:
		case TextureFormat::R16G16B16A16_Sint:
			reinterpret_cast<std::int16_t*>(data)[3] = static_cast<std::int16_t>(color.W());
			reinterpret_cast<std::int16_t*>(data)[2] = static_cast<std::int16_t>(color.Z());
		case TextureFormat::R16G16_Snorm:
		case TextureFormat::R16G16_Sint:
			reinterpret_cast<std::int16_t*>(data)[1] = static_cast<std::int16_t>(color.Y());
		case TextureFormat::R16_Snorm:
		case TextureFormat::R16_Sint:
			reinterpret_cast<std::int16_t*>(data)[0] = static_cast<std::int16_t>(color.X());
			break;
		case TextureFormat::R8G8B8A8_Unorm:
		case TextureFormat::R8G8B8A8_Uint:
			reinterpret_cast<std::uint8_t*>(data)[3] = static_cast<std::uint8_t>(color.W());
			reinterpret_cast<std::uint8_t*>(data)[2] = static_cast<std::uint8_t>(color.Z());
		case TextureFormat::R8G8_Unorm:
		case TextureFormat::R8G8_Uint:
			reinterpret_cast<std::uint8_t*>(data)[1] = static_cast<std::uint8_t>(color.Y());
		case TextureFormat::R8_Unorm:
		case TextureFormat::R8_Uint:
			reinterpret_cast<std::uint8_t*>(data)[0] = static_cast<std::uint8_t>(color.X());
			break;
		case TextureFormat::R8G8B8A8_Snorm:
		case TextureFormat::R8G8B8A8_Sint:
			reinterpret_cast<std::int8_t*>(data)[3] = static_cast<std::int8_t>(color.W());
			reinterpret_cast<std::int8_t*>(data)[2] = static_cast<std::int8_t>(color.Z());
		case TextureFormat::R8G8_Snorm:
		case TextureFormat::R8G8_Sint:
			reinterpret_cast<std::int8_t*>(data)[1] = static_cast<std::int8_t>(color.Y());
		case TextureFormat::R8_Snorm:
		case TextureFormat::R8_Sint:
			reinterpret_cast<std::int8_t*>(data)[0] = static_cast<std::int8_t>(color.X());
			break;
		case TextureFormat::A8_Unorm:
			reinterpret_cast<std::uint8_t*>(data)[0] = static_cast<std::uint8_t>(color.W());
			break;
		case TextureFormat::B8G8R8A8_Unorm:
			reinterpret_cast<std::uint8_t*>(data)[3] = static_cast<std::uint8_t>(color.W());
		case TextureFormat::B8G8R8X8_Unorm:
			reinterpret_cast<std::uint8_t*>(data)[0] = static_cast<std::uint8_t>(color.Z());
			reinterpret_cast<std::uint8_t*>(data)[1] = static_cast<std::uint8_t>(color.Y());
			reinterpret_cast<std::uint8_t*>(data)[2] = static_cast<std::uint8_t>(color.X());
			break;
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}
	}

	void SetPixelDepthStencil(const float depth, const std::uint8_t stencil, std::byte* const data, const TextureFormat format) noexcept
	{
		switch (format)
		{
		case TextureFormat::D32_Float_S8X24_Uint:
			reinterpret_cast<std::uint8_t*>(data)[4] = stencil;
		case TextureFormat::D32_Float:
			reinterpret_cast<float*>(data)[0] = depth;
			break;
		case TextureFormat::D24_Unorm_S8_Uint:
			reinterpret_cast<std::uint32_t*>(data)[0] = static_cast<std::uint32_t>(depth * 0xFFFFFF);
			reinterpret_cast<std::uint8_t*>(data)[3] = stencil;
			break;
		case TextureFormat::D16_Unorm:
			reinterpret_cast<std::uint16_t*>(data)[0] = static_cast<std::uint16_t>(depth * 0xFFFF);
		default: [[unlikely]]
			assert(false && "Incorrect texture format.");
			break;
		}
	}
}
