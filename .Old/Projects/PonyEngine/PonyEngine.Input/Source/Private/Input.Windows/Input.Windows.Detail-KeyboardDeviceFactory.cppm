/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input.Windows.Detail:KeyboardDeviceFactory;

import <memory>;
import <typeinfo>;

import PonyEngine.Core;
import PonyEngine.Input.Windows;

import :KeyboardDevice;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows keyboard device factory.
	class KeyboardDeviceFactory final : public DeviceFactory
	{
	public:
		/// @brief Creates a @p KeyboardDeviceFactory.
		/// @param application Application context.
		/// @param factoryParams Factory parameters.
		/// @param deviceParams Device parameters.
		[[nodiscard("Pure constructor")]]
		KeyboardDeviceFactory(Core::IApplicationContext& application, const KeyboardDeviceFactoryParams& factoryParams, const KeyboardDeviceParams& deviceParams) noexcept;
		KeyboardDeviceFactory(const KeyboardDeviceFactory&) = delete;
		KeyboardDeviceFactory(KeyboardDeviceFactory&&) = delete;

		virtual ~KeyboardDeviceFactory() noexcept override = default;

		[[nodiscard("Redundant call")]]
		virtual DeviceData CreateDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams) override;

		[[nodiscard("Pure function")]]
		virtual const std::type_info& DeviceType() const noexcept override;

		KeyboardDeviceFactory& operator =(const KeyboardDeviceFactory&) = delete;
		KeyboardDeviceFactory& operator =(KeyboardDeviceFactory&&) = delete;

	private:
		KeyboardDeviceParams keyboardParams; ///< Keyboard parameters.

		Core::IApplicationContext* application; ///< Application context.
	};
}

namespace PonyEngine::Input::Windows
{
	KeyboardDeviceFactory::KeyboardDeviceFactory(Core::IApplicationContext& application, const KeyboardDeviceFactoryParams&, const KeyboardDeviceParams& deviceParams) noexcept :
		keyboardParams(deviceParams),
		application{&application}
	{
	}

	DeviceData KeyboardDeviceFactory::CreateDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams)
	{
		return DeviceData{.inputDevice = std::make_shared<KeyboardDevice>(inputSystem, deviceParams, keyboardParams)};
	}

	const std::type_info& KeyboardDeviceFactory::DeviceType() const noexcept
	{
		return typeid(KeyboardDevice);
	}
}
