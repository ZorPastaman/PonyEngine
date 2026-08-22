/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Application:ThreadParams;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Application
{
	/// @brief Thread parameters.
	struct ThreadParams final
	{
		std::string_view role = ""; ///< Thread role. Must be valid. Empty role means a default role.
		Log::ILogService* logService = nullptr; ///< Log service that the thread must use in system calls. May be nullptr.
	};
}
