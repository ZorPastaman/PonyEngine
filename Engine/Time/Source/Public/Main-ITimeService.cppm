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

import :Utility;

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

		/// @brief Gets a real frame count elapsed since the start.
		/// @return Real frame count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFrameCount() const noexcept = 0;
		/// @brief Gets a virtual frame count elapsed since the start.
		/// @return Virtual frame count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFrameCount() const noexcept = 0;
		/// @brief Gets an unscaled virtual frame count elapsed since the start.
		/// @return Unscaled virtual frame count.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFrameCount() const noexcept = 0;

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

		/// @brief Gets a real frame count elapsed since a previous tick.
		/// @return Real delta frame.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealDeltaFrame() const noexcept = 0;
		/// @brief Gets a virtual frame count elapsed since a previous tick.
		/// @return Virtual delta frame.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualDeltaFrame() const noexcept = 0;
		/// @brief Gets an unscaled virtual frame count elapsed since a previous tick.
		/// @return Unscaled virtual delta frame.
		/// @note The function may be called concurrently but mustn't be called during the time service tick.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualDeltaFrame() const noexcept = 0;

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

		/// @brief Gets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @return Frame period.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p FramePeriod() setter function.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds FramePeriod() const noexcept = 0;
		/// @brief Sets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @param period Frame period to set.
		/// @note The function is not thread-safe.
		virtual void FramePeriod(std::chrono::nanoseconds period) noexcept = 0;

		/// @brief Gets the target frame time.
		/// @return Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function may be called concurrently but mustn't be called concurrently with @p TargetFrameTime() setter function.
		[[nodiscard("Pure function")]]
		virtual std::chrono::nanoseconds TargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time. 0 or less means no target frame time (it's not restricted).
		/// @note The function is not thread-safe.
		virtual void TargetFrameTime(std::chrono::nanoseconds frameTime) = 0;

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

		/// @brief Gets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @tparam T Value type.
		/// @return Frame period in seconds.
		/// @note The function may be called concurrently but mustn't be called concurrently with @p FramePeriod() setter function.
		template<std::floating_point T = double> [[nodiscard("Pure function")]]
		T FramePeriodSeconds() const noexcept;
		/// @brief Sets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @tparam T Value type.
		/// @param period Frame period in seconds to set.
		/// @note The function is not thread-safe.
		template<std::floating_point T>
		void FramePeriodSeconds(T period);

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
		return ToSeconds<T>(NowTime());
	}

	template<std::floating_point T>
	T ITimeService::RealTimeSeconds() const noexcept
	{
		return ToSeconds<T>(RealTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualTimeSeconds() const noexcept
	{
		return ToSeconds<T>(VirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualTimeSeconds() const noexcept
	{
		return ToSeconds<T>(UnscaledVirtualTime());
	}

	template<std::floating_point T>
	T ITimeService::RealDeltaTimeSeconds() const noexcept
	{
		return ToSeconds<T>(RealDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::VirtualDeltaTimeSeconds() const noexcept
	{
		return ToSeconds<T>(VirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::UnscaledVirtualDeltaTimeSeconds() const noexcept
	{
		return ToSeconds<T>(UnscaledVirtualDeltaTime());
	}

	template<std::floating_point T>
	T ITimeService::DeltaTimeCapSeconds() const noexcept
	{
		return ToSeconds<T>(DeltaTimeCap());
	}

	template<std::floating_point T>
	void ITimeService::DeltaTimeCapSeconds(const T cap)
	{
		DeltaTimeCap(ToDuration<std::chrono::nanoseconds>(cap));
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
	T ITimeService::FramePeriodSeconds() const noexcept
	{
		return ToSeconds<T>(FramePeriod());
	}

	template<std::floating_point T>
	void ITimeService::FramePeriodSeconds(const T period)
	{
		FramePeriod(ToDuration<std::chrono::nanoseconds>(period));
	}

	template<std::floating_point T>
	T ITimeService::TargetFrameTimeSeconds() const noexcept
	{
		return ToSeconds<T>(TargetFrameTime());
	}

	template<std::floating_point T>
	void ITimeService::TargetFrameTimeSeconds(const T frameTime)
	{
		TargetFrameTime(ToDuration<std::chrono::nanoseconds>(frameTime));
	}
}
