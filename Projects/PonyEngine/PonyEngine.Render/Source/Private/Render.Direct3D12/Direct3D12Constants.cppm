/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12Constants;

export namespace PonyEngine::Render
{
	constexpr DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D32_FLOAT; ///< Default depth stencil format.
	constexpr FLOAT MinDepth = D3D12_MIN_DEPTH; ///< Default minimal depth value.
	constexpr FLOAT MaxDepth = D3D12_MAX_DEPTH; ///< Default maximum depth value.
	constexpr UINT8 Stencil = 0u; ///< Default stencil value.

	constexpr auto SampleDescription = DXGI_SAMPLE_DESC{.Count = 1u, .Quality = 0u}; ///< Default sample description.
}
