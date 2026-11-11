/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:ConnectionEvent;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Connection event.
	struct ConnectionEvent final
	{
		bool isConnected = false; ///< Is connected?
		std::chrono::time_point<std::chrono::steady_clock> timePoint; ///< Time point when the event was created.
	};
}
