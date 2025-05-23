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

export module PonyEngine.Render.Detail:IBufferAgent;

import PonyEngine.Render;

import :BufferDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Buffer agent.
	class IBufferAgent
	{
		INTERFACE_BODY(IBufferAgent)

		/// @brief Creates a GPU buffer.
		/// @param buffer CPU buffer.
		virtual void Create(const IBuffer& buffer) = 0;
		/// @brief Destroys a GPU buffer.
		/// @param buffer CPU buffer.
		virtual void Destroy(const IBuffer& buffer) = 0;
		/// @brief Updates a GPU buffer.
		/// @param buffer CPU buffer.
		/// @param dirtyFlags Dirty flags.
		virtual void Update(const IBuffer& buffer, BufferDirtyFlag dirtyFlags) = 0;
	};
}
