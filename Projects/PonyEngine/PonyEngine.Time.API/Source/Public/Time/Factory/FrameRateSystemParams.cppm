/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time.Factory:FrameRateSystemParams;

export namespace PonyEngine::Time
{
	/// @brief Frame rate system parameters.
	struct FrameRateSystemParams final
	{
		float targetFrameTime; ///< Target frame time.
	};
}
