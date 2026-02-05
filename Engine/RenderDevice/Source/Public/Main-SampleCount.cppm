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

export module PonyEngine.RenderDevice:SampleCount;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class SampleCount : std::uint8_t
	{
		X1,
		X2,
		X4,
		X8,
		X16,
		X32,
		Max = X32
	};

	enum class SampleCountMask : std::uint8_t
	{
		None = 0,
		X1 = 1 << 0,
		X2 = 1 << 1,
		X4 = 1 << 2,
		X8 = 1 << 3,
		X16 = 1 << 4,
		X32 = 1 << 5,
		All = (1 << 6) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SampleCount, SampleCountMask)

	[[nodiscard("Pure function")]]
	constexpr std::uint8_t ToNumber(SampleCount count) noexcept;
}

namespace PonyEngine::RenderDevice
{
	constexpr std::uint8_t ToNumber(const SampleCount count) noexcept
	{
		return static_cast<std::uint8_t>(1u << std::to_underlying(count));
	}
}
