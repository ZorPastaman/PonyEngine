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

export module PonyEngine.Render.PixelHandlers:SnormPixelHandler;

import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;

import :IPixelHandler;
import :Utility;

export namespace PonyEngine::Render::PixelHandlers
{
	/// @brief Pixel handler that supports texture formats with snorm values.
	/// @tparam RedOffset Red channel offset.
	/// @tparam GreenOffset Green channel offset.
	/// @tparam BlueOffset Blue channel offset.
	/// @tparam AlphaOffset Alpha channel offset.
	/// @tparam RedBits Red bit count.
	/// @tparam GreenBits Green bit count.
	/// @tparam BlueBits Blue bit count.
	/// @tparam AlphaBits Alpha bit count.
	template<std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint64_t RedBits, std::uint64_t GreenBits, std::uint64_t BlueBits, std::uint64_t AlphaBits>
	class SnormPixelHandler final : public IPixelHandler
	{
	public:
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
		SnormPixelHandler() noexcept = default;
		SnormPixelHandler(const SnormPixelHandler&) = delete;
		SnormPixelHandler(SnormPixelHandler&&) = delete;

		~SnormPixelHandler() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate,
			const PonyMath::Color::RGBA<float>& color) const override;

		SnormPixelHandler& operator =(const SnormPixelHandler&) = delete;
		SnormPixelHandler& operator =(SnormPixelHandler&&) = delete;
	};
}

namespace PonyEngine::Render::PixelHandlers
{
	template <std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint64_t RedBits, std::uint64_t GreenBits, std::uint64_t BlueBits, std::uint64_t AlphaBits>
	PonyMath::Color::RGBA<float> SnormPixelHandler<RedOffset, GreenOffset, BlueOffset, AlphaOffset,
		RedBits, GreenBits, BlueBits, AlphaBits>::Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		assert(RedBits + GreenBits + BlueBits + AlphaBits <= buffer.Stride() * 8 && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<const std::byte> span = buffer.Span(pixelIndex);

		auto color = PonyMath::Color::RGBA<float>::Predefined::Black;
		if constexpr (RedBits > 0)
		{
			color.R() = SnormToFloat<RedOffset, RedBits>(span);
		}
		if constexpr (GreenBits > 0)
		{
			color.G() = SnormToFloat<GreenOffset, GreenBits>(span);
		}
		if constexpr (BlueBits > 0)
		{
			color.B() = SnormToFloat<BlueOffset, BlueBits>(span);
		}
		if constexpr (AlphaBits > 0)
		{
			color.A() = SnormToFloat<AlphaOffset, AlphaBits>(span);
		}

		return color;
	}

	template <std::uint64_t RedOffset, std::uint64_t GreenOffset, std::uint64_t BlueOffset, std::uint64_t AlphaOffset,
		std::uint64_t RedBits, std::uint64_t GreenBits, std::uint64_t BlueBits, std::uint64_t AlphaBits>
	void SnormPixelHandler<RedOffset, GreenOffset, BlueOffset, AlphaOffset,
		RedBits, GreenBits, BlueBits, AlphaBits>::Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const
	{
		assert(RedBits + GreenBits + BlueBits + AlphaBits <= buffer.Stride() * 8 && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<std::byte> span = buffer.Span(pixelIndex);

		if constexpr (RedBits > 0)
		{
			FloatToSnorm<RedOffset, RedBits>(span, color.R());
		}
		if constexpr (GreenBits > 0)
		{
			FloatToSnorm<GreenOffset, GreenBits>(span, color.G());
		}
		if constexpr (BlueBits > 0)
		{
			FloatToSnorm<BlueOffset, BlueBits>(span, color.B());
		}
		if constexpr (AlphaBits > 0)
		{
			FloatToSnorm<AlphaOffset, AlphaBits>(span, color.A());
		}
	}
}
