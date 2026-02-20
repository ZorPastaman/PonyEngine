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

export module PonyEngine.RenderDevice:IGraphicsPipelineState;

import std;

import :AttachmentParams;
import :BlendParams;
import :DepthStencilParams;
import :IPipelineState;
import :RasterizerParams;
import :SampleParams;
import :ShaderType;

export namespace PonyEngine::RenderDevice
{
	class IGraphicsPipelineState : public IPipelineState
	{
		PONY_INTERFACE_BODY(IGraphicsPipelineState)

		[[nodiscard("Pure function")]]
		virtual ShaderTypeMask ShaderStages() const noexcept = 0;

		[[nodiscard("Pure function")]]
		virtual const RasterizerParams& Rasterizer() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const BlendParams& Blend() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const DepthStencilParams& DepthStencil() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const SampleParams& Sample() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const AttachmentParams& Attachment() const noexcept = 0;
	};
}
