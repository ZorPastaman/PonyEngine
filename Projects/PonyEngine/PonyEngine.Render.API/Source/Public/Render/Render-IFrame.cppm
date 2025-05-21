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
import <optional>;
import <string_view>;

import PonyMath.Utility;

import :AttachmentType;
import :ClearValue;
import :IAttachment;
import :TextureFormat;

export namespace PonyEngine::Render
{
	/// @brief Frame.
	class IFrame
	{
		INTERFACE_BODY(IFrame)

		/// @brief Tries to find an attachment index by its type.
		/// @param attachmentType Attachment type.
		/// @return Attachment index if it's found; std::nullopt otherwise.
		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindAttachmentIndex(AttachmentType attachmentType) const noexcept = 0;
		/// @brief Gets an attachment type by the index.
		/// @param index Attachment index.
		/// @return Attachment type.
		[[nodiscard("Pure function")]]
		virtual enum AttachmentType AttachmentType(std::uint32_t index) const noexcept = 0;
		/// @brief Gets an attachment by the index.
		/// @param index Attachment index.
		/// @return Attachment.
		[[nodiscard("Pure function")]]
		virtual const IAttachment& Attachment(std::uint32_t index) const noexcept = 0;
		/// @brief Gets the attachment count.
		/// @return Attachment count.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t AttachmentCount() const noexcept = 0;

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
		virtual const PonyMath::Utility::Resolution<std::uint32_t>& Resolution() const noexcept = 0;
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
