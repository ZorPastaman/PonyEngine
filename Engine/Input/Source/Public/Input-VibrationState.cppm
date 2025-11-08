/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:VibrationState;

export namespace PonyEngine::Input
{
	/// @brief Vibration state.
	struct VibrationState final
	{
		float lowFrequency = 0.f; ///< Low frequency motor speed. Must be in range [0, 1].
		float highFrequency = 0.f; ///< High frequency motor speed. Must be in range [0, 1].
	};
}
