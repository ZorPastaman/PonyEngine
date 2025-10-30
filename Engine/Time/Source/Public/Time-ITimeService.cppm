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

export namespace PonyEngine::Time
{
	/// @brief Time service.
	class ITimeService
	{
		INTERFACE_BODY(ITimeService)

		/// @brief Gets a real time elapsed since the start. It computes a time at the call moment.
		/// @return Real time in seconds.
		[[nodiscard("Pure function")]]
		virtual double NowTime() const noexcept = 0;

		/// @brief Gets a real time elapsed since the start.
		/// @return Real time in seconds.
		[[nodiscard("Pure function")]]
		virtual double RealTime() const noexcept = 0;
		/// @brief Gets a virtual time elapsed since the start.
		/// @return Virtual time in seconds.
		[[nodiscard("Pure function")]]
		virtual double VirtualTime() const noexcept = 0;
		/// @brief Gets an unscaled virtual time elapsed since the start.
		/// @return Unscaled virtual time in seconds.
		[[nodiscard("Pure function")]]
		virtual double UnscaledVirtualTime() const noexcept = 0;

		/// @brief Gets a real frame count elapsed since the start.
		/// @return Real frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t RealFrameCount() const noexcept = 0;
		/// @brief Gets a virtual frame count elapsed since the start.
		/// @return Virtual frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t VirtualFrameCount() const noexcept = 0;
		/// @brief Gets an unscaled virtual frame count elapsed since the start.
		/// @return Unscaled virtual frame count.
		[[nodiscard("Pure function")]]
		virtual std::uint64_t UnscaledVirtualFrameCount() const noexcept = 0;

		/// @brief Gets a real time elapsed since a previous tick.
		/// @return Real delta time in seconds.
		[[nodiscard("Pure function")]]
		virtual float RealDeltaTime() const noexcept = 0;
		/// @brief Gets a virtual time elapsed since a previous tick.
		/// @return Virtual delta time in seconds.
		[[nodiscard("Pure function")]]
		virtual float VirtualDeltaTime() const noexcept = 0;
		/// @brief Gets an unscaled virtual time elapsed since a previous tick.
		/// @return Unscaled virtual delta time in seconds.
		[[nodiscard("Pure function")]]
		virtual float UnscaledVirtualDeltaTime() const noexcept = 0;

		/// @brief Gets a real frame count elapsed since a previous tick.
		/// @return Real delta frame.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t RealDeltaFrame() const noexcept = 0;
		/// @brief Gets a virtual frame count elapsed since a previous tick.
		/// @return Virtual delta frame.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t VirtualDeltaFrame() const noexcept = 0;
		/// @brief Gets an unscaled virtual frame count elapsed since a previous tick.
		/// @return Unscaled virtual delta frame.
		[[nodiscard("Pure function")]]
		virtual std::uint32_t UnscaledVirtualDeltaFrame() const noexcept = 0;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Delta time cap.
		[[nodiscard("Pure function")]]
		virtual float DeltaTimeCap() const noexcept = 0;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param cap Delta time cap to set.
		virtual void DeltaTimeCap(float cap) = 0;

		/// @brief Gets the time scale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @return Time scale.
		[[nodiscard("Pure function")]]
		virtual float TimeScale() const noexcept = 0;
		/// @brief Sets the time scale.
		/// @details It affects a virtual time only. Its delta can't exceed this value.
		/// @param scale Time scale to set.
		virtual void TimeScale(float scale) = 0;

		/// @brief Gets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @return Frame period.
		[[nodiscard("Pure function")]]
		virtual float FramePeriod() const noexcept = 0;
		/// @brief Sets the frame period.
		/// @details Every such period elapsed increments a delta frame.
		/// @param period Frame period to set.
		virtual void FramePeriod(float period) = 0;

		/// @brief Gets the target frame time.
		/// @return Target frame time in seconds. 0 or less means no target frame time (it's not restricted).
		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time in seconds. 0 or less means no target frame time (it's not restricted).
		virtual void TargetFrameTime(float frameTime) = 0;

		/// @brief Gets a time point when the service initialized.
		/// @return Time point when the service initialized.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> StartTimePoint() const noexcept = 0;
		/// @brief Gets a time point when this frame started.
		/// @return Time point when this started.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> FrameTimePoint() const noexcept = 0;
	};
}
