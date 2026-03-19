/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:UAVLayout;

import std;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	/// @brief Layout of an unordered access view that points to a non-array non-ms texture.
	struct SingleUAVLayout final
	{
		std::uint8_t mipIndex = 0u;
	};

	/// @brief Layout of an unordered access view that points to an array non-ms texture.
	struct ArrayUAVLayout final
	{
		ArrayRange arrayRange;
		std::uint8_t mipIndex = 0u;
	};

	using UAVLayout = std::variant<SingleUAVLayout, ArrayUAVLayout>; ///< Unordered access view layout.
}
