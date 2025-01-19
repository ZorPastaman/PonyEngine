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

export module PonyEngine.Render.Direct3D12.Detail:ICopyPipeline;

import <memory>;

import :Buffer;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class ICopyPipeline
	{
		INTERFACE_BODY(ICopyPipeline)

		/// @brief Adds a buffer copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The buffers must be the same size.
		virtual void AddCopyTask(const std::shared_ptr<Buffer>& source, const std::shared_ptr<Buffer>& destination) = 0;
		/// @brief Adds a texture copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The textures must be compatible for copying.
		virtual void AddCopyTask(const std::shared_ptr<Texture>& source, const std::shared_ptr<Texture>& destination) = 0;
	};
}
