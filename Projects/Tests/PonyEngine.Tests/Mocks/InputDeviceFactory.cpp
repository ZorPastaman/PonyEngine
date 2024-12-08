/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "InputDeviceFactory.h"

#include <memory>
#include <utility>

namespace Mocks
{
	PonyEngine::Input::InputDeviceData InputDeviceFactory::CreateDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::InputDeviceParams& deviceParams)
	{
		++version;
		auto device = std::make_unique<InputDevice>(inputSystem, deviceParams);
		inputDevice = device.get();

		return PonyEngine::Input::InputDeviceData{.inputDevice = std::move(device)};
	}

	const type_info& InputDeviceFactory::DeviceType() const noexcept
	{
		return typeid(InputDevice);
	}
}
