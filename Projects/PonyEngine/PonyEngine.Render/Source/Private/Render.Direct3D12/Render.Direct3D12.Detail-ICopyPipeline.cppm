/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:ICopyPipeline;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class ICopyPipeline
	{
		INTERFACE_BODY(ICopyPipeline)

		/// @brief Adds a buffer copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The resources must be the same size.
		virtual void AddBufferCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) = 0;
		/// @brief Adds a texture copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The resources must be the same size.
		virtual void AddTextureCopyTask(ID3D12Resource2& source, ID3D12Resource2& destination) = 0;
	};
}
