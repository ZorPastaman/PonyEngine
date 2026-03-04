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
	/// @brief Layout of a depth stencil view that points to a non-array non-ms depth stencil texture.
	struct SingleDSVLayout final
	{
		std::uint8_t mipIndex = 0u; ///< Mip index.
	};

	/// @brief Layout of a depth stencil view that points to an array non-ms depth stencil texture.
	struct ArrayDSVLayout final
	{
		ArrayRange arrayRange; ///< Array range.
		std::uint8_t mipIndex = 0u; ///< Mip index.
	};

	/// @brief Layout of a depth stencil view that points to a non-array ms depth stencil texture.
	struct MultiSampleDSVLayout final
	{
	};

	/// @brief Layout of a depth stencil view that points to an array ms depth stencil texture.
	struct MultiSampleArrayDSVLayout final
	{
		ArrayRange arrayRange;
	};

	using DSVLayout = std::variant<SingleDSVLayout, ArrayDSVLayout, MultiSampleDSVLayout, MultiSampleArrayDSVLayout>; ///< Depth stencil view layout.
}
