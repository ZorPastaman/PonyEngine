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
	/// @brief Layout of a render target view that points to a non-array non-ms render target texture.
	struct SingleRTVLayout final
	{
		std::uint8_t mipIndex = 0u; ///< Mip index.
	};

	/// @brief Layout of a render target view that points to an array non-ms render target texture.
	struct ArrayRTVLayout final
	{
		ArrayRange arrayRange; ///< Array range.
		std::uint8_t mipIndex = 0u; ///< Mip index.
	};

	/// @brief Layout of a render target view that points to a non-array ms render target texture.
	struct MultiSampleRTVLayout final
	{
	};

	/// @brief Layout of a render target view that points to an array ms render target texture.
	struct MultiSampleArrayRTVLayout final
	{
		ArrayRange arrayRange; ///< Array range.
	};

	using RTVLayout = std::variant<SingleRTVLayout, ArrayRTVLayout, MultiSampleRTVLayout, MultiSampleArrayRTVLayout>; ///< Render target view layout.
}
