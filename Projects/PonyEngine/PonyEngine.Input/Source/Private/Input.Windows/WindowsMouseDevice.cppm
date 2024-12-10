/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Windows/Framework.h"

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Input.Windows.Detail:WindowsMouseDevice;

import <array>;
import <unordered_map>;

import PonyDebug.Log;

import PonyEngine.Input.Windows;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Input
{
	/// @brief Windows mouse device.
	class WindowsMouseDevice final : public InputDevice, private Window::IWindowsMessageObserver, private Window::IWindowsRawInputObserver
	{
	public:
		/// @brief Creates a @p WindowsMouseDevice.
		/// @param inputSystem Input system context.
		/// @param deviceParams Device parameters.
		/// @param mouseParams Mouse parameters.
		WindowsMouseDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams, const WindowsMouseDeviceParams& mouseParams) noexcept;
		WindowsMouseDevice(const WindowsMouseDevice&) = delete;
		WindowsMouseDevice(WindowsMouseDevice&&) = delete;

		virtual ~WindowsMouseDevice() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() override;

		WindowsMouseDevice& operator =(const WindowsMouseDevice&) = delete;
		WindowsMouseDevice& operator =(WindowsMouseDevice&&) = delete;

	private:
		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		virtual void Observe(const RAWINPUT& input) override;

		/// @brief Observes X button.
		/// @param wParam WParam.
		/// @param isDown Is the key down?
		void ObserveXButton(WPARAM wParam, bool isDown);
	};
}

namespace PonyEngine::Input
{
	WindowsMouseDevice::WindowsMouseDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams, const WindowsMouseDeviceParams&) noexcept :
		InputDevice(inputSystem, deviceParams)
	{
	}

	void WindowsMouseDevice::Begin()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			constexpr auto messageTypes = std::array<UINT, 10> { WM_MOUSEMOVE, WM_LBUTTONDOWN, WM_LBUTTONUP, WM_RBUTTONDOWN, WM_RBUTTONUP, WM_MBUTTONDOWN, WM_MBUTTONUP, WM_XBUTTONDOWN, WM_XBUTTONUP, WM_MOUSEWHEEL };
			windowSystem->AddMessageObserver(*this, messageTypes);
			constexpr auto rawInputTypes = std::array<DWORD, 1> { RIM_TYPEMOUSE };
			windowSystem->AddRawInputObserver(*this, rawInputTypes);
		}
		else
		{
			PONY_LOG(InputSystem().Logger(), PonyDebug::Log::LogType::Warning, "Failed to find Windows window system. Mouse input won't work.");
		}
	}

	void WindowsMouseDevice::End()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			windowSystem->RemoveRawInputObserver(*this);
			windowSystem->RemoveMessageObserver(*this);
		}
	}

	void WindowsMouseDevice::Tick()
	{
	}

	void WindowsMouseDevice::Observe(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_MOUSEMOVE:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseXPosition, .value = static_cast<float>(GET_X_LPARAM(lParam))});
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseYPosition, .value = static_cast<float>(GET_Y_LPARAM(lParam))});
			break;
		case WM_LBUTTONDOWN:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseLeftButton, .value = 1.f});
			break;
		case WM_LBUTTONUP:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseLeftButton, .value = 0.f});
			break;
		case WM_RBUTTONDOWN:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseRightButton, .value = 1.f});
			break;
		case WM_RBUTTONUP:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseRightButton, .value = 0.f});
			break;
		case WM_MBUTTONDOWN:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseMiddleButton, .value = 1.f});
			break;
		case WM_MBUTTONUP:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseMiddleButton, .value = 0.f});
			break;
		case WM_XBUTTONDOWN:
			ObserveXButton(wParam, true);
			break;
		case WM_XBUTTONUP:
			ObserveXButton(wParam, false);
			break;
		case WM_MOUSEWHEEL:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseWheel, .value = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA)});
			break;
		default:
			break;
		}
	}

	void WindowsMouseDevice::Observe(const RAWINPUT& input)
	{
		if (input.data.mouse.usFlags != MOUSE_MOVE_RELATIVE)
		{
			return;
		}

		InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseXDelta, .value = static_cast<float>(input.data.mouse.lLastX)});
		InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseYDelta, .value = static_cast<float>(input.data.mouse.lLastY)});
	}

	void WindowsMouseDevice::ObserveXButton(const WPARAM wParam, const bool isDown)
	{
		switch (GET_XBUTTON_WPARAM(wParam))
		{
		case 1:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseButton4, .value = static_cast<float>(isDown)});
			break;
		case 2:
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseButton5, .value = static_cast<float>(isDown)});
			break;
		default:
			break;
		}
	}
}
