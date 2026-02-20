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

export module PonyEngine.RenderDevice:ISecondaryGraphicsCommandList;

import std;

import PonyEngine.Math;

import :DepthBias;
import :DepthRange;
import :ICommandList;
import :IComputePipelineState;
import :IGraphicsPipelineState;
import :StencilReference;

export namespace PonyEngine::RenderDevice
{
	class ISecondaryGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ISecondaryGraphicsCommandList)

		virtual void SetPipelineState(const IGraphicsPipelineState& pipelineState) = 0;
		virtual void SetPipelineState(const IComputePipelineState& pipelineState) = 0;

		virtual void SetDepthBias(const DepthBias& bias) = 0;
		virtual void SetDepthBounds(const DepthRange& range) = 0;
		virtual void SetStencilReference(const StencilReference& reference) = 0;

		virtual void SetBlendFactor(const Math::ColorRGBA<float>& factor) = 0;

		virtual void DispatchGraphics(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
	};
}
