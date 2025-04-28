/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:Texture1D;

import <cstdint>;

import :Texture;

export namespace PonyEngine::Render
{
	class Texture1D final : public Texture
	{
	public:
		[[nodiscard("Pure constructor")]]
		Texture1D() noexcept;
		[[nodiscard("Pure constructor")]]
		explicit Texture1D(std::uint32_t width, TextureFormat format = TextureFormat::R8G8B8A8_Unorm);
		[[nodiscard("Pure constructor")]]
		Texture1D(const Texture1D& other) = default;
		[[nodiscard("Pure constructor")]]
		Texture1D(Texture1D&& other) noexcept = default;

		virtual ~Texture1D() noexcept override = default;

		[[nodiscard("Pure function")]]
		std::uint32_t Width() const noexcept;

		Texture1D& operator =(const Texture1D& other) = default;
		Texture1D& operator =(Texture1D&& other) noexcept = default;

	private:
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
		Texture(PonyBase::Container::Buffer(TextureFormatSize(width, format), width), TextureDimension::Texture1D, format),
		width(width)
	{
	}

	std::uint32_t Texture1D::Width() const noexcept
	{
		return width;
	}
}
