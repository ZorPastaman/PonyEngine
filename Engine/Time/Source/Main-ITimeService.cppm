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

		/// @brief Gets a real time elapsed since the start. It computes a time at the call moment.
		/// @return Real time.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds NowTime() const noexcept = 0;

		/// @brief Gets a real time elapsed since the start.
		/// @return Real time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealTime() const noexcept = 0;
		/// @brief Gets a virtual time elapsed since the start.
		/// @return Virtual time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualTime() const noexcept = 0;
		/// @brief Gets an unscaled virtual time elapsed since the start.
		/// @return Unscaled virtual time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualTime() const noexcept = 0;

		/// @brief Gets a real fixed step count elapsed since the start.
		/// @return Real fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFixedStepCount() const noexcept = 0;
		/// @brief Gets a virtual fixed step count elapsed since the start.
		/// @return Virtual fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFixedStepCount() const noexcept = 0;
		/// @brief Gets an unscaled virtual fixed step count elapsed since the start.
		/// @return Unscaled virtual fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFixedStepCount() const noexcept = 0;

		/// @brief Gets a real time elapsed since a previous tick.
		/// @return Real delta time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds RealDeltaTime() const noexcept = 0;
		/// @brief Gets a virtual time elapsed since a previous tick.
		/// @return Virtual delta time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds VirtualDeltaTime() const noexcept = 0;
		/// @brief Gets an unscaled virtual time elapsed since a previous tick.
		/// @return Unscaled virtual delta time.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds UnscaledVirtualDeltaTime() const noexcept = 0;

		/// @brief Gets a real fixed step count elapsed since a previous tick.
		/// @return Real delta fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaFixedStepCount() const noexcept = 0;
		/// @brief Gets a virtual fixed step count elapsed since a previous tick.
		/// @return Virtual delta fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaFixedStepCount() const noexcept = 0;
		/// @brief Gets an unscaled virtual fixed step count elapsed since a previous tick.
		/// @return Unscaled virtual delta fixed step count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaFixedStepCount() const noexcept = 0;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Delta time cap.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p DeltaTimeCap() setter function.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds DeltaTimeCap() const noexcept = 0;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param cap Delta time cap to set.
		/// @note The function is not thread-safe.
		virtual void DeltaTimeCap(std::chrono::nanoseconds cap) noexcept = 0;

		/// @brief Gets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Time scale.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p TimeScale() setter function.
		[[nodiscard("Pure function")]]
		virtual double TimeScale() const noexcept = 0;
		/// @brief Sets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param scale Timescale to set.
		/// @note The function is not thread-safe.
		virtual void TimeScale(double scale) noexcept = 0;

		/// @brief Gets the fixed step period.
		/// @details Every such period elapsed increments a delta fixed step count.
		/// @return Fixed step period.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p FixedStepPeriod() setter function.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds FixedStepPeriod() const noexcept = 0;
		/// @brief Sets the fixed step period.
		/// @details Every such period elapsed increments a delta fixed step count.
		/// @param period Fixed step period to set.
		/// @note The function is not thread-safe.
		virtual void FixedStepPeriod(std::chrono::nanoseconds period) noexcept = 0;

		/// @brief Gets the target frame time.
		/// @return Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function may be called concurrently but mustn't be called concurrently with @p TargetFrameTime() setter function.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds TargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function is not thread-safe.
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) noexcept = 0;

		/// @brief Gets a time point when the service initialized.
		/// @return Time point when the service initialized.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept = 0;
		/// @brief Gets a time point when this frame started.
		/// @return Time point when this started.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> FrameTimePoint() const noexcept = 0;
		/// @brief Gets a current real time point.
		/// @return Real time point.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> NowTimePoint() const noexcept = 0;

		/// @brief Gets a real time elapsed since the start. It computes a time at the call moment.
		/// @tparam T Value type.
		/// @return Real time in seconds.
		/// @note The function is thread-safe.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T NowTimeSeconds() const noexcept;

		/// @brief Gets a real time elapsed since the start.
		/// @tparam T Value type.
		/// @return Real time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T RealTimeSeconds() const noexcept;
		/// @brief Gets a virtual time elapsed since the start.
		/// @tparam T Value type.
		/// @return Virtual time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T VirtualTimeSeconds() const noexcept;
		/// @brief Gets an unscaled virtual time elapsed since the start.
		/// @tparam T Value type.
		/// @return Unscaled virtual time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T UnscaledVirtualTimeSeconds() const noexcept;

		/// @brief Gets a real time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Real delta time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T RealDeltaTimeSeconds() const noexcept;
		/// @brief Gets a virtual time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Virtual delta time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T VirtualDeltaTimeSeconds() const noexcept;
		/// @brief Gets an unscaled virtual time elapsed since a previous tick.
		/// @tparam T Value type.
		/// @return Unscaled delta virtual time in seconds.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T UnscaledVirtualDeltaTimeSeconds() const noexcept;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @return Delta time cap in seconds.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p DeltaTimeCap() setter function.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T DeltaTimeCapSeconds() const noexcept;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param cap Delta time cap in seconds to set.
		/// @note The function is not thread-safe.
		template<std::floating_point T>
		void DeltaTimeCapSeconds(T cap);

		/// @brief Gets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @return Time scale.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p TimeScale() setter function.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T TimeScale() const noexcept;
		/// @brief Sets the timescale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @tparam T Value type.
		/// @param scale Timescale to set.
		/// @note The function is not thread-safe.
		template<std::floating_point T>
		void TimeScale(T scale);

		/// @brief Gets the fixed step period.
		/// @details Every such period elapsed increments a delta fixed step count.
		/// @tparam T Value type.
		/// @return Fixed step period in seconds.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p FixedStepPeriod() setter function.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T FixedStepPeriodSeconds() const noexcept;
		/// @brief Sets the fixed step period.
		/// @details Every such period elapsed increments a delta fixed step count.
		/// @tparam T Value type.
		/// @param period Fixed step period in seconds to set.
		/// @note The function is not thread-safe.
		template<std::floating_point T>
		void FixedStepPeriodSeconds(T period);

		/// @brief Gets the target frame time.
		/// @tparam T Value type.
		/// @return Target frame time in seconds. 0 or less means no target frame time (it's not restricted).
		/// @note The function may be called concurrently but mustn't be called concurrently with @p TargetFrameTime() setter function.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T TargetFrameTimeSeconds() const noexcept;
		/// @brief Sets the target frame time.
		/// @tparam T Value type.
		/// @param frameTime Target frame time in seconds. 0 or less means no target frame time (it's not restricted).
		/// @note The function is not thread-safe.
		template<std::floating_point T>
		void TargetFrameTimeSeconds(T frameTime);
	};
}

