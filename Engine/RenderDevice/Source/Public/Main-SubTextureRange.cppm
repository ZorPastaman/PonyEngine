/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SubTextureRange;

import std;

import :Aspect;

export namespace PonyEngine::RenderDevice
{
	struct MipRange final
	{
		std::uint32_t mostDetailedMipIndex = 0u;
		std::optional<std::uint32_t> mipCount = std::nullopt;
	};

	struct ArrayRange final
	{
		std::uint32_t firstArrayIndex = 0u;
		std::optional<std::uint32_t> arrayCount = std::nullopt;
	};

	struct SubTextureRange final
	{
		MipRange mipRange;
		ArrayRange arrayRange;
		Aspect aspect = Aspect::Color;
	};
}
