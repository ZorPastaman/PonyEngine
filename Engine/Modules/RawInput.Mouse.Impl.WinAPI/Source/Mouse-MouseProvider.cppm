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

export module PonyEngine.RawInput.Mouse.Impl.WinAPI:MouseProvider;

import std;

import PonyEngine.Application.WinAPI;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Mouse.Impl;
import PonyEngine.Utility;
import PonyEngine.WinInput;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse provider.
	class MouseProvider final : private WinInput::IRawInputObserver
	{
	public:
		/// @brief Creates a mouse provider.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit MouseProvider(Application::IApplication& application);
		MouseProvider(const MouseProvider&) = delete;
		MouseProvider(MouseProvider&&) = delete;

		~MouseProvider() noexcept;

		MouseProvider& operator =(const MouseProvider&) = delete;
		MouseProvider& operator =(MouseProvider&&) = delete;

	private:
		virtual void OnInput(const RAWINPUT& rawInput) override;
		virtual void OnDeviceConnectionChanged(HANDLE device, bool isConnected) override;

		/// @brief Gets button input.
		/// @param source Input source.
		/// @param buttons Buttons.
		/// @return Button event count.
		[[nodiscard("Must be used")]]
		static std::size_t GetButtons(const RAWMOUSE& source, std::span<std::pair<MouseButton, bool>, MouseButtonCount> buttons) noexcept;
		/// @brief Gets wheel input.
		/// @param source Input source.
		/// @param wheels Wheels.
		/// @return Wheel event count.
		[[nodiscard("Must be used")]]
		static std::size_t GetWheels(const RAWMOUSE& source, std::span<std::pair<MouseWheel, float>, MouseWheelCount> wheels) noexcept;
		/// @brief Gets pointer input.
		/// @param source Input source.
		/// @param pointers Pointers.
		/// @return Pointer event count.
		[[nodiscard("Must be used")]]
		static std::size_t GetPointers(const RAWMOUSE& source, std::span<std::pair<MousePointer, float>, MousePointerCount> pointers) noexcept;

		/// @brief Transform the raw wheel value to an engine axis value.
		/// @param value Wheel value.
		/// @return Axis value.
		[[nodiscard("Pure function")]]
		static float ToWheelInputValue(USHORT value) noexcept;

		/// @brief Connects the mouse device.
		/// @param device Device handle.
		void ConnectDevice(HANDLE device);
		/// @brief Disconnects the mouse device.
		/// @param device Device handle.
		void DisconnectDevice(HANDLE device);

		Application::IApplication* application; ///< Application.
		IDeviceHub* hub; ///< Device hub.
		Log::ILogService* logService; ///< Log service.
		WinInput::IInputDispatcher* inputDispatcher; ///< WinAPI input dispatcher.
		Application::IMessagePump* messagePump; ///< WinAPI message pump.

		DeviceType deviceType; ///< Mouse device type.
		DeviceStyle deviceStyle; ///< Mouse device style.
		MouseAxisMap axisMap; ///< Axis map.

		std::vector<HANDLE> nativeHandles; ///< Native handles.
		std::vector<std::string> mouseNames; ///< Mouse names.
		std::vector<std::unique_ptr<MouseController>> mouseControllers; ///< Mouse controller.
		std::vector<DeviceHandle> deviceHandles; ///< Device handles.
	};
}

namespace PonyEngine::RawInput::Mouse
{
	MouseProvider::MouseProvider(Application::IApplication& application) :
		application{&application},
		hub{&this->application->GetInterface<IDeviceHub>()},
		logService{this->application->FindInterface<Log::ILogService>()},
		inputDispatcher{&this->application->GetInterface<WinInput::IInputDispatcher>()},
		messagePump{&this->application->GetInterface<Application::IMessagePump>()},
		deviceType(hub->MakeDeviceType(MouseDevice::GenericType)),
		deviceStyle(hub->MakeDeviceStyle(Style::None)),
		axisMap(*hub)
	{
		inputDispatcher->AddObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
	}

	MouseProvider::~MouseProvider() noexcept
	{
		try
		{
			inputDispatcher->RemoveObserver(*this, HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering WinAPI raw input mouse observer.");
		}

		for (std::size_t i = mouseControllers.size(); i-- > 0uz; )
		{
			try
			{
				hub->UnregisterDevice(deviceHandles[i], mouseControllers[i]->Controller());
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On unregistering mouse device.");
			}
		}
	}

	void MouseProvider::OnInput(const RAWINPUT& rawInput)
	{
		const HANDLE handle = rawInput.header.hDevice;
		const std::size_t mouseIndex = std::ranges::find(nativeHandles, handle) - nativeHandles.cbegin();

		if (mouseIndex >= nativeHandles.size()) [[unlikely]]
		{
			return;
		}

		const RAWMOUSE& input = rawInput.data.mouse;
		MouseController& controller = *mouseControllers[mouseIndex];

		std::array<std::pair<MousePointer, float>, MousePointerCount> pointers;
		const std::size_t pointerCount = GetPointers(input, pointers);

		std::array<std::pair<MouseWheel, float>, MouseWheelCount> wheels;
		const std::size_t wheelCount = GetWheels(input, wheels);

		std::array<std::pair<MouseButton, bool>, MouseButtonCount> buttons;
		const std::size_t buttonCount = GetButtons(input, buttons);

		const std::chrono::time_point<std::chrono::steady_clock> time = messagePump->LastMessageTimePoint();
		
		controller.SetInput(std::span<const std::pair<MousePointer, float>>(pointers.data(), pointerCount),
			std::span<const std::pair<MouseWheel, float>>(wheels.data(), wheelCount),
			std::span<const std::pair<MouseButton, bool>>(buttons.data(), buttonCount),
			time);
	}

	void MouseProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
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

	std::size_t MouseProvider::GetButtons(const RAWMOUSE& source, const std::span<std::pair<MouseButton, bool>, MouseButtonCount> buttons) noexcept
	{
		struct ButtonFlagMap final
		{
			USHORT downFlag;
			USHORT upFlag;
			MouseButton button;
		};
		constexpr auto buttonMap = std::array<ButtonFlagMap, MouseButtonCount>
		{
			ButtonFlagMap{.downFlag = RI_MOUSE_LEFT_BUTTON_DOWN, .upFlag = RI_MOUSE_LEFT_BUTTON_UP, .button = MouseButton::Left},
			ButtonFlagMap{.downFlag = RI_MOUSE_RIGHT_BUTTON_DOWN, .upFlag = RI_MOUSE_RIGHT_BUTTON_UP, .button = MouseButton::Right},
			ButtonFlagMap{.downFlag = RI_MOUSE_MIDDLE_BUTTON_DOWN, .upFlag = RI_MOUSE_MIDDLE_BUTTON_UP, .button = MouseButton::Middle},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_4_DOWN, .upFlag = RI_MOUSE_BUTTON_4_UP, .button = MouseButton::X1},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_5_DOWN, .upFlag = RI_MOUSE_BUTTON_5_UP, .button = MouseButton::X2}
		};

