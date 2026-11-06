/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Thread:Spin;

import std;

import PonyEngine.Chrono;

export namespace PonyEngine::Thread
{
	/// @brief Spins the thread till the clock reaches the target time point.
	/// @tparam Clock Clock type.
	/// @tparam Duration Duration type.
	/// @param target Target time point.
	/// @return Time point at which the spin has finished.
	template<Chrono::Clock Clock = std::chrono::steady_clock, typename Duration = Clock::duration> requires std::three_way_comparable_with<Duration, typename Clock::duration>
	std::chrono::time_point<Clock> SpinUntil(std::chrono::time_point<Clock, Duration> target) noexcept;
	/// @brief Spins the thread for the duration.
	/// @tparam Clock Clock type.
	/// @tparam Duration Duration type.
	/// @param duration Duration.
	/// @return Time point at which the spin has finished.
	template<Chrono::Clock Clock = std::chrono::steady_clock, typename Duration = Clock::duration> requires std::three_way_comparable_with<Duration, typename Clock::duration>
	std::chrono::time_point<Clock> SpinFor(Duration duration) noexcept;
	/// @brief Spins the thread for some seconds.
	/// @tparam Clock Clock type.
	/// @tparam T Duration type.
	/// @param duration Duration in seconds.
	/// @return Time point at which the spin has finished.
	template<Chrono::Clock Clock = std::chrono::steady_clock, std::floating_point T>
	std::chrono::time_point<Clock> SpinForSeconds(T duration) noexcept;
}

namespace PonyEngine::Thread
{
	template<Chrono::Clock Clock, typename Duration> requires std::three_way_comparable_with<Duration, typename Clock::duration>
	std::chrono::time_point<Clock> SpinUntil(const std::chrono::time_point<Clock, Duration> target) noexcept
	{
		std::chrono::time_point<Clock> now;
		do
		{
			now = Clock::now();
		} while (now < target);

		return now;
	}

	template<Chrono::Clock Clock, typename Duration> requires std::three_way_comparable_with<Duration, typename Clock::duration>
	std::chrono::time_point<Clock> SpinFor(const Duration duration) noexcept
	{
		return SpinUntil(Clock::now() + duration);
	}

	template<Chrono::Clock Clock, std::floating_point T>
	std::chrono::time_point<Clock> SpinForSeconds(const T duration) noexcept
	{
		return SpinFor(Chrono::ToDuration<Clock::duration>(duration));
	}
}
