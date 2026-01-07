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

export namespace PonyEngine::Render
{
	enum class SampleCount : std::uint8_t
	{
		X1,
		X2,
		X4,
		X8,
		X16,
		X32,
		X64,
		Max = X64
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
		X64 = 1 << 6,
		All = (1 << 7) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SampleCount, SampleCountMask)

	[[nodiscard("Pure function")]]
	std::uint8_t ToNumber(SampleCount count) noexcept;
}

namespace PonyEngine::Render
{
	std::uint8_t ToNumber(const SampleCount count) noexcept
	{
		return static_cast<std::uint8_t>(1u << std::to_underlying(count));
	}
}
