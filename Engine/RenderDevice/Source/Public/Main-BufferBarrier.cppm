/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:BufferBarrier;

import std;

import :IBuffer;
import :PipelineStage;
import :ResourceAccess;

export namespace PonyEngine::RenderDevice
{
	struct BufferBarrier final
	{
		IBuffer* buffer = nullptr;
		PipelineStage beforeStages = PipelineStage::None;
		PipelineStage afterStages = PipelineStage::None;
		std::optional<ResourceAccess> beforeAccesses;
		std::optional<ResourceAccess> afterAccesses;
	};
}
