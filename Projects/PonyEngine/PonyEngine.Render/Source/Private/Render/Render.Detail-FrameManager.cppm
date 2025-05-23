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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:FrameManager;

import <algorithm>;
import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <unordered_map>;
import <utility>;
import <vector>;

import PonyDebug.Log;

import PonyEngine.Render;

import :Attachment;
import :AttachmentDirtyFlag;
import :Frame;
import :IRenderSystemContext;

export namespace PonyEngine::Render
{
	/// @brief Frame manager.
	class FrameManager final : public IFrameManager
	{
	public:
		/// @brief Creates a frame manager.
		/// @param renderSystem Render system context.
		/// @param mainFrameParams Main frame parameters.
		[[nodiscard("Pure constructor")]]
		FrameManager(IRenderSystemContext& renderSystem, const FrameParams& mainFrameParams);
		FrameManager(const FrameManager&) = delete;
		FrameManager(FrameManager&&) = delete;

		~FrameManager() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IFrame>& MainFrame() const noexcept override;

		/// @brief Creates a new frame.
		/// @param frameParams Frame parameters.
		/// @return Frame.
		[[nodiscard("Redundant call")]]
		std::shared_ptr<IFrame> CreateFrame(const FrameParams& frameParams);
		/// @brief Creates a main frame.
		/// @param frameParams Frame parameters.
		/// @return Main frame.
		std::shared_ptr<IFrame> CreateMainFrame(const FrameParams& frameParams);

		/// @brief Tick the frame manager.
		void Tick();
		/// @brief Cleans out dead frames.
		void Clean();

		FrameManager& operator =(const FrameManager&) = delete;
		FrameManager& operator =(FrameManager&&) = delete;

	private:
		/// @brief Creates new frames on GPU.
		void Create();
		/// @brief Updates living frames.
		void Update();
		/// @brief Clears dirty flags and caches.
		void Clear() noexcept;
		/// @brief Submits the main frame to a pipeline.
		void Submit();

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::vector<std::shared_ptr<Frame>> frames; ///< Frames.
		std::vector<std::pair<const Frame*, ClearValue>> newFrames; ///< New frames with their clear values.

		std::shared_ptr<const IFrame> mainFrame; ///< Main frame.
	};
}

namespace PonyEngine::Render
{
	FrameManager::FrameManager(IRenderSystemContext& renderSystem, const FrameParams& mainFrameParams) :
		renderSystem{&renderSystem}
	{
		CreateMainFrame(mainFrameParams);
	}

	const std::shared_ptr<const IFrame>& FrameManager::MainFrame() const noexcept
	{
		return mainFrame;
	}

	std::shared_ptr<IFrame> FrameManager::CreateFrame(const FrameParams& frameParams)
	{
		if (frameParams.sampleCount < 1u)
		{
			throw std::invalid_argument("Sample count must be greater than 0.");
		}
		if (frameParams.rtvFormat == TextureFormat::Unknown && frameParams.dsvFormat == TextureFormat::Unknown) [[unlikely]]
		{
			throw std::invalid_argument("No rtv and no dsv are specified.");
		}

		if (frameParams.rtvFormat != TextureFormat::Unknown)
		{
			const TextureFormatInfo& rtvFormatInfo = this->renderSystem->TextureManager().FormatInfo(frameParams.rtvFormat);

			if (!rtvFormatInfo.supportedByPlatform) [[unlikely]]
			{
				throw std::invalid_argument("Render target format is not supported.");
			}
			if (!IsInMask(TextureDimension::Texture2D, rtvFormatInfo.supportedDimensions)) [[unlikely]]
			{
				throw std::invalid_argument("Render target format doesn't support 2D dimension.");
			}
			if ((rtvFormatInfo.features & TextureFeature::RenderTarget) == TextureFeature::None) [[unlikely]]
			{
				throw std::invalid_argument("Render target format doesn't support render target.");
			}
			if (frameParams.sampleCount > 1u && (rtvFormatInfo.features & TextureFeature::MSAA) == TextureFeature::None) [[unlikely]]
			{
				throw std::invalid_argument("Render target format doesn't support MSAA.");
			}
		}
		if (frameParams.dsvFormat != TextureFormat::Unknown)
		{
			const TextureFormatInfo& dsvFormatInfo = this->renderSystem->TextureManager().FormatInfo(frameParams.dsvFormat);

			if (!dsvFormatInfo.supportedByPlatform) [[unlikely]]
			{
				throw std::invalid_argument("Depth stencil format is not supported.");
			}
			if (!IsInMask(TextureDimension::Texture2D, dsvFormatInfo.supportedDimensions)) [[unlikely]]
			{
				throw std::invalid_argument("Depth stencil format doesn't support 2D dimension.");
			}
			if ((dsvFormatInfo.features & TextureFeature::DepthStencil) == TextureFeature::None) [[unlikely]]
			{
				throw std::invalid_argument("Depth stencil format doesn't support depth stencil.");
			}
			if (frameParams.sampleCount > 1u && (dsvFormatInfo.features & TextureFeature::MSAA) == TextureFeature::None) [[unlikely]]
			{
				throw std::invalid_argument("Depth stencil format doesn't support MSAA.");
			}
		}

		const PonyMath::Utility::Resolution<std::uint32_t> resolution = frameParams.resolution.has_value()
			? frameParams.resolution.value()
			: this->renderSystem->SwapChain().Resolution();

		std::unordered_map<AttachmentType, std::unique_ptr<Attachment>> attachments;
		if (frameParams.rtvFormat != TextureFormat::Unknown)
		{
			attachments[AttachmentType::RenderTarget] = std::make_unique<Attachment>(frameParams.rtvFormat, resolution, frameParams.sampleCount);
			if (frameParams.sampleCount > 1u)
			{
				attachments[AttachmentType::Resolve] = std::make_unique<Attachment>(frameParams.rtvFormat, resolution, 1u);
			}
		}
		if (frameParams.dsvFormat != TextureFormat::Unknown)
		{
			attachments[AttachmentType::DepthStencil] = std::make_unique<Attachment>(frameParams.dsvFormat, resolution, frameParams.sampleCount);
		}

		const auto frame = std::make_shared<Frame>(std::move(attachments), frameParams.clearOnTick, resolution, frameParams.sampleCount, 
			frameParams.rtvFormat, frameParams.dsvFormat, frameParams.name);
		frames.push_back(frame);
		newFrames.emplace_back(frame.get(), frameParams.clearOnCreation);

		return frame;
	}

