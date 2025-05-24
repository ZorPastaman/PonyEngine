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

export module PonyEngine.Render.Core:ITextureAgent;

import <utility>;

import PonyEngine.Render;

import :AttachmentDirtyFlag;
import :TextureDirtyFlag;

export namespace PonyEngine::Render::Core
{
	/// @brief Texture agent.
	class ITextureAgent
	{
		INTERFACE_BODY(ITextureAgent)

		/// @brief Creates a GPU texture.
		/// @param texture CPU texture.
		virtual void Create(const ITexture& texture) = 0;
		/// @brief Destroys a GPU texture.
		/// @param texture CPU texture.
		virtual void Destroy(const ITexture& texture) = 0;
		/// @brief Updates a GPU texture.
		/// @param texture CPU texture.
		/// @param dirtyFlags Texture dirty flags.
		virtual void Update(const ITexture& texture, TextureDirtyFlag dirtyFlags) = 0;

		/// @brief Creates a GPU attachment.
		/// @param attachment CPU attachment.
		/// @param clearValue Clear value.
		virtual void Create(const IAttachment& attachment, const ClearValue& clearValue) = 0;
		/// @brief Destroys a GPU attachment.
		/// @param attachment CPU attachment.
		virtual void Destroy(const IAttachment& attachment) = 0;
		/// @brief Updates a GPU attachment.
		/// @param texture CPU attachment.
		/// @param dirtyFlags Attachment dirty flags.
		virtual void Update(const IAttachment& texture, AttachmentDirtyFlag dirtyFlags) = 0;

		/// @brief Gets the GPU texture format info.
		/// @param format Texture format.
		/// @return <Is the format supported?, Supported dimensions, Supported features>.
		[[nodiscard("Pure function")]]
		virtual std::tuple<bool, TextureDimensionMask, TextureFeature> TextureInfo(TextureFormat format) const noexcept = 0;
	};
}
