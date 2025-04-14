/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:MSAA;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Multi sample anti-aliasing parameters.
	struct MSAA final
	{
		std::uint32_t sampleCount = 1; ///< Sample count.
		float sampleQuality = 1.f; ///< Sample quality. Must be in range [0, 1].
	};
}
