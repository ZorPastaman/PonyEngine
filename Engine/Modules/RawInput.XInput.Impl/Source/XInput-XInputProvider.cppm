/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <xinput.h>

export module PonyEngine.RawInput.XInput.Impl:XInputProvider;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :GamepadAxisMap;
import :GamepadController;

export namespace PonyEngine::RawInput::XInput
{
	/// @brief XInput gamepad provider.
	class XInputProvider final
	{
	public:
		/// @brief Creates an XInput gamepad provider.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit XInputProvider(const Application::IApplication& application);
		XInputProvider(const XInputProvider&) = delete;
		XInputProvider(XInputProvider&&) = delete;

		~XInputProvider() noexcept;

		XInputProvider& operator =(const XInputProvider&) = delete;
		XInputProvider& operator =(XInputProvider&&) = delete;

	private:
		IDeviceHub* deviceHub; ///< Device hub.
		Log::ILogService* logService; ///< Log service.

		GamepadAxisMap gamepadAxisMap; ///< Gamepad axis map.
		std::array<GamepadController, XUSER_MAX_COUNT> gamepadControllers; ///< Gamepad controllers.
		std::array<DeviceHandle, XUSER_MAX_COUNT> deviceHandles; ///< Device handles. Synced with the @p gamepadControllers by index.
	};
}

namespace PonyEngine::RawInput::XInput
{
	XInputProvider::XInputProvider(const Application::IApplication& application) :
		deviceHub{&application.GetInterface<IDeviceHub>()},
		logService{application.FindInterface<Log::ILogService>()},
		gamepadAxisMap(*deviceHub)
	{
		for (DWORD i = 0uz; i < XUSER_MAX_COUNT; ++i)
		{
			gamepadControllers[i] = GamepadController(gamepadAxisMap, logService, i);
		}

		const DeviceType type = deviceHub->MakeDeviceType(GamepadDevice::GenericType);
		const DeviceStyle style = deviceHub->MakeDeviceStyle(Style::Xbox);
		for (DWORD i = 0u; i < XUSER_MAX_COUNT; ++i)
		{
			try
			{
				GamepadController& controller = gamepadControllers[i];
				const std::string name = std::format("XInput_{}", i);
				const auto vibratingFeature = FeatureEntry::Make<IVibrating>(controller);
				deviceHandles[i] = deviceHub->RegisterDevice(controller.Controller(), controller.IsConnected(), DeviceParams
				{
					.name = name,
					.type = type,
					.style = style,
					.features = std::span(&vibratingFeature, 1uz)
				});
			}
			catch (...)
			{
				while (i-- > 0u)
				{
					deviceHub->UnregisterDevice(deviceHandles[i], gamepadControllers[i].Controller());
				}

				throw;
			}
		}
	}

	XInputProvider::~XInputProvider() noexcept
	{
		for (DWORD i = XUSER_MAX_COUNT; i-- > 0u; )
		{
			try
			{
				deviceHub->UnregisterDevice(deviceHandles[i], gamepadControllers[i].Controller());
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering XInput device. Index: '{}'.", i);
			}
		}
	}
}
