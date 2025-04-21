/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows.Detail:MouseDeviceFactory;

import <memory>;
import <typeinfo>;

import PonyEngine.Core;
import PonyEngine.Input.Windows;

import :MouseDevice;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows mouse device factory.
	class MouseDeviceFactory final : public DeviceFactory
	{
	public:
		/// @brief Creates a @p MouseDeviceFactory.
		/// @param application Application context.
		/// @param factoryParams Factory parameters.
		/// @param deviceParams Device parameters.
		[[nodiscard("Pure constructor")]]
		MouseDeviceFactory(Core::IApplicationContext& application, const MouseDeviceFactoryParams& factoryParams, const MouseDeviceParams& deviceParams) noexcept;
		MouseDeviceFactory(const MouseDeviceFactory&) = delete;
		MouseDeviceFactory(MouseDeviceFactory&&) = delete;

		virtual ~MouseDeviceFactory() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual DeviceData CreateDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept override;

		MouseDeviceFactory& operator =(const MouseDeviceFactory&) = delete;
		MouseDeviceFactory& operator =(MouseDeviceFactory&&) = delete;

	private:
		MouseDeviceParams mouseParams; ///< Mouse parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Input::Windows
{
	MouseDeviceFactory::MouseDeviceFactory(Core::IApplicationContext& application, const MouseDeviceFactoryParams&, const MouseDeviceParams& deviceParams) noexcept :
		mouseParams(deviceParams),
		application{ &application }
	{
	}

	DeviceData MouseDeviceFactory::CreateDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams)
	{
		return DeviceData{.inputDevice = std::make_shared<MouseDevice>(inputSystem, deviceParams, mouseParams)};
	}

	const std::type_info& MouseDeviceFactory::DeviceType() const noexcept
	{
		return typeid(MouseDevice);
	}
}