	std::shared_ptr<IFrame> FrameManager::CreateMainFrame(const FrameParams& frameParams)
	{
		if (frameParams.rtvFormat == TextureFormat::Unknown) [[unlikely]]
		{
			throw std::invalid_argument("Main frame must have rtv.");
		}

		const std::shared_ptr<IFrame> frame = CreateFrame(frameParams);
		mainFrame = frame;

		return frame;
	}

	void FrameManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Submit.");
		Submit();
	}

	void FrameManager::Clean()
	{
		for (std::size_t i = frames.size(); i-- > 0; )
		{
			const std::shared_ptr<Frame>& frame = frames[i];
			if (frame.use_count() > 1L)
			{
				continue;
			}

			if (const auto position = std::ranges::find_if(newFrames, [&](const std::pair<const Frame*, ClearValue>& p) { return p.first == frame.get(); }); position != newFrames.cend())
			{
				newFrames.erase(position);
			}
			else
			{
				for (std::uint32_t attachmentIndex = 0; attachmentIndex < frame->AttachmentCount(); ++attachmentIndex)
				{
					const auto& attachment = static_cast<const Attachment&>(frame->Attachment(attachmentIndex));
					renderSystem->RenderAgent().TextureAgent().Destroy(attachment);
				}
			}
			frames.erase(frames.cbegin() + i);
		}
	}

	void FrameManager::Create()
	{
		for (const auto& [frame, clear] : newFrames)
		{
			for (std::uint32_t attachmentIndex = 0; attachmentIndex < frame->AttachmentCount(); ++attachmentIndex)
			{
				const IAttachment& attachment = frame->Attachment(attachmentIndex);
				renderSystem->RenderAgent().TextureAgent().Create(attachment, clear);
			}
		}
	}

	void FrameManager::Update()
	{
		for (const std::shared_ptr<Frame>& frame : frames)
		{
			if (frame->DirtyFlags() == AttachmentDirtyFlag::None)
			{
				continue;
			}

			for (std::uint32_t attachmentIndex = 0; attachmentIndex < frame->AttachmentCount(); ++attachmentIndex)
			{
				const auto& attachment = static_cast<const Attachment&>(frame->Attachment(attachmentIndex));
				renderSystem->RenderAgent().TextureAgent().Update(attachment, frame->DirtyFlags());
			}
		}
	}

	void FrameManager::Clear() noexcept
	{
		for (const std::shared_ptr<Frame>& frame : frames)
		{
			frame->ResetDirty();
		}

		newFrames.clear();
	}

	void FrameManager::Submit()
	{
		for (const std::shared_ptr<Frame>& frame : frames)
		{
			renderSystem->Pipeline().Submit(*frame);
		}

		renderSystem->Pipeline().SetMainFrame(*mainFrame);
	}
}
