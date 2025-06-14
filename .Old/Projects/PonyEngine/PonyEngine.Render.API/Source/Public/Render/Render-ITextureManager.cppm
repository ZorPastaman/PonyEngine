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

export module PonyEngine.Render:ITextureManager;

import <memory>;

import :ITexture;
import :TextureFormat;
import :TextureParams;

export namespace PonyEngine::Render
{
	/// @brief Texture manager.
	class ITextureManager
	{
		INTERFACE_BODY(ITextureManager)

		/// @brief Creates a texture manager.
		/// @param params Texture parameters.
		/// @return Texture.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(const TextureParams& params) = 0;

		/// @brief Gets a texture format info.
		/// @param format Texture format.
		/// @return Texture format info.
		[[nodiscard("Pure function")]]
		virtual const TextureFormatInfo& FormatInfo(TextureFormat format) const noexcept = 0;
	};
}
