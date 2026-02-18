/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RTVLayout;

import std;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	struct SingleRTVLayout final
	{
		std::uint8_t mipIndex = 0u;
	};
	struct ArrayRTVLayout final
	{
		ArrayRange arrayRange;
		std::uint8_t mipIndex = 0u;
	};
	struct MSRTVLayout final
	{
	};
	struct MSArrayRTVLayout final
	{
		ArrayRange arrayRange;
	};
	using RTVLayout = std::variant<SingleRTVLayout, ArrayRTVLayout, MSRTVLayout, MSArrayRTVLayout>;
}
