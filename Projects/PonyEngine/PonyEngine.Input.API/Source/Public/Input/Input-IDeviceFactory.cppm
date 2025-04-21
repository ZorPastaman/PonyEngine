/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Input:IDeviceFactory;

import <memory>;
import <typeinfo>;

import :DeviceData;
import :DeviceParams;
import :IInputSystemContext;

export namespace PonyEngine::Input
{
	/// @brief Input device factory.
	class IDeviceFactory
	{
		INTERFACE_BODY(IDeviceFactory)

		/// @brief Creates a device.
		/// @param inputSystem Input system context.
		/// @param deviceParams Input device parameters.
		/// @return Input device.
		[[nodiscard("Redundant call")]]
		virtual DeviceData CreateDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams) = 0;

		/// @brief Gets the device type that the factory creates.
		/// @return Device type.
		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept = 0;
	};
}
