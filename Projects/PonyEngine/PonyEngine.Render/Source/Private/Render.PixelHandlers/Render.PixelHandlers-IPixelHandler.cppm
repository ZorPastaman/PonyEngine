/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.PixelHandlers:IPixelHandler;

import <cstdint>;
import <utility>;

import PonyBase.Container;

import PonyMath.Color;
import PonyMath.Core;

export namespace PonyEngine::Render::PixelHandlers
{
	/// @brief Pixel handler.
	class IPixelHandler
	{
		INTERFACE_BODY(IPixelHandler)

		/// @brief Gets a color.
		/// @param buffer Buffer source.
		/// @param size Buffer size in pixels.
		/// @param pixelCoordinate Pixel coordinate.
		/// @return Color.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> Color(const PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate) const = 0;
		/// @brief Sets a color.
		/// @param buffer Buffer destination.
		/// @param size Buffer size in pixels.
		/// @param pixelCoordinate Pixel coordinate.
		/// @param color Color to set.
		virtual void Color(PonyBase::Container::Buffer& buffer, const PonyMath::Core::Vector3<std::uint32_t>& size,
			const PonyMath::Core::Vector3<std::uint32_t>& pixelCoordinate, const PonyMath::Color::RGBA<float>& color) const = 0;
	};
}
