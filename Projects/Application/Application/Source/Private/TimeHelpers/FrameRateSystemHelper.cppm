/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module TimeHelpers:FrameRateSystemHelper;

import PonyEngine.Time;

export namespace TimeHelpers
{
	/// @brief Sets target frame rate to the @p frameRateSystem.
	/// @param frameRateSystem Target frame rate system.
	void SetTargetFrameTime(PonyEngine::Time::IFrameRateSystem& frameRateSystem) noexcept;

	/// @brief Sets up the @p frameRateSystem.
	/// @param frameRateSystem Frame rate system to set up.
	void SetupFrameRateSystem(PonyEngine::Time::IFrameRateSystem& frameRateSystem) noexcept;
}

namespace TimeHelpers
{
	void SetTargetFrameTime(PonyEngine::Time::IFrameRateSystem& frameRateSystem) noexcept
	{
		frameRateSystem.TargetFrameTime(PonyEngine::Time::ConvertFrameRateFrameTime(60.f));
	}

	void SetupFrameRateSystem(PonyEngine::Time::IFrameRateSystem& frameRateSystem) noexcept
	{
		SetTargetFrameTime(frameRateSystem);
	}
}
