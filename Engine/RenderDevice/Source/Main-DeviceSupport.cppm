/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DeviceSupport;

import :FenceSupport;
import :RasterizerSupport;
import :ResourceSupport;
import :SamplerSupport;
import :ShaderSupport;
import :SwapChainSupport;
import :ViewSupport;

export namespace PonyEngine::RenderDevice
{
	/// @brief Device support.
	struct DeviceSupport final
	{
		ShaderSupport shaderSupport; ///< Shader support.
		ViewSupport viewSupport; ///< Resource view support.
		SamplerSupport samplerSupport; ///< Sampler support.
		RasterizerSupport rasterizerSupport; ///< Rasterizer support.
		SwapChainSupport swapChainSupport; ///< Swap chain support.
		ResourceSupport resourceSupport; ///< Resource support.
		FenceSupport fenceSupport; ///< Fence support.
	};
}
