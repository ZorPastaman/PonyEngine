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

export module PonyEngine.Input:Device;

import :DeviceParams;
import :IDevice;
import :IInputSystemContext;

export namespace PonyEngine::Input
{
	/// @brief Input device.
	class Device : public IDevice
	{
		BASE_BODY(Device)

	public:
		/// @brief Begins an input capture. It's called before a first tick.
		virtual void Begin() = 0;
		/// @brief Ends an input capture. It's called after a last tick.
		virtual void End() = 0;

		/// @brief Ticks the device. It's called before a queue analysis.
		virtual void Tick() = 0;

	protected:
		/// @brief Creates an @p Device.
		/// @param inputSystem Input system context.
		/// @param deviceParams Input device parameters.
		[[nodiscard("Pure constructor")]]
		Device(IInputSystemContext& inputSystem, const DeviceParams& deviceParams) noexcept;

		/// @brief Gets the input system context.
		/// @return Input system context.
		[[nodiscard("Pure function")]]
		IInputSystemContext& InputSystem() const noexcept;

	private:
		IInputSystemContext* inputSystem; ///< Input system context.
	};
}

namespace PonyEngine::Input
{
	Device::Device(IInputSystemContext& inputSystem, const DeviceParams&) noexcept :
		inputSystem{&inputSystem}
	{
	}

	IInputSystemContext& Device::InputSystem() const noexcept
	{
		return *inputSystem;
	}
}
