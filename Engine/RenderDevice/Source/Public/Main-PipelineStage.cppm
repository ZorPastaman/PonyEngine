/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.RenderDevice:PipelineStage;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Pipeline stage.
	enum class PipelineStage : std::uint8_t
	{
		VertexShading,
		PixelShading,
		RenderTarget,
		DepthStencil,
		ComputeShading,
		Copy,
		Resolve,
		UnorderedAccessClearing
	};

	/// @brief Pipeline stage mask.
	enum class PipelineStageMask : std::uint8_t
	{
		None = 0,
		VertexShading = 1 << 0,
		PixelShading = 1 << 1,
		RenderTarget = 1 << 2,
		DepthStencil = 1 << 3,
		ComputeShading = 1 << 4,
		Copy = 1 << 5,
		Resolve = 1 << 6,
		UnorderedAccessClearing = 1 << 7,
		All = (1 << 8) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(PipelineStage, PipelineStageMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Pipeline stage names.
	constexpr std::array<std::string_view, 8> PipelineStageNames
	{
		"VertexShading",
		"PixelShading",
		"RenderTarget",
		"DepthStencil",
		"ComputeShading",
		"Copy",
		"Resolve",
		"UnorderedAccessClearing"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::PipelineStage, PonyEngine::RenderDevice::PipelineStageMask, PonyEngine::RenderDevice::PipelineStageNames)
}
