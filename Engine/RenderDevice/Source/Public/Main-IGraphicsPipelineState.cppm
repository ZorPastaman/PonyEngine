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
import :IPipelineLayout;
import :RasterizerParams;
import :SampleParams;
import :ShaderType;

export namespace PonyEngine::RenderDevice
{
	class IGraphicsPipelineState
	{
		PONY_INTERFACE_BODY(IGraphicsPipelineState)

		[[nodiscard("Pure function")]]
		virtual const std::shared_ptr<const IPipelineLayout>& Layout() const noexcept = 0;
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

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept = 0;
		virtual void Name(std::string_view name) = 0;
	};
}
