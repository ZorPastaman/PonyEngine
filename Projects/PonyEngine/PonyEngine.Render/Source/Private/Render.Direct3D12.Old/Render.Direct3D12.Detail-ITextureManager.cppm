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

export module PonyEngine.Render.Direct3D12.Detail:ITextureManager;

import <memory>;

import PonyEngine.Render;

import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 texture manager.
	class ITextureManager
	{
		INTERFACE_BODY(ITextureManager)

		/// @brief Creates a render texture.
		/// @param texture Texture.
		/// @return Render texture.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Texture> CreateTexture(const std::shared_ptr<const Render::Texture>& texture) = 0;
	};
}
