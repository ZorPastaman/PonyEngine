/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureFormatSupport;

import :Aspect;
import :BlendMode;
import :ShaderOperation;
import :TextureDimension;
import :TextureUsage;
import :TextureViewDimension;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture format support.
	struct TextureFormatSupport final
	{
		TextureDimensionMask dimensions = TextureDimensionMask::None; ///< Supported dimension.
		TextureViewDimensionMask viewDimensions = TextureViewDimensionMask::None; ///< Supported view dimension.
		AspectMask aspects = AspectMask::None; ///< Supported aspects.
		TextureUsage usage = TextureUsage::None; ///< Supported usage.
		bool srgb = false; ///< Is the format srgb-compatible?
		bool swapChain = false; ///< Can it be used for a swap chain buffer?
		ShaderOperationMask shaderOperations = ShaderOperationMask::None; ///< Supported shader operations.
		BlendModeMask blendModes = BlendModeMask::None; ///< Supported blend modes.
		bool supported = false; ///< Does the current backend support a format at all?
	};
}
