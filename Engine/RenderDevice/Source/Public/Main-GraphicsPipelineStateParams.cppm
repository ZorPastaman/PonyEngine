/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:GraphicsPipelineStateParams;

import std;

import :AttachmentParams;
import :BlendParams;
import :DepthStencilParams;
import :SampleParams;
import :RasterizerParams;

export namespace PonyEngine::RenderDevice
{
	/// @brief Graphics pipeline state parameters.
	struct GraphicsPipelineStateParams final
	{
		std::span<const std::byte> amplificationShader; ///< Amplification shader byte code. Must be a valid shader or empty.
		std::span<const std::byte> meshShader; ///< Mesh shader byte code. Must be a valid shader.
		std::span<const std::byte> pixelShader; ///< Pixel shader byte code. Must be a valid shader or empty.
		AttachmentParams attachment; ///< Attachment parameters. Its render target format count must match the @p blend render target count. It must have a valid depth texture format if the depth test is enabled in the @p depthStencil.
		RasterizerParams rasterizer; ///< Rasterizer parameters.
		DepthStencilParams depthStencil; ///< Depth stencil parameters. If its depth test is enabled, the @p attachment must have a valid depth texture format.
		SampleParams sample; ///< Sample parameters.
		BlendParams blend; ///< Blend parameters. Its render target count must match the @p attachment render target format count.
	};
}
