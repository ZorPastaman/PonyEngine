/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:BlendOperation;

import <cstdint>;

export namespace PonyEngine::Render
{
	/// @brief Blend operation.
	enum class BlendOperation : std::uint8_t
	{
		Add,
		Subtract,
		SubtractReverse,
		Min,
		Max
	};
}
