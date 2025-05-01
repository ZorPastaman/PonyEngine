/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Texture1D;

import <concepts>;
import <cstddef>;
import <cstdint>;
import <cstring>;
import <span>;
import <stdexcept>;

import PonyBase.Container;
import PonyBase.Utility;

import PonyMath.Color;

import :Texture;
import :TextureDimension;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Texture 1D.
	class Texture1D final : public Texture // TODO: Add texture array and texture cube
	{
	public:
		/// @brief Creates an empty texture.
		[[nodiscard("Pure constructor")]]
		Texture1D() noexcept;
		/// @brief Creates a texture with a new buffer.
		/// @param width Texture width.
		/// @param format Texture format. Mustn't be compressed.
		[[nodiscard("Pure constructor")]]
		explicit Texture1D(std::uint32_t width, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);
		/// @brief Creates a texture with the preset buffer.
		/// @param buffer Texture data buffer. If the @p format isn't compressed, its stride must be equal the @p format pixel size and its count must be equal the @p width.
		/// @param width Texture width.
		/// @param format Texture format.
		[[nodiscard("Pure constructor")]]
		explicit Texture1D(const PonyBase::Container::Buffer& buffer, std::uint32_t width, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);
		[[nodiscard("Pure constructor")]]
		Texture1D(const Texture1D& other) = default;
		[[nodiscard("Pure constructor")]]
		Texture1D(Texture1D&& other) noexcept = default;

		virtual ~Texture1D() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual std::uint32_t Width() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t Height() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint16_t Depth() const noexcept override;

		/// @brief Gets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @return Pixel color.
		template<std::floating_point T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBA<T> GetPixelRGBA(std::uint32_t index) const noexcept;
		/// @brief Gets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param output Output.
		template<std::floating_point T>
		void GetPixelsRGBA(std::uint32_t startIndex, std::span<PonyMath::Color::RGBA<T>> output) const;
		/// @brief Gets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @return Pixel color.
		template<std::floating_point T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGB<T> GetPixelRGB(std::uint32_t index) const noexcept;
		/// @brief Gets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param output Output.
		template<std::floating_point T>
		void GetPixelsRGB(std::uint32_t startIndex, std::span<PonyMath::Color::RGB<T>> output) const;

		/// @brief Gets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @return Pixel color.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBAInt<T> GetPixelRGBA(std::uint32_t index) const noexcept;
		/// @brief Gets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param output Output.
		template<std::unsigned_integral T>
		void GetPixelsRGBA(std::uint32_t startIndex, std::span<PonyMath::Color::RGBAInt<T>> output) const;
		/// @brief Gets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @return Pixel color.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBInt<T> GetPixelRGB(std::uint32_t index) const noexcept;
		/// @brief Gets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param output Output.
		template<std::unsigned_integral T>
		void GetPixelsRGB(std::uint32_t startIndex, std::span<PonyMath::Color::RGBInt<T>> output) const;

		/// @brief Gets a pixel color data.
		/// @details It returns a color as is, without any conversion.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @return Pixel color.
		template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
		PonyMath::Core::Vector4<T> GetPixelData(std::uint32_t index) const noexcept;
		/// @brief Gets pixel color data.
		/// @details It returns a color as is, without any conversion.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param output Output.
		template<PonyMath::Core::Arithmetic T>
		void GetPixelsData(std::uint32_t startIndex, std::span<PonyMath::Core::Vector4<T>> output) const;

		/// @brief Gets a raw pixel data.
		/// @note If the texture is compressed, it works by texture blocks.
		/// @param index Pixel index.
		/// @return Raw pixel data.
		[[nodiscard("Pure function")]]
		const std::byte* GetPixelRaw(std::uint32_t index) const noexcept;
		/// @brief Gets raw pixel data.
		/// @note If the texture is compressed, it works by texture blocks.
		/// @param startIndex Pixel index.
		/// @param output Output.
		void GetPixelsRaw(std::uint32_t startIndex, std::span<std::byte> output) const;

		/// @brief Sets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @param color Color to set.
		template<std::floating_point T> [[nodiscard("Pure function")]]
		void SetPixelRGBA(std::uint32_t index, const PonyMath::Color::RGBA<T>& color) noexcept;
		/// @brief Sets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		template<std::floating_point T>
		void SetPixelsRGBA(std::uint32_t startIndex, std::span<const PonyMath::Color::RGBA<T>> input);
		/// @brief Sets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @param color Color to set.
		template<std::floating_point T> [[nodiscard("Pure function")]]
		void SetPixelRGB(std::uint32_t index, const PonyMath::Color::RGB<T>& color) noexcept;
		/// @brief Sets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		template<std::floating_point T>
		void SetPixelsRGB(std::uint32_t startIndex, std::span<const PonyMath::Color::RGB<T>> input);

		/// @brief Sets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @param color Color to set.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		void SetPixelRGBA(std::uint32_t index, const PonyMath::Color::RGBAInt<T>& color) noexcept;
		/// @brief Sets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		template<std::unsigned_integral T>
		void SetPixelsRGBA(std::uint32_t startIndex, std::span<const PonyMath::Color::RGBAInt<T>> input);
		/// @brief Sets a pixel color.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @param color Color to set.
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		void SetPixelRGB(std::uint32_t index, const PonyMath::Color::RGBInt<T>& color) noexcept;
		/// @brief Sets pixel colors.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		template<std::unsigned_integral T>
		void SetPixelsRGB(std::uint32_t startIndex, std::span<const PonyMath::Color::RGBInt<T>> input);

		/// @brief Sets a pixel color data.
		/// @details It sets a color as is, without any conversion.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param index Pixel index.
		/// @param color Color to set.
		template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
		void SetPixelData(std::uint32_t index, const PonyMath::Core::Vector4<T>& color) noexcept;
		/// @brief Sets pixel color data.
		/// @details It sets a color as is, without any conversion.
		/// @note The texture mustn't be compressed.
		/// @tparam T Color component type.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		template<PonyMath::Core::Arithmetic T>
		void SetPixelsData(std::uint32_t startIndex, std::span<const PonyMath::Core::Vector4<T>> input);

		/// @brief Sets a raw pixel data.
		/// @note If the texture is compressed, it works by texture blocks.
		/// @param index Pixel index.
		/// @param data Raw pixel data.
		void SetPixelRaw(std::uint32_t index, const std::byte* data);
		/// @brief Sets raw pixel data.
		/// @note If the texture is compressed, it works by texture blocks.
		/// @param startIndex Start pixel index.
		/// @param input Input.
		void SetPixelsRaw(std::uint32_t startIndex, std::span<const std::byte> input);

		Texture1D& operator =(const Texture1D& other) = default;
		Texture1D& operator =(Texture1D&& other) noexcept = default;

	private:
		/// @brief Creates a texture buffer.
		/// @param width Width.
		/// @param format Texture format. It mustn't be compressed.
		/// @return Texture buffer.
		[[nodiscard("Pure function")]]
		static PonyBase::Container::Buffer CreateBuffer(std::uint32_t width, TextureFormat format);
		/// @brief Validates the @p buffer.
		/// @param buffer Buffer to validate.
		/// @param width Width.
		/// @param format Texture format.
		/// @return @p buffer.
		[[nodiscard("Pure function")]]
		static const PonyBase::Container::Buffer& ValidateBuffer(const PonyBase::Container::Buffer& buffer, std::uint32_t width, TextureFormat format);

		/// @brief Gets a raw pixel data.
		/// @note If the texture is compressed, it works by texture blocks.
		/// @param index Pixel index.
		/// @return Raw pixel data.
		[[nodiscard("Pure function")]]
		std::byte* GetPixelRaw(std::uint32_t index) noexcept;

		/// @brief Validates a color span.
		/// @param startIndex Start index.
		/// @param size Span size.
		void ValidateColor(std::uint32_t startIndex, std::size_t size) const;
		/// @brief Validates a raw color span.
		/// @param startIndex Start index.
		/// @param size Span size.
		void ValidateRaw(std::uint32_t startIndex, std::size_t size) const;

		std::uint32_t width; ///< Width.
	};
}

