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
	/// @brief Graphics pipeline state.
	class IGraphicsPipelineState : public IPipelineState
	{
		PONY_INTERFACE_BODY(IGraphicsPipelineState)

		/// @brief Gets the shader stages.
		/// @return Shader stages.
		[[nodiscard("Pure function")]]
		virtual GraphicsShaderTypeMask ShaderStages() const noexcept = 0;

		/// @brief Gets the attachment parameters.
		/// @return Attachment parameters.
		[[nodiscard("Pure function")]]
		virtual const AttachmentParams& Attachment() const noexcept = 0;
		/// @brief Gets the rasterizer parameters.
		/// @return Rasterizer parameters.
		[[nodiscard("Pure function")]]
		virtual const RasterizerParams& Rasterizer() const noexcept = 0;
		/// @brief Gets the depth stencil parameters.
		/// @return Depth stencil parameters.
		[[nodiscard("Pure function")]]
		virtual const DepthStencilParams& DepthStencil() const noexcept = 0;
		/// @brief Gets the sample parameters.
		/// @return Sample parameters.
		[[nodiscard("Pure function")]]
		virtual const SampleParams& Sample() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual const BlendParams& Blend() const noexcept = 0;
	};
}
