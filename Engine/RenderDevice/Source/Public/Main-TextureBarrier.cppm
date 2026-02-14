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
	struct TextureBarrier final
	{
		ITexture* texture = nullptr;
		std::optional<MultiAspectSubTextureRange> range;
		PipelineStage beforeStages = PipelineStage::None;
		PipelineStage afterStages = PipelineStage::None;
		std::optional<ResourceAccess> beforeAccesses;
		std::optional<ResourceAccess> afterAccesses;
		ResourceLayout beforeLayout = ResourceLayout::Common;
		ResourceLayout afterLayout = ResourceLayout::Common;
		bool discard = false;
	};
}