namespace PonyEngine::Render
{
	Texture1D::Texture1D() noexcept :
		Texture(PonyBase::Container::Buffer(), TextureDimension::Texture1D, TextureFormat::R8G8B8A8_Unorm),
		width(0u)
	{
	}

	Texture1D::Texture1D(const std::uint32_t width, const TextureFormat format) :
		Texture(CreateBuffer(width, format), TextureDimension::Texture1D, format),
		width(width)
	{
	}

	Texture1D::Texture1D(const PonyBase::Container::Buffer& buffer, const std::uint32_t width, const TextureFormat format) :
		Texture(ValidateBuffer(buffer, width, format), TextureDimension::Texture1D, format),
		width(width)
	{
	}

	std::uint32_t Texture1D::Width() const noexcept
	{
		return width;
	}

	std::uint32_t Texture1D::Height() const noexcept
	{
		return 1u;
	}

	std::uint16_t Texture1D::Depth() const noexcept
	{
		return 1u;
	}

	template <std::floating_point T>
	PonyMath::Color::RGBA<T> Texture1D::GetPixelRGBA(const std::uint32_t index) const noexcept
	{
		return GetPixelColor<T>(GetPixelRaw(index), format);
	}

	template <std::floating_point T>
	void Texture1D::GetPixelsRGBA(const std::uint32_t startIndex, const std::span<PonyMath::Color::RGBA<T>> output) const
	{
		ValidateColor(startIndex, output.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(output.size()); ++i)
		{
			output[i] = GetPixelRGBA<T>(startIndex + i);
		}
	}

