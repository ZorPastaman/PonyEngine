/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows.Detail:WindowsKeyboardDeviceFactory;

import <memory>;

import PonyEngine.Input.Detail;

import :WindowsKeyboardDevice;

export namespace PonyEngine::Input
{
	class WindowsKeyboardDeviceFactory final : public InputDeviceFactory
	{
	public:
		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<InputDevice> CreateDevice(IInputSystemContext& inputSystem) override;
	};
}

namespace PonyEngine::Input
{
	std::unique_ptr<InputDevice> WindowsKeyboardDeviceFactory::CreateDevice(IInputSystemContext& inputSystem)
	{
		return std::make_unique<WindowsKeyboardDevice>(inputSystem);
	}
}
