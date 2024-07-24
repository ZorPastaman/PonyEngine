/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:Event;

import :KeyboardMessage;

export namespace PonyEngine::Input
{
	/// @brief Input event.
	struct Event final
	{
		[[nodiscard("Pure operator")]]
		bool operator ==(const Event& other) const noexcept = default;

		KeyboardMessage expectedMessage; ///< The event is raised if the input system receives such an event.
	};
}
