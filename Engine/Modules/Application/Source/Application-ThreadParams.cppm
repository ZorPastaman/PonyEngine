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

export namespace PonyEngine::Application
{
	/// @brief Thread parameters.
	struct ThreadParams final
	{
		std::string_view role = ""; ///< Thread role. Must be valid. Empty role means a default role.
		std::move_only_function<bool(std::exception_ptr) noexcept> onBeginException; ///< Called if the thread start failed. If the return value is @a false, the thread is terminated.
		std::move_only_function<void(std::exception_ptr) noexcept> onEndException; ///< Called if the thread end failed.
	};
}
