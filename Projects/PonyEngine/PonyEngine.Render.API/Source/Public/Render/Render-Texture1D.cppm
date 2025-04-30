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
	class Texture1D final : public Texture // TODO: Add texture array and texture cube
	{
	public:
		[[nodiscard("Pure constructor")]]
		Texture1D() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit Texture1D(std::uint32_t width, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);
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

		template<std::floating_point T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBA<T> GetPixelRGBA(std::uint32_t index) const noexcept;
		template<std::floating_point T>
		void GetPixelsRGBA(std::uint32_t startIndex, std::span<PonyMath::Color::RGBA<T>> output) const;
		template<std::floating_point T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGB<T> GetPixelRGB(std::uint32_t index) const noexcept;
		template<std::floating_point T>
		void GetPixelsRGB(std::uint32_t startIndex, std::span<PonyMath::Color::RGB<T>> output) const;

		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBAInt<T> GetPixelRGBA(std::uint32_t index) const noexcept;
		template<std::unsigned_integral T>
		void GetPixelsRGBA(std::uint32_t startIndex, std::span<PonyMath::Color::RGBAInt<T>> output) const;
		template<std::unsigned_integral T> [[nodiscard("Pure function")]]
		PonyMath::Color::RGBInt<T> GetPixelRGB(std::uint32_t index) const noexcept;
		template<std::unsigned_integral T>
		void GetPixelsRGB(std::uint32_t startIndex, std::span<PonyMath::Color::RGBInt<T>> output) const;

		template<PonyMath::Core::Arithmetic T> [[nodiscard("Pure function")]]
		PonyMath::Core::Vector4<T> GetPixelData(std::uint32_t index) const noexcept;
		template<PonyMath::Core::Arithmetic T>
		void GetPixelsData(std::uint32_t startIndex, std::span<PonyMath::Core::Vector4<T>> output) const;

		[[nodiscard("Pure function")]]
		const std::byte* GetPixelRaw(std::uint32_t index) const noexcept;
		void GetPixelsRaw(std::uint32_t startIndex, std::span<std::byte> output) const;

		Texture1D& operator =(const Texture1D& other) = default;
		Texture1D& operator =(Texture1D&& other) noexcept = default;

	private:
		[[nodiscard("Pure function")]]
		static PonyBase::Container::Buffer CreateBuffer(std::uint32_t width, TextureFormat format);
		[[nodiscard("Pure function")]]
		static const PonyBase::Container::Buffer& ValidateBuffer(const PonyBase::Container::Buffer& buffer, std::uint32_t width, TextureFormat format);

		std::uint32_t width;
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		for (std::size_t i = 0; i < output.size(); ++i)
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		for (std::size_t i = 0; i < output.size(); ++i)
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		for (std::size_t i = 0; i < output.size(); ++i)
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		for (std::size_t i = 0; i < output.size(); ++i)
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() > BlockCount() - startIndex) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		for (std::size_t i = 0; i < output.size(); ++i)
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
		if (startIndex >= BlockCount()) [[unlikely]]
		{
			throw std::out_of_range("Start index exceeds pixel count.");
		}
		if (output.size() % BlockSize()) [[unlikely]]
		{
			throw std::invalid_argument("Output is invalid size.");
		}
		if (output.size() > Size() - startIndex * BlockSize()) [[unlikely]]
		{
			throw std::out_of_range("Output is too large.");
		}

		std::memcpy(output.data(), GetPixelRaw(startIndex), output.size());
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
}
