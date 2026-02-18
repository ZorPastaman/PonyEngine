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
import :ICommandList;
import :StencilReference;

export namespace PonyEngine::RenderDevice
{
	class ISecondaryGraphicsCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ISecondaryGraphicsCommandList)

		virtual void SetDepthBias(const DepthBias& bias) = 0;
		virtual void SetDepthBounds(float min, float max) = 0;
		virtual void SetStencilReference(const StencilReference& reference) = 0;

		virtual void DispatchMesh(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
		virtual void DispatchCompute(const Math::Vector3<std::uint32_t>& threadGroupCounts) = 0;
	};
}
