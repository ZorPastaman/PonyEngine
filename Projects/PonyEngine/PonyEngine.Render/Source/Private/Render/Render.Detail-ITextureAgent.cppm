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

export module PonyEngine.Render.Detail:ITextureAgent;

import <utility>;

import PonyEngine.Render;

import :Texture;

export namespace PonyEngine::Render
{
	/// @brief Texture agent.
	class ITextureAgent
	{
		INTERFACE_BODY(ITextureAgent)

		/// @brief Creates a GPU texture.
		/// @param texture CPU texture.
		/// @param clear Clear value.
		virtual void Create(const Texture& texture, const ClearValue& clear) = 0;
		/// @brief Destroys a GPU texture.
		/// @param texture CPU texture.
		virtual void Destroy(const Texture& texture) = 0;
		/// @brief Updates a GPU texture.
		/// @param texture CPU texture.
		virtual void Update(const Texture& texture) = 0;

		/// @brief Gets the GPU texture format info.
		/// @param format Texture format.
		/// @return <Is the format supported?, Supported dimensions, Supported features>.
		[[nodiscard("Pure function")]]
		virtual std::tuple<bool, TextureDimensionMask, TextureFeature> TextureInfo(TextureFormat format) const noexcept = 0;
	};
}
