/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureBarrier;

import std;

import :Aspect;
import :ITexture;
import :PipelineStage;
import :ResourceAccess;
import :ResourceLayout;
import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture barrier.
	struct TextureBarrier final
	{
		ITexture* texture = nullptr; ///< Texture. Must be a valid texture.
		std::optional<SubTextureRange> range; ///< Sub-texture range. Nullopt means the whole texture.
		PipelineStageMask beforeStages = PipelineStageMask::None; ///< Synchronization scope of all preceding GPU work that must be completed before executing the barrier.
		PipelineStageMask afterStages = PipelineStageMask::None; ///< Synchronization scope of all subsequent GPU work that must wait until the barrier execution is finished.
		std::optional<ResourceAccessMask> beforeAccesses; ///< Access state of the texture preceding the barrier execution. Nullopt means no access - it's compatible only with none pipeline stage.
		std::optional<ResourceAccessMask> afterAccesses; ///< Access state of the texture upon completion of barrier execution. Nullopt means no access - it's compatible only with none pipeline stage.
		ResourceLayout beforeLayout = ResourceLayout::Common; ///< Layout of the texture that must be before the barrier execution.
		ResourceLayout afterLayout = ResourceLayout::Common; ///< Layout of the texture that must be after the barrier execution.
		bool discard = false; ///< Should it discard a content of the texture? It's compatible only with the undefined before layout.
	};
}