	template <std::floating_point T>
	PonyMath::Color::RGB<T> Texture1D::GetPixelRGB(const std::uint32_t index) const noexcept
	{
		return static_cast<PonyMath::Color::RGB<T>>(GetPixelRGBA<T>(index));
	}

	template <std::floating_point T>
	void Texture1D::GetPixelsRGB(const std::uint32_t startIndex, const std::span<PonyMath::Color::RGB<T>> output) const
	{
		ValidateColor(startIndex, output.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(output.size()); ++i)
		{
			output[i] = GetPixelRGB<T>(startIndex + i);
		}
	}

	template <std::unsigned_integral T>
	PonyMath::Color::RGBAInt<T> Texture1D::GetPixelRGBA(const std::uint32_t index) const noexcept
	{
		return Render::GetPixelColor<T>(GetPixelRaw(index), format);
	}

	template <std::unsigned_integral T>
	void Texture1D::GetPixelsRGBA(const std::uint32_t startIndex, const std::span<PonyMath::Color::RGBAInt<T>> output) const
	{
		ValidateColor(startIndex, output.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(output.size()); ++i)
		{
			output[i] = GetPixelRGBA<T>(startIndex + i);
		}
	}

	template <std::unsigned_integral T>
	PonyMath::Color::RGBInt<T> Texture1D::GetPixelRGB(const std::uint32_t index) const noexcept
	{
		return static_cast<PonyMath::Color::RGBInt<T>>(GetPixelRGBA<T>(index));
	}

	template <std::unsigned_integral T>
	void Texture1D::GetPixelsRGB(const std::uint32_t startIndex, const std::span<PonyMath::Color::RGBInt<T>> output) const
	{
		ValidateColor(startIndex, output.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(output.size()); ++i)
		{
			output[i] = GetPixelRGB<T>(startIndex + i);
		}
	}

	template <PonyMath::Core::Arithmetic T>
	PonyMath::Core::Vector4<T> Texture1D::GetPixelData(const std::uint32_t index) const noexcept
	{
		return Render::GetPixelColorData<T>(GetPixelRaw(index), format);
	}

	template <PonyMath::Core::Arithmetic T>
	void Texture1D::GetPixelsData(const std::uint32_t startIndex, const std::span<PonyMath::Core::Vector4<T>> output) const
	{
		ValidateColor(startIndex, output.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(output.size()); ++i)
		{
			output[i] = GetPixelData<T>(startIndex + i);
		}
	}

	const std::byte* Texture1D::GetPixelRaw(const std::uint32_t index) const noexcept
	{
		return data.Data() + index * BlockSize();
	}

	void Texture1D::GetPixelsRaw(const std::uint32_t startIndex, const std::span<std::byte> output) const
	{
		ValidateRaw(startIndex, output.size());

		std::memcpy(output.data(), GetPixelRaw(startIndex), output.size());
	}

	template <std::floating_point T>
	void Texture1D::SetPixelRGBA(const std::uint32_t index, const PonyMath::Color::RGBA<T>& color) noexcept
	{
		SetPixelColor(color, GetPixelRaw(index), format);

		OnTextureChanged();
	}

	template <std::floating_point T>
	void Texture1D::SetPixelsRGBA(const std::uint32_t startIndex, const std::span<const PonyMath::Color::RGBA<T>> input)
	{
		ValidateColor(startIndex, input.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(input.size()); ++i)
		{
			SetPixelColor(input[i], GetPixelRaw(startIndex + i), format);
		}

		OnTextureChanged();
	}

	template <std::floating_point T>
	void Texture1D::SetPixelRGB(const std::uint32_t index, const PonyMath::Color::RGB<T>& color) noexcept
	{
		SetPixelRGBA(index, PonyMath::Color::RGBA<T>(color, T{1}));
	}

