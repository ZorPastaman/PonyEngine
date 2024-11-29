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
	class IDirect3D12GraphicsPipeline
	{
		INTERFACE_BODY(IDirect3D12GraphicsPipeline)

		virtual void AddVertexInitializationTask(ID3D12Resource2& vertexBuffer) = 0;
		virtual void AddIndexInitializationTask(ID3D12Resource2& indexBuffer) = 0;
		virtual void AddRenderTask(const std::shared_ptr<Direct3D12RenderObject>& renderObject) = 0;
	};
}
