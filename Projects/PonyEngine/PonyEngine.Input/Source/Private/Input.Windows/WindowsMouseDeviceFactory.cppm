/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows.Detail:WindowsMouseDeviceFactory;

import <memory>;
import <typeinfo>;

import PonyEngine.Core;
import PonyEngine.Input.Windows;

import :WindowsMouseDevice;

export namespace PonyEngine::Input
{
	/// @brief Windows mouse device factory.
	class WindowsMouseDeviceFactory final : public InputDeviceFactory
	{
	public:
		/// @brief Creates a @p WindowsMouseDeviceFactory.
		/// @param application Application context.
		/// @param factoryParams Factory parameters.
		/// @param deviceParams Device parameters.
		[[nodiscard("Pure constructor")]]
		WindowsMouseDeviceFactory(Core::IApplicationContext& application, const WindowsMouseDeviceFactoryParams& factoryParams, const WindowsMouseDeviceParams& deviceParams) noexcept;
		WindowsMouseDeviceFactory(const WindowsMouseDeviceFactory&) = delete;
		WindowsMouseDeviceFactory(WindowsMouseDeviceFactory&&) = delete;

		virtual ~WindowsMouseDeviceFactory() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual InputDeviceData CreateDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept override;

		WindowsMouseDeviceFactory& operator =(const WindowsMouseDeviceFactory&) = delete;
		WindowsMouseDeviceFactory& operator =(WindowsMouseDeviceFactory&&) = delete;

	private:
		WindowsMouseDeviceParams mouseParams; ///< Mouse parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Input
{
	WindowsMouseDeviceFactory::WindowsMouseDeviceFactory(Core::IApplicationContext& application, const WindowsMouseDeviceFactoryParams&, const WindowsMouseDeviceParams& deviceParams) noexcept :
		mouseParams(deviceParams),
		application{ &application }
	{
	}

	InputDeviceData WindowsMouseDeviceFactory::CreateDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams)
	{
		return InputDeviceData{ .inputDevice = std::make_unique<WindowsMouseDevice>(inputSystem, deviceParams, mouseParams) };
	}

	const std::type_info& WindowsMouseDeviceFactory::DeviceType() const noexcept
	{
		return typeid(WindowsMouseDevice);
	}
}
