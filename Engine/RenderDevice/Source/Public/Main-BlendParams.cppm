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
	/// @brief Color blend parameters.
	struct ColorBlendParams final
	{
		BlendFactor sourceColorBlendFactor = BlendFactor::One; ///< Source color blend factor.
		BlendFactor destinationColorBlendFactor = BlendFactor::Zero; ///< Destination color blend factor.
		BlendOperation colorBlendOperation = BlendOperation::Add; ///< Color blend operation.
		BlendFactor sourceAlphaBlendFactor = BlendFactor::One; ///< Source alpha blend factor.
		BlendFactor destinationAlphaBlendFactor = BlendFactor::Zero; ///< Destination alpha blend factor.
		BlendOperation alphaBlendOperation = BlendOperation::Add; ///< Alpha blend operation.
	};

	/// @brief Arithmetic render target blend parameters.
	struct ArithmeticRenderTargetBlendParams final
	{
		std::optional<ColorBlendParams> blend; ///< Blend parameters. If nullopt, no blending is done.
		ColorComponentMask colorComponentWriteMask = ColorComponentMask::All; ///< Color component write mask.
	};

	/// @brief Logic render target blend parameters.
	struct LogicRenderTargetBlendParams final
	{
		ColorComponentMask colorComponentWriteMask = ColorComponentMask::All; ///< Color component write mask.
	};

	/// @brief Arithmetic blend group parameters.
	struct ArithmeticBlendGroupParams final
	{
		std::span<const ArithmeticRenderTargetBlendParams> renderTargetBlend; ///< Render target blends. Its count must be synced with the render target format count.
	};

	/// @brief Logic blend group parameters.
	struct LogicBlendGroupParams final
	{
		LogicOperation logicOperation; ///< Logic operation.
		std::span<const LogicRenderTargetBlendParams> renderTargetBlend; ///< Render target blends. Its count must be synced with the render target format count.
	};

	/// @brief Blend parameters.
	struct BlendParams final
	{
		std::variant<ArithmeticBlendGroupParams, LogicBlendGroupParams> blendGroup; ///< Blend group.
	};
}
