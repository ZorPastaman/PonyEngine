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

export module PonyEngine.Render:IFrame;

import <cstdint>;
import <memory>;
import <string_view>;

import PonyMath.Utility;

import :ClearValue;
import :ITexture;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Frame.
	class IFrame
	{
		INTERFACE_BODY(IFrame)

		/// @brief Gets the clear value.
		/// @return Clear value.
		[[nodiscard("Pure function")]]
		virtual const struct ClearValue& ClearValue() const noexcept = 0;
		/// @brief Sets the clear value.
		/// @param clear Clear value to set.
		virtual void ClearValue(const struct ClearValue& clear) noexcept = 0;

		/// @brief Gets the frame resolution.
		/// @return Frame resolution. It returns a zero resolution if there's no render target or depth stencil attached.
		[[nodiscard("Pure function")]]
		virtual PonyMath::Utility::Resolution<std::uint32_t> Resolution() const noexcept = 0;
		/// @brief Gets the sample count.
		/// @return Sample count. It returns 0 if there's no render target or depth stencil attached.
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SampleCount() const noexcept = 0;

		/// @brief Gets the render target format.
		/// @return Render target format. Unknown if there's no render target attached.
		[[nodiscard("Pure function")]]
		virtual TextureFormat RenderTargetFormat() const noexcept = 0;
		/// @brief Gets the depth stencil format.
		/// @return Depth stencil format. Unknown if there's no depth stencil attached.
		[[nodiscard("Pure function")]]
		virtual TextureFormat DepthStencilFormat() const noexcept = 0;

		/// @brief Gets the name.
		/// @return Name.
		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		/// @brief Sets the name.
		/// @param name Name to set.
		virtual void Name(std::string_view name) = 0;
	};
}
