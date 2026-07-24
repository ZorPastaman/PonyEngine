/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Time:ITimeService;

import std;

import PonyEngine.Chrono;

export namespace PonyEngine::Time
{
	/// @brief Time service.
	class ITimeService
	{
		PONY_INTERFACE_BODY(ITimeService)

		/// @brief Gets a real time elapsed since the start.
		/// @return Real time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealTime() const = 0;
		/// @brief Gets a virtual time elapsed since the start.
		/// @return Virtual time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualTime() const = 0;
		/// @brief Gets an unscaled virtual time elapsed since the start.
		/// @return Unscaled virtual time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualTime() const = 0;

		/// @brief Gets a real step count elapsed since the start.
		/// @return Real step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealStepCount() const = 0;
		/// @brief Gets a virtual step count elapsed since the start.
		/// @return Virtual step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualStepCount() const = 0;
		/// @brief Gets an unscaled virtual step count elapsed since the start.
		/// @return Unscaled virtual step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualStepCount() const = 0;

		/// @brief Gets a real time elapsed since a previous tick.
		/// @return Real delta time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const = 0;
		/// @brief Gets a virtual time elapsed since a previous tick.
		/// @return Virtual delta time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const = 0;
		/// @brief Gets an unscaled virtual time elapsed since a previous tick.
		/// @return Unscaled virtual delta time.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const = 0;

		/// @brief Gets a real step count elapsed since a previous tick.
		/// @return Real delta step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaStepCount() const = 0;
		/// @brief Gets a virtual step count elapsed since a previous tick.
		/// @return Virtual delta step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaStepCount() const = 0;
		/// @brief Gets an unscaled virtual step count elapsed since a previous tick.
		/// @return Unscaled virtual delta step count.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaStepCount() const = 0;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Delta time cap.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const = 0;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param cap Delta time cap to set.
		/// @note The function must be called on a main thread.
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) = 0;

		/// @brief Gets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Time scale.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual double TimeScale() const = 0;
		/// @brief Sets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param scale Timescale to set.
		/// @note The function must be called on a main thread.
		virtual void TimeScale(double scale) = 0;

		/// @brief Gets the step period.
		/// @details Every such period elapsed increments a delta step count.
		/// @return Step period.
		/// @note The function must be called on a main thread.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds StepPeriod() const = 0;
		/// @brief Sets the step period.
		/// @details Every such period elapsed increments a delta step count.
		/// @param period Step period to set.
		/// @note The function must be called on a main thread.
		virtual void StepPeriod(std::chrono::nanoseconds period) = 0;

		/// @brief Gets a real time elapsed since the start.
		/// @tparam T Value type.
		/// @return Real time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T RealTimeSeconds() const;
		/// @brief Gets a virtual time elapsed since the start.
		/// @tparam T Value type.
		/// @return Virtual time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T VirtualTimeSeconds() const;
		/// @brief Gets an unscaled virtual time elapsed since the start.
		/// @tparam T Value type.
		/// @return Unscaled virtual time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T UnscaledVirtualTimeSeconds() const;

		/// @brief Gets a real time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Real delta time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T RealDeltaTimeSeconds() const;
		/// @brief Gets a virtual time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Virtual delta time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T VirtualDeltaTimeSeconds() const;
		/// @brief Gets an unscaled virtual time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Unscaled delta virtual time in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T UnscaledVirtualDeltaTimeSeconds() const;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @return Delta time cap in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T DeltaTimeCapSeconds() const;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param cap Delta time cap in seconds to set.
		/// @note The function must be called on a main thread.
		template<std::floating_point T>
		void DeltaTimeCapSeconds(T cap);

		/// @brief Gets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @return Time scale.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T TimeScale() const;
		/// @brief Sets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @param scale Timescale to set.
		/// @note The function must be called on a main thread.
		template<std::floating_point T>
		void TimeScale(T scale);

		/// @brief Gets the step period.
		/// @details Every such period elapsed increments a delta step count.
		/// @tparam T Value type.
		/// @return Step period in seconds.
		/// @note The function must be called on a main thread.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T StepPeriodSeconds() const;
		/// @brief Sets the step period.
		/// @details Every such period elapsed increments a delta step count.
		/// @tparam T Value type.
		/// @param period Step period in seconds to set.
		/// @note The function must be called on a main thread.
		template<std::floating_point T>
		void StepPeriodSeconds(T period);
	};
}

namespace PonyEngine::Time
{
	template<std::floating_point T>
	T ITimeService::RealTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(RealTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(VirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(UnscaledVirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::RealDeltaTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(RealDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualDeltaTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(VirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualDeltaTimeSeconds() const
	{
		return Chrono::ToSeconds<T>(UnscaledVirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::DeltaTimeCapSeconds() const
	{
		return Chrono::ToSeconds<T>(DeltaTimeCap());
	}

	template<std::floating_point T>
	void ITimeService::DeltaTimeCapSeconds(const T cap)
	{
		DeltaTimeCap(Chrono::ToDuration<std::chrono::nanoseconds>(cap));
	}

	template<std::floating_point T>
	T ITimeService::TimeScale() const
	{
		return static_cast<T>(TimeScale());
	}

	template<std::floating_point T>
	void ITimeService::TimeScale(const T scale)
	{
		TimeScale(static_cast<double>(scale));
	}

	template<std::floating_point T>
	T ITimeService::StepPeriodSeconds() const
	{
		return Chrono::ToSeconds<T>(StepPeriod());
	}

	template<std::floating_point T>
	void ITimeService::StepPeriodSeconds(const T period)
	{
		StepPeriod(Chrono::ToDuration<std::chrono::nanoseconds>(period));
	}
}
