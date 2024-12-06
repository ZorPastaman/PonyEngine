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
import <typeinfo>;

import :IInputSystemContext;
import :InputDeviceData;
import :InputDeviceParams;

export namespace PonyEngine::Input
{
	/// @brief Input device factory.
	class IInputDeviceFactory
	{
		INTERFACE_BODY(IInputDeviceFactory)

		/// @brief Creates a device.
		/// @param inputSystem Input system context.
		/// @param deviceParams Input device parameters.
		/// @return Input device.
		[[nodiscard("Pure function")]] // TODO: Rename some to Redundant call
		virtual InputDeviceData CreateDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams) = 0;

		/// @brief Gets the device type that the factory creates.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept = 0;
	};
}
