/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:Utility;

import std;

export namespace PonyEngine::Time
{
	/// @brief Casts the duration to seconds.
	/// @tparam T Type representing seconds.
	/// @tparam Rep Type representing the number of ticks.
	/// @tparam Period Period type.
	/// @param duration Duration.
	/// @return Seconds.
	template<std::floating_point T = double, typename Rep, typename Period> [[nodiscard("Pure function")]]
	T ToSeconds(std::chrono::duration<Rep, Period> duration) noexcept;
	/// @brief Casts the seconds to a duration.
	/// @tparam Duration Duration type.
	/// @tparam T Type representing seconds.
	/// @param seconds Seconds.
	/// @return Duration
	template<typename Duration, std::floating_point T>
	Duration ToDuration(T seconds) noexcept;
}

namespace PonyEngine::Time
{
	template<std::floating_point T, typename Rep, typename Period>
	T ToSeconds(std::chrono::duration<Rep, Period> duration) noexcept
	{
		return std::chrono::duration_cast<std::chrono::duration<T>>(duration).count();
	}

	template<typename Duration, std::floating_point T>
	Duration ToDuration(const T seconds) noexcept
	{
		return std::chrono::duration_cast<Duration>(std::chrono::duration<T>(seconds));
	}
}
