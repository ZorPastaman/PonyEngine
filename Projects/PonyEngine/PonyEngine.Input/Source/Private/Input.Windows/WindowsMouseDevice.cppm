/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

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

		virtual void Tick() noexcept override;

		WindowsMouseDevice& operator =(const WindowsMouseDevice&) = delete;
		WindowsMouseDevice& operator =(WindowsMouseDevice&&) = delete;

	private:
		virtual void Observe(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
		virtual void Observe(const RAWINPUT& input) override;

		/// @brief Observes X button.
		/// @param wParam WParam.
		/// @param isDown Is the key down?
		void ObserveXButton(WPARAM wParam, bool isDown);

		float sensitivity; ///< Mouse sensitivity.
	};
}

namespace PonyEngine::Input
{
	WindowsMouseDevice::WindowsMouseDevice(IInputSystemContext& inputSystem, const InputDeviceParams& deviceParams, const WindowsMouseDeviceParams& mouseParams) noexcept :
		InputDevice(inputSystem, deviceParams),
		sensitivity{mouseParams.sensitivity}
	{
	}

	void WindowsMouseDevice::Begin()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::IWindowsWindowSystem>())
		{
			windowSystem->MessagePump().AddMessageObserver(*this, std::array<UINT, 10> { WM_MOUSEMOVE, WM_LBUTTONDOWN, WM_LBUTTONUP, WM_RBUTTONDOWN, WM_RBUTTONUP, WM_MBUTTONDOWN, WM_MBUTTONUP, WM_XBUTTONDOWN, WM_XBUTTONUP, WM_MOUSEWHEEL });
			windowSystem->RawInputManager().AddRawInputObserver(*this, std::array<DWORD, 1> { RIM_TYPEMOUSE });
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
			windowSystem->RawInputManager().RemoveRawInputObserver(*this);
			windowSystem->MessagePump().RemoveMessageObserver(*this);
		}
	}

	void WindowsMouseDevice::Tick() noexcept
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
		default: [[unlikely]]
			assert(false && "The incorrect message type has been received.");
			break;
		}
	}

	void WindowsMouseDevice::Observe(const RAWINPUT& input)
	{
		assert(input.data.mouse.usFlags == MOUSE_MOVE_RELATIVE && "The incorrect raw input type has been received.");

		const LONG deltaX = input.data.mouse.lLastX;
		const LONG deltaY = input.data.mouse.lLastY;

		if (deltaX != 0L)
		{
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseXDelta, .value = static_cast<float>(deltaX) * sensitivity});
		}
		if (deltaY != 0L)
		{
			InputSystem().AddInputEvent(InputEvent{.inputCode = InputCode::MouseYDelta, .value = static_cast<float>(deltaY) * sensitivity});
		}
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
