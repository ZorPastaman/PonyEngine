/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputType;

import <cstdint>;

export namespace PonyEngine::Input
{
	/// @brief Input type.
	enum class InputType : std::uint8_t
	{
		State, ///< Input state change. It's kept across ticks and can be only changed.
		Delta ///< Input delta. It's zeroed every tick and can only be added.
	};
}
