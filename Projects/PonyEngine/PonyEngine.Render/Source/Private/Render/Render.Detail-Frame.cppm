/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render.Detail:Frame;

import <cstdint>;
import <memory>;
import <optional>;
import <string>;
import <string_view>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyEngine.Render;

import :Attachment;
import :AttachmentDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Frame.
	class Frame final : public IFrame
	{
	public:
		/// @brief Creates a frame.
		/// @param attachments Attachments.
		/// @param clearValue Clear value.
		/// @param resolution Resolution.
		/// @param sampleCount Sample count.
		/// @param renderTargetFormat Render target format.
		/// @param depthStencilFormat Depth stencil format.
		/// @param name Name.
		[[nodiscard("Pure constructor")]]
		Frame(std::unordered_map<enum AttachmentType, std::unique_ptr<class Attachment>>&& attachments, const struct ClearValue& clearValue,
			const PonyMath::Utility::Resolution<std::uint32_t>& resolution, std::uint8_t sampleCount,
			TextureFormat renderTargetFormat, TextureFormat depthStencilFormat, std::string_view name) noexcept;
		[[nodiscard("Pure constructor")]]
		Frame(const Frame&) = delete;
		[[nodiscard("Pure constructor")]]
		Frame(Frame&&) = delete;

		~Frame() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::optional<std::uint32_t> FindAttachmentIndex(enum AttachmentType attachmentType) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual enum AttachmentType AttachmentType(std::uint32_t index) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual const IAttachment& Attachment(std::uint32_t index) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint32_t AttachmentCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual const struct ClearValue& ClearValue() const noexcept override;
		virtual void ClearValue(const struct ClearValue& clear) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const PonyMath::Utility::Resolution<std::uint32_t>& Resolution() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::uint8_t SampleCount() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual TextureFormat RenderTargetFormat() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual TextureFormat DepthStencilFormat() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;
		virtual void Name(std::string_view name) override;

		[[nodiscard("Pure function")]]
		AttachmentDirtyFlag DirtyFlags() const noexcept;
		void ResetDirty() noexcept;

		Frame& operator =(const Frame&) = delete;
		Frame& operator =(Frame&&) = delete;

	private:
		/// @brief Updates attachment names. It syncs their names with the frame name.
		void UpdateAttachmentName();

		std::vector<enum AttachmentType> attachmentTypes; ///< Attachment types.
		std::vector<std::unique_ptr<class Attachment>> attachments; ///< Attachments.

		struct ClearValue clearValue; ///< Clear value.

		PonyMath::Utility::Resolution<std::uint32_t> resolution; ///< Resolution.
		std::uint8_t sampleCount; ///< Sample count.

		TextureFormat renderTargetFormat; ///< Render target format.
		TextureFormat depthStencilFormat; ///< Depth stencil format.

		std::string name; ///< Name.

		AttachmentDirtyFlag dirtyFlags; ///< Dirty flags.
	};
}

namespace PonyEngine::Render
{
	Frame::Frame(std::unordered_map<enum AttachmentType, std::unique_ptr<class Attachment>>&& attachments, const struct ClearValue& clearValue,
		const PonyMath::Utility::Resolution<std::uint32_t>& resolution, const std::uint8_t sampleCount,
		const TextureFormat renderTargetFormat, const TextureFormat depthStencilFormat, const std::string_view name) noexcept :
		clearValue(clearValue),
		resolution(resolution),
		sampleCount{sampleCount},
		renderTargetFormat(renderTargetFormat),
		depthStencilFormat(depthStencilFormat),
		name(name),
		dirtyFlags{AttachmentDirtyFlag::All}
	{
		attachmentTypes.reserve(attachments.size());
		this->attachments.reserve(attachments.size());
		for (auto& [attachmentType, attachment] : attachments)
		{
			attachmentTypes.push_back(attachmentType);
			this->attachments.push_back(std::move(attachment));
		}
		UpdateAttachmentName();
	}

	std::optional<std::uint32_t> Frame::FindAttachmentIndex(const enum AttachmentType attachmentType) const noexcept
	{
		for (std::uint32_t i = 0u; i < static_cast<std::uint32_t>(attachmentTypes.size()); ++i)
		{
			if (attachmentTypes[i] == attachmentType)
			{
				return i;
			}
		}

		return std::nullopt;
	}

	enum AttachmentType Frame::AttachmentType(const std::uint32_t index) const noexcept
	{
		return attachmentTypes[index];
	}

	const IAttachment& Frame::Attachment(const std::uint32_t index) const noexcept
	{
		return *attachments[index];
	}

	std::uint32_t Frame::AttachmentCount() const noexcept
	{
		return static_cast<std::uint32_t>(attachments.size());
	}

	const struct ClearValue& Frame::ClearValue() const noexcept
	{
		return clearValue;
	}

	void Frame::ClearValue(const struct ClearValue& clear) noexcept
	{
		clearValue = clear;
	}

	const PonyMath::Utility::Resolution<std::uint32_t>& Frame::Resolution() const noexcept
	{
		return resolution;
	}

	std::uint8_t Frame::SampleCount() const noexcept
	{
		return sampleCount;
	}

	TextureFormat Frame::RenderTargetFormat() const noexcept
	{
		return renderTargetFormat;
	}

	TextureFormat Frame::DepthStencilFormat() const noexcept
	{
		return depthStencilFormat;
	}

	std::string_view Frame::Name() const noexcept
	{
		return name;
	}

	void Frame::Name(const std::string_view name)
	{
		if (this->name == name)
		{
			return;
		}

		this->name = name;
		UpdateAttachmentName();
		dirtyFlags |= AttachmentDirtyFlag::Name;
	}

	AttachmentDirtyFlag Frame::DirtyFlags() const noexcept
	{
		return dirtyFlags;
	}

	void Frame::ResetDirty() noexcept
	{
		dirtyFlags = AttachmentDirtyFlag::None;
	}

	void Frame::UpdateAttachmentName()
	{
		for (const std::unique_ptr<class Attachment>& attachment : attachments)
		{
			attachment->Name(name);
		}
	}
}
