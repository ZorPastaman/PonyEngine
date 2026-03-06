/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SRVLayout;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
	/// @brief Layout of a shader resource view that points to a non-array non-ms texture.
	struct SingleSRVLayout final
	{
		MipRange mipRange;
	};

	/// @brief Layout of a shader resource view that points to an array non-ms texture.
	struct ArraySRVLayout final
	{
		ArrayRange arrayRange;
		MipRange mipRange;
	};

	/// @brief Layout of a shader resource view that points to a non-array ms texture.
	struct MultiSampleSRVLayout final
	{
	};

	/// @brief Layout of a shader resource view that points to an array ms texture.
	struct MultiSampleArraySRVLayout final
	{
		ArrayRange arrayRange;
	};

	using SRVLayout = std::variant<SingleSRVLayout, ArraySRVLayout, MultiSampleSRVLayout, MultiSampleArraySRVLayout>; ///< Shader resource view layout.
}
