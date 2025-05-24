/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.PixelHandlers:UnsupportedPixelHandler;

import <stdexcept>;

import :IPixelHandler;

export namespace PonyEngine::Render::PixelHandlers
{
	/// @brief Pixel handler that throws on any function.
	class UnsupportedPixelHandler final : public IPixelHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		UnsupportedPixelHandler() noexcept = default;
		UnsupportedPixelHandler(const UnsupportedPixelHandler&) = delete;
		UnsupportedPixelHandler(UnsupportedPixelHandler&&) = delete;

		~UnsupportedPixelHandler() noexcept = default;

		[[nodiscard("Pure function")]] [[noreturn]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		[[noreturn]]
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const override;

		UnsupportedPixelHandler& operator =(const UnsupportedPixelHandler&) = delete;
		UnsupportedPixelHandler& operator =(UnsupportedPixelHandler&&) = delete;
	};
}

namespace PonyEngine::Render::PixelHandlers
{
	PonyMath::Color::RGBA<float> UnsupportedPixelHandler::Color(const PonyBase::Container::Buffer& buffer,
		const PonyMath::Core::Vector3<std::uint32_t>& size, const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		throw std::logic_error("Unsupported format.");
	}

	void UnsupportedPixelHandler::Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
		const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const
	{
		throw std::logic_error("Unsupported format.");
	}
}
