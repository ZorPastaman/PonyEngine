/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:BlendParams;

import std;

import :BlendFactor;
import :BlendOperation;
import :ColorComponent;
import :LogicOperation;

export namespace PonyEngine::RenderDevice
{
	struct ColorBlendParams final
	{
		BlendFactor sourceColorBlendFactor = BlendFactor::One;
		BlendFactor destinationColorBlendFactor = BlendFactor::Zero;
		BlendOperation colorBlendOperation = BlendOperation::Add;
		BlendFactor sourceAlphaBlendFactor = BlendFactor::One;
		BlendFactor destinationAlphaBlendFactor = BlendFactor::Zero;
		BlendOperation alphaBlendOperation = BlendOperation::Add;
	};

	struct RenderTargetBlendParams final
	{
		std::optional<ColorBlendParams> blend;
		ColorComponentMask colorComponentWriteMask = ColorComponentMask::All;
	};

	struct LogicRenderTargetBlendParams final
	{
		ColorComponentMask colorComponentWriteMask = ColorComponentMask::All;
	};

	struct BlendGroupParams final
	{
		std::span<const RenderTargetBlendParams> renderTargetBlend;
	};

	struct LogicBlendGroupParams final
	{
		LogicOperation logicOperation;
		std::span<const LogicRenderTargetBlendParams> renderTargetBlend;
	};

	struct BlendParams final
	{
		std::variant<BlendGroupParams, LogicBlendGroupParams> blendGroup;
	};
}
