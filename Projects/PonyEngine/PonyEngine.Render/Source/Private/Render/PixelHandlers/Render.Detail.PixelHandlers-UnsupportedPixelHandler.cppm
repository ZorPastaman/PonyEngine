/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail.PixelHandlers:UnsupportedPixelHandler;

import <stdexcept>;

import :PixelHandler;

export namespace PonyEngine::Render
{
	/// @brief Pixel handler that throws on any function.
	class UnsupportedPixelHandler final : public PixelHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		UnsupportedPixelHandler() noexcept = default;
		UnsupportedPixelHandler(const UnsupportedPixelHandler&) = delete;
		UnsupportedPixelHandler(UnsupportedPixelHandler&&) = delete;

		virtual ~UnsupportedPixelHandler() noexcept override = default;

		[[nodiscard("Pure function")]] [[noreturn]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		[[noreturn]]
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const override;

		[[nodiscard("Pure function")]] [[noreturn]]
		virtual std::pair<float, std::uint8_t> DepthStencil(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const override;
		[[noreturn]]
		virtual void DepthStencil(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const std::pair<float, std::uint8_t>& depthStencil) const override;

		UnsupportedPixelHandler& operator =(const UnsupportedPixelHandler&) = delete;
		UnsupportedPixelHandler& operator =(UnsupportedPixelHandler&&) = delete;
	};
}

namespace PonyEngine::Render
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

	std::pair<float, std::uint8_t> UnsupportedPixelHandler::DepthStencil(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
		const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const
	{
		throw std::logic_error("Unsupported format.");
	}

	void UnsupportedPixelHandler::DepthStencil(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
		const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const std::pair<float, std::uint8_t>& depthStencil) const
	{
		throw std::logic_error("Unsupported format.");
	}
}
