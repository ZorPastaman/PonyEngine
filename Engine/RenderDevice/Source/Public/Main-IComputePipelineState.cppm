/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:IComputePipelineState;

import :IPipelineState;

export namespace PonyEngine::RenderDevice
{
	/// @brief Compute pipeline state.
	class IComputePipelineState : public IPipelineState
	{
		PONY_INTERFACE_BODY(IComputePipelineState)
	};
}
