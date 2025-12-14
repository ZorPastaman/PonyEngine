/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/GamepadInput.h"

export module PonyEngine.RawInput.XInput.Impl:Windows.GamepadVibrator;

import PonyEngine.RawInput;

export namespace PonyEngine::Input::Windows
{
	class GamepadVibrator final : public IVibrating
	{
	public:
		

		[[nodiscard("Pure function")]] 
		virtual VibrationState State() const override;
		virtual void State(const VibrationState& state) override;

	private:
		VibrationState state;
	};
}
