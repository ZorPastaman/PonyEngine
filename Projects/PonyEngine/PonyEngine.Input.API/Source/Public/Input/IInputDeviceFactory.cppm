/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Interface.h"

export module PonyEngine.Input:IInputDeviceFactory;

import <memory>;

import :IInputSystemContext;
import :InputDevice;

export namespace PonyEngine::Input
{
	class IInputDeviceFactory
	{
		INTERFACE_BODY(IInputDeviceFactory)

		[[nodiscard("Pure function")]]
		virtual std::unique_ptr<InputDevice> CreateDevice(IInputSystemContext& inputSystem) = 0;
	};
}
