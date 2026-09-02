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

export module PonyEngine.RawInput.Mouse.Impl.Windows:MouseProvider;

import std;

import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Memory;
import PonyEngine.RawInput.Ext;
import PonyEngine.RawInput.Mouse.Impl;
import PonyEngine.WinAPIInput.Windows;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse provider.
	class MouseProvider final : private WinAPIInput::IRawInputObserver
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

		/// @brief Updates button states.
		/// @param source Input source.
		/// @param controller Mouse controller.
		/// @param time Input time.
		/// @param cursor Input cursor position.
		static void UpdateButtons(const RAWMOUSE& source, MouseController& controller,
			std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor);
		/// @brief Updates wheel states.
		/// @param source Input source.
		/// @param controller Mouse controller.
		/// @param time Input time.
		/// @param cursor Input cursor position.
		static void UpdateWheels(const RAWMOUSE& source, MouseController& controller,
			std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor);
		/// @brief Updates pointer states.
		/// @param source Input source.
		/// @param controller Mouse controller.
		/// @param time Input time.
		/// @param cursor Input cursor position.
		static void UpdatePointer(const RAWMOUSE& source, MouseController& controller,
			std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor);

		[[nodiscard("Pure function")]]
		static float ToWheelInputValue(USHORT value) noexcept;

		Application::IApplication* application; ///< Application.
		IDeviceHub* hub; ///< Device hub.
		Log::ILogService* logService; ///< Log service.
		WinAPIInput::IInputDispatcher* inputDispatcher; ///< WinAPI input dispatcher.
		Application::IMessagePump* messagePump; ///< WinAPI message pump.

		DeviceType deviceType; ///< Mouse device type.
		DeviceStyle deviceStyle; ///< Mouse device style.
		MouseAxisMap axisMap; ///< Axis map.

		std::vector<HANDLE> nativeHandles; ///< Native handles.
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
		inputDispatcher{&this->application->GetInterface<WinAPIInput::IInputDispatcher>()},
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
		const std::chrono::time_point<std::chrono::steady_clock> time = messagePump->LastMessageTimePoint();
		const POINT point = messagePump->LastMessageCursorPoint();
		const auto cursor = Math::Vector2<std::int32_t>(static_cast<std::int32_t>(point.x), static_cast<std::int32_t>(point.y));
		UpdatePointer(input, controller, time, cursor);
		UpdateWheels(input, controller, time, cursor);
		UpdateButtons(input, controller, time, cursor);
	}

	void MouseProvider::OnDeviceConnectionChanged(const HANDLE device, const bool isConnected)
	{
		if (isConnected)
		{
			const std::size_t nameLength = WinAPIInput::GetDeviceNameSize(device);
			const std::shared_ptr<Application::IBuffer> buffer = application->CreateBuffer(nameLength);
			auto arena = Memory::Arena(buffer->Span());
			const std::span<char> name = arena.AllocateArray<char>(nameLength);
			const std::size_t nameSize = WinAPIInput::GetDeviceName(device, name);

			const std::size_t initialSize = nativeHandles.size();
			try
			{
				nativeHandles.push_back(device);
				mouseControllers.push_back(std::make_unique<MouseController>(axisMap, true));
				IDeviceController& controller = mouseControllers.back()->Controller();
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
				mouseControllers.resize(initialSize);
				nativeHandles.resize(initialSize);
				throw;
			}
		}
		else
		{
			const std::size_t mouseIndex = std::ranges::find(nativeHandles, device) - nativeHandles.cbegin();
			if (mouseIndex >= nativeHandles.size())
			{
				return;
			}

			hub->UnregisterDevice(deviceHandles[mouseIndex], mouseControllers[mouseIndex]->Controller());

			deviceHandles.erase(deviceHandles.cbegin() + mouseIndex);
			mouseControllers.erase(mouseControllers.cbegin() + mouseIndex);
			nativeHandles.erase(nativeHandles.cbegin() + mouseIndex);
		}
	}

	void MouseProvider::UpdateButtons(const RAWMOUSE& source, MouseController& controller,
		const std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor)
	{
		struct ButtonFlagMap final
		{
			USHORT downFlag;
			USHORT upFlag;
			MouseButton button;
		};

		constexpr auto buttonMap = std::array<ButtonFlagMap, 5>
		{
			ButtonFlagMap{.downFlag = RI_MOUSE_LEFT_BUTTON_DOWN, .upFlag = RI_MOUSE_LEFT_BUTTON_UP, .button = MouseButton::Left},
			ButtonFlagMap{.downFlag = RI_MOUSE_RIGHT_BUTTON_DOWN, .upFlag = RI_MOUSE_RIGHT_BUTTON_UP, .button = MouseButton::Right},
			ButtonFlagMap{.downFlag = RI_MOUSE_MIDDLE_BUTTON_DOWN, .upFlag = RI_MOUSE_MIDDLE_BUTTON_UP, .button = MouseButton::Middle},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_4_DOWN, .upFlag = RI_MOUSE_BUTTON_4_UP, .button = MouseButton::X1},
			ButtonFlagMap{.downFlag = RI_MOUSE_BUTTON_5_DOWN, .upFlag = RI_MOUSE_BUTTON_5_UP, .button = MouseButton::X2}
		};

		for (const ButtonFlagMap& mapping : buttonMap)
		{
			if (source.usButtonFlags & mapping.downFlag)
			{
				controller.SetButton(mapping.button, true, time, cursor);
			}
			if (source.usButtonFlags & mapping.upFlag)
			{
				controller.SetButton(mapping.button, false, time, cursor);
			}
		}
	}

	void MouseProvider::UpdateWheels(const RAWMOUSE& source, MouseController& controller,
		const std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor)
	{
		if (source.usButtonFlags & RI_MOUSE_WHEEL)
		{
			controller.AddWheel(MouseWheel::Vertical, ToWheelInputValue(source.usButtonData), time, cursor);
		}
		if (source.usButtonFlags & RI_MOUSE_HWHEEL)
		{
			controller.AddWheel(MouseWheel::Horizontal, ToWheelInputValue(source.usButtonData), time, cursor);
		}
	}

	void MouseProvider::UpdatePointer(const RAWMOUSE& source, MouseController& controller,
		const std::chrono::time_point<std::chrono::steady_clock> time, const Math::Vector2<std::int32_t>& cursor)
	{
		if (source.usFlags != MOUSE_MOVE_RELATIVE) [[unlikely]]
		{
			return;
		}
		if (!source.lLastX && !source.lLastY)
		{
			return;
		}

		const auto delta = Math::Vector2<float>(static_cast<float>(source.lLastX), static_cast<float>(source.lLastY));
		controller.AddPointer(delta, time, cursor);
	}

	float MouseProvider::ToWheelInputValue(const USHORT value) noexcept
	{
		return static_cast<float>(std::bit_cast<SHORT>(value)) / WHEEL_DELTA;
	}
}