		std::size_t count = 0uz;
		for (const ButtonFlagMap map : buttonMap)
		{
			const bool isPressed = source.usButtonFlags & map.downFlag;
			const bool isUnpressed = source.usButtonFlags & map.upFlag;
			buttons[count] = std::pair(map.button, isPressed && !isUnpressed);
			count += isPressed || isUnpressed;
		}

		return count;
	}

	std::size_t MouseProvider::GetWheels(const RAWMOUSE& source, const std::span<std::pair<MouseWheel, float>, MouseWheelCount> wheels) noexcept
	{
		constexpr auto wheelMap = std::array<std::pair<USHORT, MouseWheel>, MouseWheelCount>
		{
			std::pair(RI_MOUSE_WHEEL, MouseWheel::Vertical),
			std::pair(RI_MOUSE_HWHEEL, MouseWheel::Horizontal)
		};

		const float input = ToWheelInputValue(source.usButtonData);
		std::size_t count = 0uz;
		for (const auto [nativeWheel, wheel] : wheelMap)
		{
			wheels[count] = std::pair(wheel, input);
			count += static_cast<bool>(source.usButtonFlags & nativeWheel);
		}

		return count;
	}

	std::size_t MouseProvider::GetPointers(const RAWMOUSE& source, const std::span<std::pair<MousePointer, float>, MousePointerCount> pointers) noexcept
	{
		if (source.usFlags != MOUSE_MOVE_RELATIVE) [[unlikely]]
		{
			return 0uz;
		}

		pointers[0] = std::pair(MousePointer::X, static_cast<float>(source.lLastX));
		pointers[1] = std::pair(MousePointer::Y, static_cast<float>(source.lLastY));

		return 2uz;
	}

	float MouseProvider::ToWheelInputValue(const USHORT value) noexcept
	{
		return static_cast<float>(std::bit_cast<SHORT>(value)) / WHEEL_DELTA;
	}

	void MouseProvider::ConnectDevice(const HANDLE device)
	{
		const std::size_t nameLength = WinInput::GetDeviceNameSize(device);
		const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(nameLength);
		auto arena = Memory::Arena(buffer->Span());
		const std::span<char> rawName = arena.AllocateArray<char>(nameLength);
		const std::size_t nameSize = WinInput::GetDeviceName(device, rawName);
		const auto name = std::string_view(rawName.data(), nameSize);

		if (const std::size_t mouseIndex = std::ranges::find(mouseNames, name) - mouseNames.cbegin(); mouseIndex < nativeHandles.size())
		{
			mouseControllers[mouseIndex]->SetConnection(true, messagePump->LastMessageTimePoint());
		}
		else
		{
			auto scopeGuardFlag = Utility::ScopeGuardFlag();

			nativeHandles.push_back(device);
			const auto nativeHandlesScopeGuard = Utility::ScopeGuard([&]() noexcept { nativeHandles.pop_back(); }, scopeGuardFlag);
			mouseNames.push_back(std::string(name));
			const auto mouseNamesScopeGuard = Utility::ScopeGuard([&]() noexcept { mouseNames.pop_back(); }, scopeGuardFlag);
			mouseControllers.push_back(std::make_unique<MouseController>(axisMap, true));
			const auto mouseControllersScopeGuard = Utility::ScopeGuard([&]() noexcept { mouseControllers.pop_back(); }, scopeGuardFlag);
			IDeviceController& controller = mouseControllers.back()->Controller();
			const DeviceHandle deviceHandle = hub->RegisterDevice(controller, true, DeviceParams
			{
				.name = mouseNames.back(),
				.type = deviceType,
				.style = deviceStyle
			});
			const auto deviceHandleScopeGuard = Utility::ScopeGuard([&]() noexcept { hub->UnregisterDevice(deviceHandle, controller); }, scopeGuardFlag);
			deviceHandles.push_back(deviceHandle);

			scopeGuardFlag.Release();
		}
	}

	void MouseProvider::DisconnectDevice(const HANDLE device)
	{
		if (const std::size_t mouseIndex = std::ranges::find(nativeHandles, device) - nativeHandles.cbegin(); mouseIndex < nativeHandles.size())
		{
			mouseControllers[mouseIndex]->SetConnection(false, messagePump->LastMessageTimePoint());
		}
	}
}
