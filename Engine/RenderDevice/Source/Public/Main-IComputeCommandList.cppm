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

export module PonyEngine.RenderDevice:IComputeCommandList;

import std;

import :BufferBarrier;
import :ICommandList;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	class IComputeCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(IComputeCommandList)

		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void IComputeCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers)
	{
		Barrier(bufferBarriers, std::span<const TextureBarrier>());
	}

	void IComputeCommandList::Barrier(const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span<const BufferBarrier>(), textureBarriers);
	}
}
