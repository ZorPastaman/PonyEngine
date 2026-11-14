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
#include <hidusage.h>

export module PonyEngine.RawInput.Keyboard.Impl.WinAPI:KeyboardProvider;

import std;

import PonyEngine.Application.WinAPI;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Keyboard.Impl;
import PonyEngine.Utility;
import PonyEngine.WinInput;

import :KeyboardAxisMap;

export namespace PonyEngine::RawInput::Keyboard
{
	/// @brief WinAPI keyboard provider.
	class KeyboardProvider final : private WinInput::IRawInputObserver
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

		/// @brief Connects the keyboard device.
		/// @param device Device handle.
		void ConnectDevice(HANDLE device);
		/// @brief Disconnects the keyboard device.
		/// @param device Device handle.
		void DisconnectDevice(HANDLE device);

		Application::IApplication* application; ///< Application.
		IDeviceHub* hub; ///< Device hub.
		Log::ILogService* logService; ///< Log service.
		WinInput::IInputDispatcher* inputDispatcher; ///< WinAPI input dispatcher.
		Application::IMessagePump* messagePump; ///< WinAPI message pump.

		DeviceType deviceType; ///< Keyboard device type.
		DeviceStyle deviceStyle; ///< Keyboard device style.
		KeyboardAxisMap axisMap; ///< Axis map.

		std::vector<HANDLE> nativeHandles; ///< Native handles.
		std::vector<std::string> keyboardNames; ///< Keyboard names.
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
		inputDispatcher{&this->application->GetInterface<WinInput::IInputDispatcher>()},
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
		keyboardControllers[keyboardIndex]->SetInput(axis, pressed, time);
	}

	void KeyboardProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		if (isConnected)
		{
			ConnectDevice(device);
		}
		else
		{
			DisconnectDevice(device);
		}
	}

	void KeyboardProvider::ConnectDevice(const HANDLE device)
	{
		const std::size_t nameLength = WinInput::GetDeviceNameSize(device);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(nameLength);
		auto arena = Memory::Arena(buffer->Span());
		const std::span<char> rawName = arena.AllocateArray<char>(nameLength);
		const std::size_t nameSize = WinInput::GetDeviceName(device, rawName);
		const auto name = std::string_view(rawName.data(), nameSize);

		if (const std::size_t keyboardIndex = std::ranges::find(keyboardNames, name) - keyboardNames.cbegin(); keyboardIndex < nativeHandles.size())
		{
			keyboardControllers[keyboardIndex]->SetConnection(true, messagePump->LastMessageTimePoint());
		}
		else
		{
			auto scopeGuardFlag = Utility::ScopeGuardFlag();

			nativeHandles.push_back(device);
			const auto nativeHandlesScopeGuard = Utility::ScopeGuard([&]() noexcept { nativeHandles.pop_back(); }, scopeGuardFlag);
			keyboardNames.push_back(std::string(name));
			const auto keyboardNamesScopeGuard = Utility::ScopeGuard([&]() noexcept { keyboardNames.pop_back(); }, scopeGuardFlag);
			keyboardControllers.push_back(std::make_unique<KeyboardController>(true));
			const auto keyboardControllersScopeGuard = Utility::ScopeGuard([&]() noexcept { keyboardControllers.pop_back(); }, scopeGuardFlag);
			IDeviceController& controller = keyboardControllers.back()->Controller();
			const std::string friendlyName = std::format("Keyboard {}", keyboardIndex);
			const DeviceHandle deviceHandle = hub->RegisterDevice(controller, true, DeviceParams
			{
				.name = keyboardNames.back(),
				.friendlyName = friendlyName,
				.interfaceName = Interface::RawInput,
				.type = deviceType,
				.style = deviceStyle
			});
			const auto deviceHandleScopeGuard = Utility::ScopeGuard([&]() noexcept { hub->UnregisterDevice(deviceHandle, controller); }, scopeGuardFlag);
			deviceHandles.push_back(deviceHandle);

			scopeGuardFlag.Release();
		}
	}

	void KeyboardProvider::DisconnectDevice(const HANDLE device)
	{
		if (const std::size_t keyboardIndex = std::ranges::find(nativeHandles, device) - nativeHandles.cbegin(); keyboardIndex < nativeHandles.size())
		{
			keyboardControllers[keyboardIndex]->SetConnection(false, messagePump->LastMessageTimePoint());
		}
	}
}
