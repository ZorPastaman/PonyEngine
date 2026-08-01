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

#include <hidusage.h>

export module PonyEngine.RawInput.Keyboard.Impl.Windows:KeyboardProvider;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.Platform.Windows;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Keyboard.Impl;
import PonyEngine.WinAPIInput.Windows;

import :KeyboardAxisMap;

export namespace PonyEngine::RawInput::Keyboard
{
	/// @brief Windows keyboard provider.
	class KeyboardProvider final : private WinAPIInput::IRawInputObserver
	{
	public:
		/// @brief Creates a keyboard provider.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit KeyboardProvider(Application::IApplication& application);
		KeyboardProvider(const KeyboardProvider&) = delete;
		KeyboardProvider(KeyboardProvider&&) = delete;

		~KeyboardProvider() noexcept;

		KeyboardProvider& operator =(const KeyboardProvider&) = delete;
		KeyboardProvider& operator =(KeyboardProvider&&) = delete;

	private:
		virtual void OnInput(const RAWINPUT& rawInput) override;
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) override;

		Application::IApplication* application; ///< Application.
		IDeviceHub* hub; ///< Device hub.
		Log::ILogService* logService; ///< Log service.
		WinAPIInput::IInputDispatcher* inputDispatcher; ///< WinAPI input dispatcher.
		Application::IMessagePump* messagePump; ///< WinAPI message pump.

		DeviceType deviceType; ///< Keyboard device type.
		DeviceStyle deviceStyle; ///< Keyboard device style.
		KeyboardAxisMap axisMap; ///< Axis map.

		std::vector<HANDLE> nativeHandles; ///< Native handles.
		std::vector<std::unique_ptr<KeyboardController>> keyboardControllers; ///< Keyboard controller.
		std::vector<DeviceHandle> deviceHandles; ///< Device handles.
	};
}

namespace PonyEngine::RawInput::Keyboard
{
	KeyboardProvider::KeyboardProvider(Application::IApplication& application) :
		application{&application},
		hub{&this->application->GetInterface<IDeviceHub>()},
		logService{this->application->FindInterface<Log::ILogService>()},
		inputDispatcher{&this->application->GetInterface<WinAPIInput::IInputDispatcher>()},
		messagePump{&this->application->GetInterface<Application::IMessagePump>()},
		deviceType(hub->MakeDeviceType(KeyboardDevice::GenericType)),
		deviceStyle(hub->MakeDeviceStyle(Style::None)),
		axisMap(*hub)
	{
		inputDispatcher->AddObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
	}

	KeyboardProvider::~KeyboardProvider() noexcept
	{
		try
		{
			inputDispatcher->RemoveObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering WinAPI raw input keyboard observer.");
		}

		for (std::size_t i = keyboardControllers.size(); i-- > 0uz; )
		{
			try
			{
				hub->UnregisterDevice(deviceHandles[i], keyboardControllers[i]->Controller());
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering keyboard device.");
			}
		}
	}

	void KeyboardProvider::OnInput(const RAWINPUT& rawInput)
	{
		const HANDLE handle = rawInput.header.hDevice;
		const std::size_t keyboardIndex = std::ranges::find(nativeHandles, handle) - nativeHandles.cbegin();

		if (keyboardIndex >= nativeHandles.size()) [[unlikely]]
		{
			return;
		}

		const Axis axis = axisMap.EngineAxis(*hub, rawInput.data.keyboard);
		const bool pressed = !(rawInput.data.keyboard.Flags & RI_KEY_BREAK);
		const std::chrono::time_point<std::chrono::steady_clock> time = messagePump->LastMessageTimePoint();
		const POINT nativeCursor = messagePump->LastMessageCursorPoint();
		const auto cursor = Math::Vector2<std::int32_t>(static_cast<std::int32_t>(nativeCursor.x), static_cast<std::int32_t>(nativeCursor.y));
		keyboardControllers[keyboardIndex]->SetInput(axis, pressed, time, cursor);
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		if (isConnected)
		{
			const std::size_t nameLength = Platform::GetDeviceNameSize(device);
			const auto buffer = Application::ScopedTempBuffer(*application, nameLength);
			auto arena = Memory::Arena(*buffer);
			const std::span<char> name = arena.AllocateArray<char>(nameLength);
			const std::size_t nameSize = Platform::GetDeviceName(device, name);

			const std::size_t initialSize = nativeHandles.size();
			try
			{
				nativeHandles.push_back(device);
				keyboardControllers.push_back(std::make_unique<KeyboardController>(true));
				IDeviceController& controller = keyboardControllers.back()->Controller();
				const DeviceHandle deviceHandle = hub->RegisterDevice(controller, true, DeviceParams
				{
					.name = std::string_view(name.data(), nameSize),
					.type = deviceType,
					.style = deviceStyle
				});
				try
				{
					deviceHandles.push_back(deviceHandle);
				}
				catch (...)
				{
					hub->UnregisterDevice(deviceHandle, controller);
					throw;
				}
			}
			catch (...)
			{
				keyboardControllers.resize(initialSize);
				nativeHandles.resize(initialSize);
				throw;
			}
		}
		else
		{
			const std::size_t keyboardIndex = std::ranges::find(nativeHandles, device) - nativeHandles.cbegin();
			if (keyboardIndex >= nativeHandles.size())
			{
				return;
			}

			hub->UnregisterDevice(deviceHandles[keyboardIndex], keyboardControllers[keyboardIndex]->Controller());

			deviceHandles.erase(deviceHandles.cbegin() + keyboardIndex);
			keyboardControllers.erase(keyboardControllers.cbegin() + keyboardIndex);
			nativeHandles.erase(nativeHandles.cbegin() + keyboardIndex);
		}
	}
}
