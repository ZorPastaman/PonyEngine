/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "InputDevice.h"

namespace Mocks
{
	InputDevice::InputDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::InputDeviceParams& deviceParams) noexcept :
		PonyEngine::Input::InputDevice(inputSystem, deviceParams)
	{
	}

	void InputDevice::Begin()
	{
		++beginCount;
	}

	void InputDevice::End()
	{
		++endCount;
	}

	void InputDevice::Tick()
	{
		++tickCount;
	}

	void InputDevice::AddInput(const PonyEngine::Input::InputEvent& input)
	{
		InputSystem().AddInputEvent(*this, input);
	}
}
