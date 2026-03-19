/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerBinding;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sampler binding.
	struct SamplerBinding final
	{
		std::uint32_t layoutSetIndex = 0u; ///< Layout set index in a bound pipeline state.
		std::uint32_t containerIndex = 0u; ///< Sampler index in a bound container.
	};
}
