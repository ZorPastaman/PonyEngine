/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DSVLayout;

import std;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	struct SingleDSVLayout final
	{
		std::uint32_t mipIndex = 0u;
	};
	struct ArrayDSVLayout final
	{
		std::uint32_t mipIndex = 0u;
		ArrayRange arrayRange;
	};
	struct MSDSVLayout final
	{
	};
	struct MSArrayDSVLayout final
	{
		ArrayRange arrayRange;
	};
	using DSVLayout = std::variant<SingleDSVLayout, ArrayDSVLayout, MSDSVLayout, MSArrayDSVLayout>;
}
