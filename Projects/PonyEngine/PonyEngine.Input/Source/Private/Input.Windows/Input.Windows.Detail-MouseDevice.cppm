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

export module PonyEngine.Input.Windows.Detail:MouseDevice;

import <array>;
import <unordered_map>;

import PonyDebug.Log;

import PonyEngine.Input.Windows;
import PonyEngine.Window.Windows;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows mouse device.
	class MouseDevice final : public Device, private Window::Windows::IMessageObserver, private Window::Windows::IRawInputObserver
	{
	public:
		/// @brief Creates a @p MouseDevice.
		/// @param inputSystem Input system context.
		/// @param deviceParams Device parameters.
		/// @param mouseParams Mouse parameters.
		MouseDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams, const MouseDeviceParams& mouseParams) noexcept;
		MouseDevice(const MouseDevice&) = delete;
		MouseDevice(MouseDevice&&) = delete;

		virtual ~MouseDevice() noexcept override = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Tick() noexcept override;

		MouseDevice& operator =(const MouseDevice&) = delete;
		MouseDevice& operator =(MouseDevice&&) = delete;

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

namespace PonyEngine::Input::Windows
{
	MouseDevice::MouseDevice(IInputSystemContext& inputSystem, const DeviceParams& deviceParams, const MouseDeviceParams& mouseParams) noexcept :
		Device(inputSystem, deviceParams),
		sensitivity{mouseParams.sensitivity}
	{
	}

	void MouseDevice::Begin()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::Windows::IWindowSystem>()) [[likely]]
		{
			windowSystem->MessagePump().AddMessageObserver(*this, std::array<UINT, 10> { WM_MOUSEMOVE, WM_LBUTTONDOWN, WM_LBUTTONUP, WM_RBUTTONDOWN, WM_RBUTTONUP, WM_MBUTTONDOWN, WM_MBUTTONUP, WM_XBUTTONDOWN, WM_XBUTTONUP, WM_MOUSEWHEEL });
			windowSystem->RawInputManager().AddRawInputObserver(*this, std::array<DWORD, 1> { RIM_TYPEMOUSE });
		}
		else [[unlikely]]
		{
			PONY_LOG(InputSystem().Logger(), PonyDebug::Log::LogType::Warning, "Failed to find Windows window system. Mouse input won't work.");
		}
	}

	void MouseDevice::End()
	{
		if (const auto windowSystem = InputSystem().SystemManager().FindSystem<Window::Windows::IWindowSystem>()) [[likely]]
		{
			windowSystem->RawInputManager().RemoveRawInputObserver(*this);
			windowSystem->MessagePump().RemoveMessageObserver(*this);
		}
	}

	void MouseDevice::Tick() noexcept
	{
	}

	void MouseDevice::Observe(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_MOUSEMOVE:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseXPosition, .inputValue = static_cast<float>(GET_X_LPARAM(lParam)), .inputType = InputType::State});
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseYPosition, .inputValue = static_cast<float>(GET_Y_LPARAM(lParam)), .inputType = InputType::State});
			break;
		case WM_LBUTTONDOWN:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseLeftButton, .inputValue = 1.f, .inputType = InputType::State});
			break;
		case WM_LBUTTONUP:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseLeftButton, .inputValue = 0.f, .inputType = InputType::State});
			break;
		case WM_RBUTTONDOWN:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseRightButton, .inputValue = 1.f, .inputType = InputType::State});
			break;
		case WM_RBUTTONUP:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseRightButton, .inputValue = 0.f, .inputType = InputType::State});
			break;
		case WM_MBUTTONDOWN:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseMiddleButton, .inputValue = 1.f, .inputType = InputType::State});
			break;
		case WM_MBUTTONUP:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseMiddleButton, .inputValue = 0.f, .inputType = InputType::State});
			break;
		case WM_XBUTTONDOWN:
			ObserveXButton(wParam, true);
			break;
		case WM_XBUTTONUP:
			ObserveXButton(wParam, false);
			break;
		case WM_MOUSEWHEEL:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseWheel, .inputValue = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA), .inputType = InputType::Delta});
			break;
		default: [[unlikely]]
			assert(false && "The incorrect message type has been received.");
			break;
		}
	}

	void MouseDevice::Observe(const RAWINPUT& input)
	{
		assert(input.data.mouse.usFlags == MOUSE_MOVE_RELATIVE && "The incorrect raw input type has been received.");

		const LONG deltaX = input.data.mouse.lLastX;
		const LONG deltaY = input.data.mouse.lLastY;

		if (deltaX != 0L)
		{
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseXDelta, .inputValue = static_cast<float>(deltaX) * sensitivity, .inputType = InputType::Delta});
		}
		if (deltaY != 0L)
		{
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseYDelta, .inputValue = static_cast<float>(deltaY) * sensitivity, .inputType = InputType::Delta});
		}
	}

	void MouseDevice::ObserveXButton(const WPARAM wParam, const bool isDown)
	{
		switch (GET_XBUTTON_WPARAM(wParam))
		{
		case 1:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseButton4, .inputValue = static_cast<float>(isDown), .inputType = InputType::State});
			break;
		case 2:
			InputSystem().AddInputEvent(*this, InputEvent{.inputCode = InputCode::MouseButton5, .inputValue = static_cast<float>(isDown), .inputType = InputType::State});
			break;
		default:
			break;
		}
	}
}