	template <std::floating_point T>
	void Texture1D::SetPixelsRGB(const std::uint32_t startIndex, const std::span<const PonyMath::Color::RGB<T>> input)
	{
		ValidateColor(startIndex, input.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(input.size()); ++i)
		{
			SetPixelColor(PonyMath::Color::RGBA<T>(input, T{1}), GetPixelRaw(startIndex + 1), format);
		}

		OnTextureChanged();
	}

	template <std::unsigned_integral T>
	void Texture1D::SetPixelRGBA(const std::uint32_t index, const PonyMath::Color::RGBAInt<T>& color) noexcept
	{
		SetPixelColor(color, GetPixelRaw(index), format);

		OnTextureChanged();
	}

	template <std::unsigned_integral T>
	void Texture1D::SetPixelsRGBA(const std::uint32_t startIndex, const std::span<const PonyMath::Color::RGBAInt<T>> input)
	{
		ValidateColor(startIndex, input.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(input.size()); ++i)
		{
			SetPixelColor(input[i], GetPixelRaw(startIndex + i), format);
		}

		OnTextureChanged();
	}

	template <std::unsigned_integral T>
	void Texture1D::SetPixelRGB(const std::uint32_t index, const PonyMath::Color::RGBInt<T>& color) noexcept
	{
		SetPixelRGBA(index, PonyMath::Color::RGBAInt<T>(color, PonyMath::Color::RGBAInt<T>::MaxValue));
	}

	template <std::unsigned_integral T>
	void Texture1D::SetPixelsRGB(const std::uint32_t startIndex, const std::span<const PonyMath::Color::RGBInt<T>> input)
	{
		ValidateColor(startIndex, input.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(input.size()); ++i)
		{
			SetPixelColor(PonyMath::Color::RGBInt<T>(input[i], PonyMath::Color::RGBInt<T>::MaxValue), GetPixelRaw(startIndex + 1), format);
		}

		OnTextureChanged();
	}

	template <PonyMath::Core::Arithmetic T>
	void Texture1D::SetPixelData(const std::uint32_t index, const PonyMath::Core::Vector4<T>& color) noexcept
	{
		SetPixelColorData(color, GetPixelRaw(index), format);

		OnTextureChanged();
	}

	template <PonyMath::Core::Arithmetic T>
	void Texture1D::SetPixelsData(const std::uint32_t startIndex, std::span<const PonyMath::Core::Vector4<T>> input)
	{
		ValidateColor(startIndex, input.size());

		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(input.size()); ++i)
		{
			SetPixelData(startIndex + i, input[i]);
		}

		OnTextureChanged();
	}

	void Texture1D::SetPixelRaw(const std::uint32_t index, const std::byte* const data)
	{
		std::memcpy(GetPixelRaw(index), data, BlockSize());

		OnTextureChanged();
	}

	void Texture1D::SetPixelsRaw(const std::uint32_t startIndex, const std::span<const std::byte> input)
	{
		ValidateRaw(startIndex, input.size());

		std::memcpy(GetPixelRaw(startIndex), input.data(), input.size());

		OnTextureChanged();
	}

	PonyBase::Container::Buffer Texture1D::CreateBuffer(const std::uint32_t width, const TextureFormat format)
	{
		if (IsCompressed(format)) [[unlikely]]
		{
			throw std::invalid_argument("Format is compressed.");
		}

		return PonyBase::Container::Buffer(PixelSize(format), width);
	}

	const PonyBase::Container::Buffer& Texture1D::ValidateBuffer(const PonyBase::Container::Buffer& buffer, const std::uint32_t width, const TextureFormat format)
	{
		if (IsCompressed(format))
		{
			return buffer;
		}

		if (buffer.Stride() != PixelSize(format) || buffer.Count() != width) [[unlikely]]
		{
			throw std::invalid_argument("Buffer is not compatible with width and format.");
		}

		return buffer;
	}

	std::byte* Texture1D::GetPixelRaw(const std::uint32_t index) noexcept
	{
		return data.Data() + index * BlockSize();
	}

	void Texture1D::ValidateColor(const std::uint32_t startIndex, const std::size_t size) const
	{
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (size > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Input is too large.");
		}
	}

	void Texture1D::ValidateRaw(const std::uint32_t startIndex, const std::size_t size) const
	{
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (size % BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Output is invalid size.");
		}
		if (size > Size() - startIndex * BlockSize()) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}
	}
}
