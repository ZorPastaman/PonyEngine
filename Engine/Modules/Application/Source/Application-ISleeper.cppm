/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Body.h"

export module PonyEngine.Application:ISleeper;

import std;

import PonyEngine.Chrono;

export namespace PonyEngine::Application
{
	/// @brief Puts a thread into a sleep.
	/// @details It uses a high resolution timer for waiting.
	class ISleeper
	{
		PONY_INTERFACE_BODY(ISleeper)

		/// @brief Sleeps until the target time point.
		/// @param target Target time point.
		/// @return Sleep result.
		/// @note It mustn't be called if the sleeper is in a sleep phase.
		virtual void SleepUntil(std::chrono::time_point<std::chrono::steady_clock> target) = 0;
		/// @brief Sleeps for the requested duration.
		/// @param duration Duration.
		/// @return Sleep result.
		/// @note It mustn't be called if the sleeper is in a sleep phase.
		virtual void SleepFor(std::chrono::nanoseconds duration) = 0;
		/// @brief Sleeps for some seconds.
		/// @tparam T Duration type.
		/// @param duration Duration in seconds.
		/// @return Sleep result.
		/// @note It mustn't be called if the sleeper is in a sleep phase.
		template<std::floating_point T>
		void SleepForSeconds(T duration);
	};
}

namespace PonyEngine::Application
{
	template<std::floating_point T>
	void ISleeper::SleepForSeconds(const T duration)
	{
		return SleepFor(Chrono::ToDuration<std::chrono::nanoseconds>(duration));
	}
}
