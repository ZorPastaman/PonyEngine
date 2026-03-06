/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerParams;

import :SamplerAddressMode;
import :SamplerFilter;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sampler parameters.
	struct SamplerParams final
	{
		SamplerFilter filter; ///< Sampler filter.
		SamplerAddressMode addressU = SamplerAddressMode::Wrap; ///< Address mode of a texture U-coordinate.
		SamplerAddressMode addressV = SamplerAddressMode::Wrap; ///< Address mode of a texture V-coordinate.
		SamplerAddressMode addressW = SamplerAddressMode::Wrap; ///< Address mode of a texture W-coordinate.
		float mipLodBias = 0.f; ///< Mip lod bias.
		float minLod = 0.f; ///< Minimal lod.
		float maxLod = 0.f; ///< Maximal lod.
	};
}
