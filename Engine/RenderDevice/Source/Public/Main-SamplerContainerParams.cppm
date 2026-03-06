/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerContainerParams;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sampler container parameters.
	struct SamplerContainerParams final
	{
		std::uint32_t size = 1u; ///< Container size.
		bool shaderVisible = false; ///< Is it shader visible?
	};
}
