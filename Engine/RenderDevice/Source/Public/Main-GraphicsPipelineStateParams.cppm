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
	struct GraphicsPipelineStateParams final
	{
		std::span<const std::byte> amplificationShader;
		std::span<const std::byte> meshShader;
		std::span<const std::byte> pixelShader;
		RasterizerParams rasterizer;
		BlendParams blend;
		DepthStencilParams depthStencil;
		SampleParams sample;
		AttachmentParams attachmentParams;
	};
}
