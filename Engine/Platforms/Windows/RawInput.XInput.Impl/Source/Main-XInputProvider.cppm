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
#include "PonyEngine/Platform/Windows/Framework.h"

#include <xinput.h>

export module PonyEngine.RawInput.XInput.Impl.Windows:XInputProvider;

import std;

import PonyEngine.Application;
import PonyEngine.Log;
import PonyEngine.RawInput.Ext;

import :GamepadAxisMap;
import :GamepadController;

export namespace PonyEngine::RawInput::XInput::Windows
{
	/// @brief XInput gamepad provider.
	class XInputProvider final
	{
	public:
		/// @brief Creates an XInput gamepad provider.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit XInputProvider(const Application::IApplication& application) noexcept;
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

namespace PonyEngine::RawInput::XInput::Windows
{
	XInputProvider::XInputProvider(const Application::IApplication& application) noexcept :
		deviceHub{&application.GetInterface<IDeviceHub>()},
		logService{application.FindInterface<Log::ILogService>()},
		gamepadAxisMap(*deviceHub)
	{
		for (DWORD i = 0uz; i < XUSER_MAX_COUNT; ++i)
		{
			gamepadControllers[i] = GamepadController(gamepadAxisMap, logService, i);
		}

		const DeviceType type = deviceHub->MakeDeviceType(GamepadDevice::XboxType);
		for (DWORD i = 0u; i < XUSER_MAX_COUNT; ++i)
		{
			try
			{
				deviceHandles[i] = deviceHub->RegisterDevice(gamepadControllers[i], std::format("XInput_{}", i), type, gamepadControllers[i].IsConnected());
			}
			catch (...)
			{
				while (i-- > 0u)
				{
					deviceHub->UnregisterDevice(gamepadControllers[i], deviceHandles[i]);
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
				deviceHub->UnregisterDevice(gamepadControllers[i], deviceHandles[i]);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering XInput device. Index: '{}'.", i);
			}
		}
	}
}
