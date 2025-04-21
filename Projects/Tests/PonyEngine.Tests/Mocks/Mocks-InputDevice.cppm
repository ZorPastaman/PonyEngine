/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Mocks:InputDevice;

import <cstddef>;

import PonyEngine.Input;

export namespace Mocks
{
	class InputDevice final : public PonyEngine::Input::Device
	{
	public:
		[[nodiscard("Pure constructor")]]
		InputDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::DeviceParams& deviceParams) noexcept;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		void AddInput(const PonyEngine::Input::InputEvent& input);

		std::size_t beginCount = 0;
		std::size_t endCount = 0;
		std::size_t tickCount = 0;
	};
}

namespace Mocks
{
	InputDevice::InputDevice(PonyEngine::Input::IInputSystemContext& inputSystem, const PonyEngine::Input::DeviceParams& deviceParams) noexcept :
		PonyEngine::Input::Device(inputSystem, deviceParams)
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
		InputSystem().AddInputEvent(input);
	}
}
