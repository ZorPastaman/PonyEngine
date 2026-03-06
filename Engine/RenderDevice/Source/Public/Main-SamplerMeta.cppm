/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerMeta;

import std;

import :SamplerParams;

export namespace PonyEngine::RenderDevice
{
	/// @brief Empty sampler meta. It means no sampler was created.
	struct EmptySamplerParams final
	{
	};

	using SamplerMeta = std::variant<EmptySamplerParams, SamplerParams>; ///< Sampler meta.
}
