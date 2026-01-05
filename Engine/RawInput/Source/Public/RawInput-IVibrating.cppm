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

export module PonyEngine.RawInput:IVibrating;

export namespace PonyEngine::Input
{
	/// @brief Vibrating input device feature.
	class IVibrating
	{
		PONY_INTERFACE_BODY(IVibrating)

		/// @brief Sets a vibration state.
		/// @param lowFrequency Low frequency motor speed. Must be in range [0, 1].
		/// @param highFrequency High frequency motor speed. Must be in range [0, 1].
		virtual void Vibrate(float lowFrequency, float highFrequency) = 0;
	};
}
