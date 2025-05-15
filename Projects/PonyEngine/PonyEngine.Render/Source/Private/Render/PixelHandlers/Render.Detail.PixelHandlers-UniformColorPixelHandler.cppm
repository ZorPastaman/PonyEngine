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

export module PonyEngine.Render.Detail.PixelHandlers:UniformColorPixelHandler;

import <cstddef>;
import <cstdint>;
import <span>;
import <stdexcept>;
import <type_traits>;
import <utility>;

import :PixelHandler;

export namespace PonyEngine::Render
{
	/// @brief The concept is satisfied if @p T can be converted to float and back.
	template<typename T>
	concept FloatConvertible = std::is_convertible_v<T, float> && std::is_convertible_v<float, T>;

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
	class UniformColorPixelHandler final : public PixelHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		UniformColorPixelHandler() noexcept = default;
		UniformColorPixelHandler(const UniformColorPixelHandler&) = delete;
		UniformColorPixelHandler(UniformColorPixelHandler&&) = delete;

		virtual ~UniformColorPixelHandler() noexcept override = default;

		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const override;

		[[nodiscard("Pure function")]] [[noreturn]]
		virtual std::pair<float, std::uint8_t> DepthStencil(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		[[noreturn]]
		virtual void DepthStencil(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const std::pair<float, std::uint8_t>& depthStencil) const override;

		UniformColorPixelHandler& operator =(const UniformColorPixelHandler&) = delete;
		UniformColorPixelHandler& operator =(UniformColorPixelHandler&&) = delete;

	private:
		static constexpr std::size_t ComponentCount = HasRed + HasGreen + HasBlue + HasAlpha; ///< Component count.

		/// @brief Computes a pixel index in a buffer.
		/// @param size Texture size.
		/// @param pixelCoordinate Pixel coordinate.
		/// @return Pixel index.
		[[nodiscard("Pure function")]]
		static std::size_t PixelIndex(const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) noexcept;
	};
}

namespace PonyEngine::Render
{
	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t  AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	PonyMath::Color::RGBA<float> UniformColorPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::Color(
		const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		assert(sizeof(T) * ComponentCount <= buffer.Stride() && "Unsupported buffer stride.");

		const std::size_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<const std::byte> span = buffer.Span(pixelIndex);
		const auto dataSpan = std::span<const T, ComponentCount>(reinterpret_cast<const T*>(span.data()), ComponentCount);

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
	void UniformColorPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::Color(
		PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, 
		const PonyMath::Color::RGBA<float>& color) const
	{
		assert(sizeof(T) * ComponentCount <= buffer.Stride() && "Unsupported buffer stride.");

		const std::uint32_t pixelIndex = PixelIndex(size, pixelCoordinate);
		const std::span<std::byte> span = buffer.Span(pixelIndex);
		const auto dataSpan = std::span<T, ComponentCount>(reinterpret_cast<T*>(span.data()), ComponentCount);

		if constexpr (HasRed)
		{
			dataSpan[RedIndex] = static_cast<T>(color.R());
		}
		if constexpr (HasGreen)
		{
			dataSpan[GreenIndex] = static_cast<T>(color.G());
		}
		if constexpr (HasBlue)
		{
			dataSpan[BlueIndex] = static_cast<T>(color.B());
		}
		if constexpr (HasAlpha)
		{
			dataSpan[AlphaIndex] = static_cast<T>(color.A());
		}
	}

	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	std::pair<float, std::uint8_t> UniformColorPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::DepthStencil(
		const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		throw std::logic_error("Color format.");
	}

	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	void UniformColorPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue, HasAlpha>::DepthStencil(
		PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate,
		const std::pair<float, std::uint8_t>& depthStencil) const
	{
		throw std::logic_error("Color format.");
	}

	template <FloatConvertible T, std::size_t RedIndex, std::size_t GreenIndex, std::size_t BlueIndex, std::size_t AlphaIndex,
		bool HasRed, bool HasGreen, bool HasBlue, bool HasAlpha>
	std::size_t UniformColorPixelHandler<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex, HasRed, HasGreen, HasBlue,HasAlpha>::PixelIndex(
		const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) noexcept
	{
		return static_cast<std::size_t>(size.X()) * size.Y() * pixelCoordinate.Z() + static_cast<std::size_t>(size.X()) * pixelCoordinate.Y() + pixelCoordinate.X();
	}
}
