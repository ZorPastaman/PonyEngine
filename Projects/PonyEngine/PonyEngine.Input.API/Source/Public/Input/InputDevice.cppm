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

export module PonyEngine.Input:InputDevice;

import :IInputSystemContext;
import :InputDeviceParams;

export namespace PonyEngine::Input
{
	/// @brief Input device.
	class InputDevice
	{
		BASE_BODY_WITHOUT_DEFAULT_CONSTRUCTOR(InputDevice)

	public:
		/// @brief Begins an input capture. It's called before a first tick.
		virtual void Begin() = 0;
		/// @brief Ends an input capture. It's called after a last tick.
		virtual void End() = 0;

		/// @brief Ticks the device. It's called before a queue analysis.
		virtual void Tick() = 0;

	protected:
		/// @brief Creates an @p InputDevice.
		/// @param inputSystem Input system context.
		/// @param deviceParams Input device parameters.
		[[nodiscard("Pure constructor")]]
		InputDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams) noexcept;

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
	InputDevice::InputDevice(IInputSystemContext& inputSystem, const InputDeviceParams&) noexcept :
		inputSystem{&inputSystem}
	{
	}

	IInputSystemContext& InputDevice::InputSystem() const noexcept
	{
		return *inputSystem;
	}
}
