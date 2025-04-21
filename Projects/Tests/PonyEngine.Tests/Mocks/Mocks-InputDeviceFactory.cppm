/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:InputDeviceFactory;

import <cstddef>;
import <memory>;
import <typeinfo>;
import <utility>;

import :InputDevice;

export namespace Mocks
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

namespace Mocks
{
	PonyEngine::Input::DeviceData InputDeviceFactory::CreateDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::DeviceParams& deviceParams)
	{
		++version;
		auto device = std::make_unique<InputDevice>(inputSystem, deviceParams);
		inputDevice = device.get();

		return PonyEngine::Input::DeviceData{.inputDevice = std::move(device)};
	}

	const type_info& InputDeviceFactory::DeviceType() const noexcept
	{
		return typeid(InputDevice);
	}
}
