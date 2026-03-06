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
	/// @brief Buffer barrier.
	struct BufferBarrier final
	{
		IBuffer* buffer = nullptr; ///< Buffer. Mustn't be nullptr.
		PipelineStageMask beforeStages = PipelineStageMask::None; ///< Synchronization scope of all preceding GPU work that must be completed before executing the barrier.
		PipelineStageMask afterStages = PipelineStageMask::None; ///< Synchronization scope of all subsequent GPU work that must wait until the barrier execution is finished.
		std::optional<ResourceAccessMask> beforeAccesses; ///< Access state of the buffer preceding the barrier execution. Nullopt means no access - it's compatible only with none pipeline stage.
		std::optional<ResourceAccessMask> afterAccesses; ///< Access state of the buffer upon completion of barrier execution. Nullopt means no access - it's compatible only with none pipeline stage.
	};
}
