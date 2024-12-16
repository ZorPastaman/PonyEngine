/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Time:TimeSystemParams;

export namespace PonyEngine::Time
{
	/// @brief Time system parameters.
	struct TimeSystemParams final
	{
		float deltaTimeCap = 0.1f; ///< Delta time cap.
		float timeScale = 1.f; ///< Time scale.
		float framePeriod = 1.f / 60.f; ///< Frame period.
	};
}
