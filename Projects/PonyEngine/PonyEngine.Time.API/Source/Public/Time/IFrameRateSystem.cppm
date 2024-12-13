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

export module PonyEngine.Time:IFrameRateSystem;

export namespace PonyEngine::Time
{
	/// @brief System that controls a frame rate of an engine.
	class IFrameRateSystem
	{
		INTERFACE_BODY(IFrameRateSystem)

		/// @brief Gets the target frame time.
		/// @return Target frame time in seconds. 0 means no target frame time (it's not restricted).
		[[nodiscard("Pure function")]]
		virtual float TargetFrameTime() const noexcept = 0;
		/// @brief Sets the target frame time.
		/// @param frameTime Target frame time in seconds. 0 means no target frame time (it's not restricted).
		virtual void TargetFrameTime(float frameTime) noexcept = 0;
	};
}
