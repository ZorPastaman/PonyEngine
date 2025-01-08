/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include <cstddef>

#include "InputDevice.h"

import PonyEngine.Input;

namespace Mocks
{
	class InputDeviceFactory final : public PonyEngine::Input::IDeviceFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual PonyEngine::Input::DeviceData CreateDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::DeviceParams& deviceParams) override;

		[[nodiscard("Pure function")]]
		virtual const type_info& DeviceType() const noexcept override;

		std::size_t version = 0;
		InputDevice* inputDevice = nullptr;
	};
}
