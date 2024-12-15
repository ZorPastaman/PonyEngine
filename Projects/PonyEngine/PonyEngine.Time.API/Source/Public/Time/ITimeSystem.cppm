/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Time:ITimeSystem;

import <cstdint>;
import <chrono>;

export namespace PonyEngine::Time
{
	/// @brief Time system.
	class ITimeSystem
	{
		INTERFACE_BODY(ITimeSystem)

		/// @brief Gets a real time elapsed since the engine start.
		/// @return Real time in seconds.
		[[nodiscard("Pure function")]]
		virtual double RealTime() const noexcept = 0;
		/// @brief Gets a virtual time elapsed since the engine start.
		/// @return Virtual time in seconds.
		[[nodiscard("Pure function")]]
		virtual double VirtualTime() const noexcept = 0;
		/// @brief Gets an unscaled virtual time elapsed since the engine start.
		/// @return Unscaled virtual time in seconds.
		[[nodiscard("Pure function")]]
		virtual double UnscaledVirtualTime() const noexcept = 0;
		/// @brief Gets a fixed time elapsed since the engine start.
		/// @return Fixed time in ticks.
		[[nodiscard("Pure function")]]
		virtual std::int64_t FixedTime() const noexcept = 0;

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
		/// @brief Gets a fixed time elapsed since a previous tick.
		/// @return Fixed delta time in ticks.
		[[nodiscard("Pure function")]]
		virtual std::int32_t FixedDeltaTime() const noexcept = 0;

		/// @brief Gets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value. The fixed time is dependent on the virtual time as well.
		/// @return Delta time cap.
		[[nodiscard("Pure function")]]
		virtual float DeltaTimeCap() const noexcept = 0;
		/// @brief Sets the delta time cap.
		/// @details It affects a virtual time only. Its delta can't exceed this value. The fixed time is dependent on the virtual time as well.
		/// @param cap Delta time cap to set.
		virtual void DeltaTimeCap(float cap) noexcept = 0;

		/// @brief Gets the time scale.
		/// @details It affects a virtual time only. Its delta can't exceed this value. The fixed time is dependent on the virtual time as well.
		/// @return Time scale.
		[[nodiscard("Pure function")]]
		virtual float TimeScale() const noexcept = 0;
		/// @brief Sets the time scale.
		/// @details It affects a virtual time only. Its delta can't exceed this value. The fixed time is dependent on the virtual time as well.
		/// @param scale Time scale to set.
		virtual void TimeScale(float scale) noexcept = 0;

		/// @brief Gets the fixed time period.
		/// @details Every such period elapsed increments a fixed delta time.
		/// @return Fixed time period.
		[[nodiscard("Pure function")]]
		virtual float FixedTimePeriod() const noexcept = 0;
		/// @brief Sets the fixed time period.
		/// @details Every such period elapsed increments a fixed delta time.
		/// @param period Fixed time period to set.
		virtual void FixedTimePeriod(float period) noexcept = 0;

		/// @brief Gets a time point when the engine started.
		/// @return Time point when the engine started.
		[[nodiscard("Pure function")]]
		virtual std::chrono::time_point<std::chrono::steady_clock> EngineStartTimePoint() const noexcept = 0;
	};
}
