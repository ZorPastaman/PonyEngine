/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Render.Direct3D12.Detail:IDirect3D12GraphicsPipeline;

import <memory>;

import :Direct3D12RenderObject;

export namespace PonyEngine::Render
{
	/// @brief Direct3D12 graphics pipeline.
	class IDirect3D12GraphicsPipeline
	{
		INTERFACE_BODY(IDirect3D12GraphicsPipeline)

		/// @brief Adds a vertex initialization task. It sets the resource to the state of @p D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER.
		/// @param vertexBuffer Vertex buffer.
		virtual void AddVertexInitializationTask(ID3D12Resource2& vertexBuffer) = 0;
		/// @brief Adds an index initialization task.It sets the resource to the state of @p D3D12_RESOURCE_STATE_INDEX_BUFFER.
		/// @param indexBuffer Index buffer.
		virtual void AddIndexInitializationTask(ID3D12Resource2& indexBuffer) = 0;
		/// @brief Adds a render task.
		/// @param renderObject Render object to render.
		virtual void AddRenderTask(const std::shared_ptr<Direct3D12RenderObject>& renderObject) = 0;
	};
}
