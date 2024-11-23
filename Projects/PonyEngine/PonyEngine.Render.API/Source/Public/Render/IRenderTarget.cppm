/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render:IRenderTarget;

import <cstdint>;

import PonyMath.Color;
import PonyMath.Utility;

export namespace PonyEngine::Render
{
	/// @brief Render target.
	class IRenderTarget
	{
		INTERFACE_BODY(IRenderTarget)

		/// @brief Gets the clear color.
		/// @return Clear color.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Color::RGBA<float> ClearColor() const noexcept = 0;
		/// @brief Sets the clear color.
		/// @param color Clear color.
		virtual void ClearColor(const PonyMath::Color::RGBA<float>& color) noexcept = 0;

		/// @brief Gets the render target resolution.
		/// @return Render target resolution.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept = 0;
	};
}