namespace PonyEngine::Time
{
	template<std::floating_point T>
	T ITimeService::NowTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(NowTime());
	}

	template<std::floating_point T>
	T ITimeService::RealTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(RealTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(VirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(UnscaledVirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::RealDeltaTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(RealDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualDeltaTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(VirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualDeltaTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(UnscaledVirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::DeltaTimeCapSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(DeltaTimeCap());
	}

	template<std::floating_point T>
	void ITimeService::DeltaTimeCapSeconds(const T cap)
	{
		DeltaTimeCap(Chrono::ToDuration<std::chrono::nanoseconds>(cap));
	}

	template<std::floating_point T>
	T ITimeService::TimeScale() const noexcept
	{
		return static_cast<T>(TimeScale());
	}

	template<std::floating_point T>
	void ITimeService::TimeScale(const T scale)
	{
		TimeScale(static_cast<double>(scale));
	}

	template<std::floating_point T>
	T ITimeService::FixedStepPeriodSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(FixedStepPeriod());
	}

	template<std::floating_point T>
	void ITimeService::FixedStepPeriodSeconds(const T period)
	{
		FixedStepPeriod(Chrono::ToDuration<std::chrono::nanoseconds>(period));
	}

	template<std::floating_point T>
	T ITimeService::TargetFrameTimeSeconds() const noexcept
	{
		return Chrono::ToSeconds<T>(TargetFrameTime());
	}

	template<std::floating_point T>
	void ITimeService::TargetFrameTimeSeconds(const T frameTime)
	{
		TargetFrameTime(Chrono::ToDuration<std::chrono::nanoseconds>(frameTime));
	}
}
