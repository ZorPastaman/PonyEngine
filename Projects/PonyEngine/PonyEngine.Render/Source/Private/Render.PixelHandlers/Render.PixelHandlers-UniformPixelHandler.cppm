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

export module PonyEngine.Render.PixelHandlers:UniformPixelHandler;

import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;
import <type_traits>;
import <utility>;

import PonyMath.Core;

import :IPixelHandler;
import :Utility;

export namespace PonyEngine::Render
{
	/// @brief The concept is satisfied if @p T can be converted to float and back.
	template<typename T>
	concept FloatConvertible = requires (const T t, const float f)
	{
		{ static_cast<float>(t) } -> std::same_as<float>;
		{ static_cast<T>(f) } -> std::same_as<T>;
	};

	/// @brief Pixel handler that supports color texture formats with the same components in a pixel that can be converted to float and back.
	/// @tparam T Component type.
	/// @tparam RedIndex Red component index.
	/// @tparam GreenIndex Green component index.
	/// @tparam BlueIndex Blue component index.
	/// @tparam AlphaIndex Alpha component index.
	/// @tparam HasRed Does the format has a red component.
	/// @tparam HasGreen Does the format has a green component.
	/// @tparam HasBlue Does the format has a blue component.
	/// @tparam HasAlpha Does the format has an alpha component.
	template<FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	class UniformPixelHandler final : public IPixelHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		UniformPixelHandler() noexcept = default;
		UniformPixelHandler(const UniformPixelHandler&) = delete;
		UniformPixelHandler(UniformPixelHandler&&) = delete;

		~UniformPixelHandler() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const override;

		UniformPixelHandler& operator =(const UniformPixelHandler&) = delete;
		UniformPixelHandler& operator =(UniformPixelHandler&&) = delete;

	private:
		static constexpr std::size_t UsedBytes = (std::max({RedIndex, GreenIndex, BlueIndex, AlphaIndex}) + 1) * sizeof(T); ///< How many bytes are used by the data.
	};
}

namespace PonyEngine::Render
{
	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	PonyMath::Color::RGBA<float> UniformPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::Color(
		const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		assert(UsedBytes <= buffer.Stride() && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<const std::byte> span = buffer.Span(pixelIndex);
		const auto dataSpan = std::span<const T, UsedBytes>(reinterpret_cast<const T*>(span.data()), UsedBytes);

		auto color = PonyMath::Color::RGBA<float>::Predefined::Black;
		if constexpr (HasRed)
		{
			color.R() = static_cast<float>(dataSpan[RedIndex]);
		}
		if constexpr (HasGreen)
		{
			color.G() = static_cast<float>(dataSpan[GreenIndex]);
		}
		if constexpr (HasBlue)
		{
			color.B() = static_cast<float>(dataSpan[BlueIndex]);
		}
		if constexpr (HasAlpha)
		{
			color.A() = static_cast<float>(dataSpan[AlphaIndex]);
		}

		return color;
	}

	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	void UniformPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::Color(
		PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, 
		const PonyMath::Color::RGBA<float>& color) const
	{
		assert(UsedBytes <= buffer.Stride() && "Unsupported buffer stride.");

		const std::uint32_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<std::byte> span = buffer.Span(pixelIndex);
		const auto dataSpan = std::span<T, UsedBytes>(reinterpret_cast<T*>(span.data()), UsedBytes);

		if constexpr (HasRed)
		{
			if constexpr (std::is_integral_v<T>)
			{
				dataSpan[RedIndex] = PonyMath::Core::RoundToIntegral<float, T>(color.R());
			}
			else
			{
				dataSpan[RedIndex] = static_cast<T>(color.R());
			}
		}
		if constexpr (HasGreen)
		{
			if constexpr (std::is_integral_v<T>)
			{
				dataSpan[GreenIndex] = PonyMath::Core::RoundToIntegral<float, T>(color.G());
			}
			else
			{
				dataSpan[GreenIndex] = static_cast<T>(color.G());
			}
		}
		if constexpr (HasBlue)
		{
			if constexpr (std::is_integral_v<T>)
			{
				dataSpan[BlueIndex] = PonyMath::Core::RoundToIntegral<float, T>(color.B());
			}
			else
			{
				dataSpan[BlueIndex] = static_cast<T>(color.B());
			}
		}
		if constexpr (HasAlpha)
		{
			if constexpr (std::is_integral_v<T>)
			{
				dataSpan[AlphaIndex] = PonyMath::Core::RoundToIntegral<float, T>(color.A());
			}
			else
			{
				dataSpan[AlphaIndex] = static_cast<T>(color.A());
			}
		}
	}
}
