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

export module PonyEngine.Input:IVibrating;

import :VibrationState;

export namespace PonyEngine::Input
{
	/// @brief Vibrating input device feature.
	class IVibrating
	{
		INTERFACE_BODY(IVibrating)

		/// @brief Gets a vibration state.
		/// @return Vibration state.
		[[nodiscard("Pure function")]]
		virtual VibrationState State() const = 0;
		/// @brief Sets a vibration state.
		/// @param state Vibration state.
		virtual void State(const VibrationState& state) = 0;
	};
}
