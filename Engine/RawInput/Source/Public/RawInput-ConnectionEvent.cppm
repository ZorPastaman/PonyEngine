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

export namespace PonyEngine::Input
{
	/// @brief Connection event.
	struct ConnectionEvent final
	{
		bool isConnected = false; ///< Is connected?
		/// @brief Time point when the event was created.
		/// @remark Different devices use different clocks. So, it can be used only to approximately compare what input was earlier or something like that.
		std::chrono::time_point<std::chrono::steady_clock> timePoint;
	};
}
