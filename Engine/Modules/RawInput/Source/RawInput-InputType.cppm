/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:InputType;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Input event type.
	enum class InputType : std::uint8_t
	{
		State, ///< A value is kept till set to another value.
		Delta ///< A value is zeroed each tick.
	};
}
