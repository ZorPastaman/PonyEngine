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

export module PonyEngine.Render.PixelHandlers:UfloatPixelHandler;

import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;

import :IPixelHandler;
import :Utility;

export namespace PonyEngine::Render::PixelHandlers
{
	/// @brief Pixel handler that supports texture formats with ufloat values.
	/// @tparam RedOffset Red channel offset.
	/// @tparam GreenOffset Green channel offset.
	/// @tparam BlueOffset Blue channel offset.
	/// @tparam AlphaOffset Alpha channel offset.
	/// @tparam RedExponentBits Red exponent bit count.
	/// @tparam RedMantissaBits Red mantissa bit count.
	/// @tparam GreenExponentBits Green exponent bit count.
	/// @tparam GreenMantissaBits Green mantissa bit count.
	/// @tparam BlueExponentBits Blue exponent bit count.
	/// @tparam BlueMantissaBits Blue mantissa bit count.
	/// @tparam AlphaExponentBits Alpha exponent bit count.
	/// @tparam AlphaMantissaBits Alpha mantissa bit count.
	template<std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint32_t RedExponentBits, std::uint32_t RedMantissaBits, std::uint32_t GreenExponentBits, std::uint32_t GreenMantissaBits,
		std::uint32_t BlueExponentBits, std::uint32_t BlueMantissaBits, std::uint32_t AlphaExponentBits, std::uint32_t AlphaMantissaBits>
	class UfloatPixelHandler final : public IPixelHandler
	{
	public:
		static constexpr std::uint32_t RedBits = RedExponentBits + RedMantissaBits;
		static constexpr std::uint32_t GreenBits = GreenExponentBits + GreenMantissaBits;
		static constexpr std::uint32_t BlueBits = BlueExponentBits + BlueMantissaBits;
		static constexpr std::uint32_t AlphaBits = AlphaExponentBits + AlphaMantissaBits;

		static_assert(RedOffset + RedBits <= sizeof(std::uint64_t) * 8, "Red is too big.");
		static_assert(GreenOffset + GreenBits <= sizeof(std::uint64_t) * 8, "Green is too big.");
		static_assert(BlueOffset + BlueBits <= sizeof(std::uint64_t) * 8, "Blue is too big.");
		static_assert(AlphaOffset + AlphaBits <= sizeof(std::uint64_t) * 8, "Alpha is too big.");

		static constexpr std::uint64_t RedMask = BitMask<RedBits>; ///< Red mask.
		static constexpr std::uint64_t GreenMask = BitMask<GreenBits>; ///< Green mask.
		static constexpr std::uint64_t BlueMask = BitMask<BlueBits>; ///< Blue mask.
		static constexpr std::uint64_t AlphaMask = BitMask<AlphaBits>; ///< Alpha mask.

		static_assert(RedMask << RedOffset & GreenMask << GreenOffset == 0, "Red and green overlap.");
		static_assert(RedMask << RedOffset & BlueMask << BlueOffset == 0, "Red and blue overlap.");
		static_assert(RedMask << RedOffset & AlphaMask << AlphaOffset == 0, "Red and alpha overlap.");
		static_assert(GreenMask << GreenOffset & BlueMask << BlueBits == 0, "Green and blue overlap.");
		static_assert(GreenMask << GreenOffset & AlphaMask << AlphaBits == 0, "Green and alpha overlap.");
		static_assert(BlueMask << BlueOffset & AlphaMask << AlphaBits == 0, "Blue and alpha overlap.");

		[[nodiscard("Pure constructor")]]
		UfloatPixelHandler() noexcept = default;
		UfloatPixelHandler(const UfloatPixelHandler&) = delete;
		UfloatPixelHandler(UfloatPixelHandler&&) = delete;

		~UfloatPixelHandler() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate,
			const PonyMath::Color::RGBA<float>& color) const override;

		UfloatPixelHandler& operator =(const UfloatPixelHandler&) = delete;
		UfloatPixelHandler& operator =(UfloatPixelHandler&&) = delete;
	};
}

namespace PonyEngine::Render::PixelHandlers
{
	template <std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint32_t RedExponentBits, std::uint32_t RedMantissaBits, std::uint32_t GreenExponentBits, std::uint32_t GreenMantissaBits,
		std::uint32_t BlueExponentBits, std::uint32_t BlueMantissaBits, std::uint32_t AlphaExponentBits, std::uint32_t AlphaMantissaBits>
	PonyMath::Color::RGBA<float> UfloatPixelHandler<RedOffset, GreenOffset, BlueOffset, AlphaOffset, RedExponentBits, RedMantissaBits,
		GreenExponentBits, GreenMantissaBits, BlueExponentBits, BlueMantissaBits, AlphaExponentBits, AlphaMantissaBits>::Color(
		const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		assert(RedBits + GreenBits + BlueBits + AlphaBits <= buffer.Stride() * 8 && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<const std::byte> span = buffer.Span(pixelIndex);

		auto color = PonyMath::Color::RGBA<float>::Predefined::Black;
		if constexpr (RedBits > 0)
		{
			color.R() = SpecialUfloatToFloat<RedOffset, RedExponentBits, RedMantissaBits>(span);
		}
		if constexpr (GreenBits > 0)
		{
			color.G() = SpecialUfloatToFloat<GreenOffset, GreenExponentBits, GreenMantissaBits>(span);
		}
		if constexpr (BlueBits > 0)
		{
			color.B() = SpecialUfloatToFloat<BlueOffset, BlueExponentBits, BlueMantissaBits>(span);
		}
		if constexpr (AlphaBits > 0)
		{
			color.A() = SpecialUfloatToFloat<AlphaOffset, AlphaExponentBits, AlphaMantissaBits>(span);
		}

		return color;
	}

	template <std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint32_t RedExponentBits, std::uint32_t RedMantissaBits, std::uint32_t GreenExponentBits, std::uint32_t GreenMantissaBits,
		std::uint32_t BlueExponentBits, std::uint32_t BlueMantissaBits, std::uint32_t AlphaExponentBits, std::uint32_t AlphaMantissaBits>
	void UfloatPixelHandler<RedOffset, GreenOffset, BlueOffset, AlphaOffset, RedExponentBits, RedMantissaBits,
		GreenExponentBits, GreenMantissaBits, BlueExponentBits, BlueMantissaBits, AlphaExponentBits, AlphaMantissaBits>::Color(
		PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, 
		const PonyMath::Color::RGBA<float>& color) const
	{
		assert(RedBits + GreenBits + BlueBits + AlphaBits <= buffer.Stride() * 8 && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<std::byte> span = buffer.Span(pixelIndex);

		if constexpr (RedBits > 0)
		{
			FloatToSpecialUfloat<RedOffset, RedExponentBits, RedMantissaBits>(span, color.R());
		}
		if constexpr (GreenBits > 0)
		{
			FloatToSpecialUfloat<GreenOffset, GreenExponentBits, GreenMantissaBits>(span, color.G());
		}
		if constexpr (BlueBits > 0)
		{
			FloatToSpecialUfloat<BlueOffset, BlueExponentBits, BlueMantissaBits>(span, color.B());
		}
		if constexpr (AlphaBits > 0)
		{
			FloatToSpecialUfloat<AlphaOffset, AlphaExponentBits, AlphaMantissaBits>(span, color.A());
		}
	}
}
