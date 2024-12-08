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
import <typeinfo>;

import PonyEngine.Core;
import PonyEngine.Input.Windows;

import :WindowsKeyboardDevice;

export namespace PonyEngine::Input
{
	/// @brief Windows keyboard device factory.
	class WindowsKeyboardDeviceFactory final : public InputDeviceFactory
	{
	public:
		/// @brief Creates a @p WindowsKeyboardDeviceFactory.
		/// @param application Application context.
		/// @param factoryParams Factory parameters.
		/// @param deviceParams Device parameters.
		[[nodiscard("Pure constructor")]]
		WindowsKeyboardDeviceFactory(Core::IApplicationContext& application, const WindowsKeyboardDeviceFactoryParams& factoryParams, const WindowsKeyboardDeviceParams& deviceParams) noexcept;
		WindowsKeyboardDeviceFactory(const WindowsKeyboardDeviceFactory&) = delete;
		WindowsKeyboardDeviceFactory(WindowsKeyboardDeviceFactory&&) = delete;

		virtual ~WindowsKeyboardDeviceFactory() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual InputDeviceData CreateDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept override;

		WindowsKeyboardDeviceFactory& operator =(const WindowsKeyboardDeviceFactory&) = delete;
		WindowsKeyboardDeviceFactory& operator =(WindowsKeyboardDeviceFactory&&) = delete;

	private:
		WindowsKeyboardDeviceParams keyboardParams; ///< Keyboard parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Input
{
	WindowsKeyboardDeviceFactory::WindowsKeyboardDeviceFactory(Core::IApplicationContext& application, const WindowsKeyboardDeviceFactoryParams&, const WindowsKeyboardDeviceParams& deviceParams) noexcept :
		keyboardParams(deviceParams),
		application{&application}
	{
	}

	InputDeviceData WindowsKeyboardDeviceFactory::CreateDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams)
	{
		return InputDeviceData{.inputDevice = std::make_unique<WindowsKeyboardDevice>(inputSystem, deviceParams, keyboardParams)};
	}

	const std::type_info& WindowsKeyboardDeviceFactory::DeviceType() const noexcept
	{
		return typeid(WindowsKeyboardDevice);
	}
}
