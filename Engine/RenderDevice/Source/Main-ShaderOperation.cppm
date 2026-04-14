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

export module PonyEngine.RenderDevice:ShaderOperation;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader operation.
	enum class ShaderOperation : std::uint8_t
	{
		ShaderLoad,
		ShaderSample,
		ShaderSampleComparison,
		ShaderGather,
		ShaderGatherComparison,
		UnorderedAccessAtomicAdd,
		UnorderedAccessAtomicBitwise,
		UnorderedAccessAtomicExchange,
		UnorderedAccessAtomicExchangeComparison,
		UnorderedAccessAtomicSignedMinMax,
		UnorderedAccessAtomicUnsignedMinMax,
		UnorderedAccessLoad,
		UnorderedAccessStore
	};

	/// @brief Shader operation mask.
	enum class ShaderOperationMask : std::uint16_t
	{
		None = 0,
		ShaderLoad = 1 << 0,
		ShaderSample = 1 << 1,
		ShaderSampleComparison = 1 << 2,
		ShaderGather = 1 << 3,
		ShaderGatherComparison = 1 << 4,
		UnorderedAccessAtomicAdd = 1 << 5,
		UnorderedAccessAtomicBitwise = 1 << 6,
		UnorderedAccessAtomicExchange = 1 << 7,
		UnorderedAccessAtomicExchangeComparison = 1 << 8,
		UnorderedAccessAtomicSignedMinMax = 1 << 9,
		UnorderedAccessAtomicUnsignedMinMax = 1 << 10,
		UnorderedAccessLoad = 1 << 11,
		UnorderedAccessStore = 1 << 12,
		All = (1 << 13) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(ShaderOperation, ShaderOperationMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Shader operation names.
	constexpr std::array<std::string_view, 13> ShaderOperationNames
	{
		"ShaderLoad",
		"ShaderSample",
		"ShaderSampleComparison",
		"ShaderGather",
		"ShaderGatherComparison",
		"UnorderedAccessAtomicAdd",
		"UnorderedAccessAtomicBitwise",
		"UnorderedAccessAtomicExchange",
		"UnorderedAccessAtomicExchangeComparison",
		"UnorderedAccessAtomicSignedMinMax",
		"UnorderedAccessAtomicUnsignedMinMax",
		"UnorderedAccessLoad",
		"UnorderedAccessStore"
	};
}

export 
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::ShaderOperation, PonyEngine::RenderDevice::ShaderOperationMask, PonyEngine::RenderDevice::ShaderOperationNames)
}
