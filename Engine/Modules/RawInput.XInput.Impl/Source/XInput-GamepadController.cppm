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

export module PonyEngine.RawInput.XInput.Impl:GamepadController;

import std;

import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.RawInput.Ext;

import :GamepadAxisMap;

export namespace PonyEngine::RawInput::XInput
{
	/// @brief XInput gamepad controller.
	class GamepadController final : public IVibrating, private IDeviceController
	{
	public:
		[[nodiscard("Pure constructor")]]
		GamepadController() noexcept = default;
		/// @brief Creates an XInput gamepad controller.
		/// @param axisMap Axis map.
		/// @param logService Log service.
		/// @param gamepadIndex Gamepad index.
		[[nodiscard("Pure constructor")]]
		GamepadController(const GamepadAxisMap& axisMap, const Log::ILogService* logService, DWORD gamepadIndex) noexcept;
		[[nodiscard("Pure constructor")]]
		GamepadController(const GamepadController& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		GamepadController(GamepadController&& other) noexcept = default;

		~GamepadController() noexcept = default;

		virtual void Vibrate(float lowFrequency, float highFrequency) override;

		/// @brief Checks if a gamepad is connected.
		/// @return @a True if it's connected; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsConnected() const noexcept;

		/// @brief Gets the device controller.
		/// @return Device controller.
		[[nodiscard("Pure function")]]
		IDeviceController& Controller() noexcept;

		GamepadController& operator =(const GamepadController& other) noexcept = default;
		GamepadController& operator =(GamepadController&& other) noexcept = default;

	private:
		virtual void Tick(IInputRegistry& inputRegistry) override;

		/// @brief Updates a connection state.
		/// @param isConnected Is a gamepad connected now?
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateConnection(bool isConnected, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry);

		/// @brief Updates a gamepad input.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateInput(const XINPUT_STATE& currentState, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry);
		/// @brief Updates a button input.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateButtonInput(const XINPUT_GAMEPAD& currentState, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const;
		/// @brief Updates a trigger input.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateTriggerInput(const XINPUT_GAMEPAD& currentState, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const;
		/// @brief Updates a trigger input.
		/// @param trigger Trigger axis.
		/// @param previousState Previous state.
		/// @param currentState Current state.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateTriggerInput(GamepadAxisMap::TriggerAxis trigger, BYTE previousState, BYTE currentState, 
			std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const;
		/// @brief Updates a stick input.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateStickInput(const XINPUT_GAMEPAD& currentState, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const;
		/// @brief Updates a stick input.
		/// @param placement Stick placement.
		/// @param previousState Previous state.
		/// @param currentState Current state.
		/// @param threshold Dead zone threshold.
		/// @param now Event time.
		/// @param inputRegistry Input registry.
		void UpdateStickInput(GamepadAxisMap::StickPlacement placement, const Math::Vector2<SHORT>& previousState, const Math::Vector2<SHORT>& currentState,
			SHORT threshold, std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const;

		const GamepadAxisMap* axisMap; ///< Axis map.
		const Log::ILogService* logService; ///< Log service.

		DWORD gamepadIndex; ///< Gamepad index.
		XINPUT_STATE state; ///< Current state.
		bool isConnected; ///< Is gamepad connected?
	};
}

namespace PonyEngine::RawInput::XInput
{
	GamepadController::GamepadController(const GamepadAxisMap& axisMap, const Log::ILogService* const logService, const DWORD gamepadIndex) noexcept :
		axisMap{&axisMap},
		logService{logService},
		gamepadIndex{gamepadIndex},
		state{.dwPacketNumber = 0u, .Gamepad = XINPUT_GAMEPAD{.wButtons = 0u, .bLeftTrigger = 0u, .bRightTrigger = 0u, 
			.sThumbLX = 0u, .sThumbLY = 0u, .sThumbRX = 0u, .sThumbRY = 0u}},
		isConnected{false}
	{
	}

	void GamepadController::Vibrate(const float lowFrequency, const float highFrequency)
	{
		auto vibration = XINPUT_VIBRATION
		{
			.wLeftMotorSpeed = Math::RoundToIntegral<WORD>(std::clamp(lowFrequency, 0.f, 1.f) * std::numeric_limits<WORD>::max()),
			.wRightMotorSpeed = Math::RoundToIntegral<WORD>(std::clamp(highFrequency, 0.f, 1.f) * std::numeric_limits<WORD>::max())
		};
		const DWORD result = XInputSetState(gamepadIndex, &vibration);

		PONY_LOG_IF(result != ERROR_SUCCESS && result != ERROR_DEVICE_NOT_CONNECTED, logService, Log::LogType::Error,
			"Failed to set XInput device vibration. Error code: '0x{:X}'.", result);
	}

	bool GamepadController::IsConnected() const noexcept
	{
		return isConnected;
	}

	IDeviceController& GamepadController::Controller() noexcept
	{
		return *this;
	}

	void GamepadController::Tick(IInputRegistry& inputRegistry)
	{
		const std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
		XINPUT_STATE state = {};
		if (const DWORD stateResult = XInputGetState(gamepadIndex, &state); stateResult == ERROR_SUCCESS)
		{
			UpdateConnection(true, now, inputRegistry);
			UpdateInput(state, now, inputRegistry);
		}
		else
		{
			PONY_LOG_IF(stateResult != ERROR_DEVICE_NOT_CONNECTED, logService, Log::LogType::Error,
				"Failed to get XInput gamepad state. X user index: '{}'; Error code: '0x{:X}'.", gamepadIndex, stateResult);
			UpdateConnection(false, now, inputRegistry);
		}
	}

	void GamepadController::UpdateConnection(const bool isConnected, const std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry)
	{
		if (this->isConnected == isConnected)
		{
			return;
		}

		inputRegistry.Connect(ConnectionEvent{.isConnected = isConnected, .timePoint = now});
		this->isConnected = isConnected;
	}

	void GamepadController::UpdateInput(const XINPUT_STATE& currentState, const std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry)
	{
		if (state.dwPacketNumber == currentState.dwPacketNumber)
		{
			return;
		}

		UpdateStickInput(currentState.Gamepad, now, inputRegistry);
		UpdateTriggerInput(currentState.Gamepad, now, inputRegistry);
		UpdateButtonInput(currentState.Gamepad, now, inputRegistry);
		state = currentState;
	}

	void GamepadController::UpdateButtonInput(const XINPUT_GAMEPAD& currentState, const std::chrono::time_point<std::chrono::steady_clock> now, 
		IInputRegistry& inputRegistry) const
	{
		constexpr std::array<WORD, 14> buttons =
		{
			XINPUT_GAMEPAD_DPAD_UP,
			XINPUT_GAMEPAD_DPAD_DOWN,
			XINPUT_GAMEPAD_DPAD_LEFT,
			XINPUT_GAMEPAD_DPAD_RIGHT,
			XINPUT_GAMEPAD_START,
			XINPUT_GAMEPAD_BACK,
			XINPUT_GAMEPAD_LEFT_THUMB,
			XINPUT_GAMEPAD_RIGHT_THUMB,
			XINPUT_GAMEPAD_LEFT_SHOULDER,
			XINPUT_GAMEPAD_RIGHT_SHOULDER,
			XINPUT_GAMEPAD_A,
			XINPUT_GAMEPAD_B,
			XINPUT_GAMEPAD_X,
			XINPUT_GAMEPAD_Y
		};

		for (std::size_t i = 0uz; i < buttons.size(); ++i)
		{
			const WORD button = buttons[i];
			const WORD prev = state.Gamepad.wButtons & button;
			const WORD current = currentState.wButtons & button;
			if (prev == current)
			{
				continue;
			}

			const bool pressed = current;
			const float value = pressed;
			const Axis axis = axisMap->Button(button);
			inputRegistry.AddInput(RawInputEvent
			{
				.axes = std::span<const Axis>(&axis, 1uz),
				.values = std::span<const float>(&value, 1uz),
				.eventType = InputEventType::State,
				.timePoint = now
			});
		}
	}

	void GamepadController::UpdateTriggerInput(const XINPUT_GAMEPAD& currentState, const std::chrono::time_point<std::chrono::steady_clock> now, 
		IInputRegistry& inputRegistry) const
	{
		UpdateTriggerInput(GamepadAxisMap::TriggerAxis::Left, state.Gamepad.bLeftTrigger, currentState.bLeftTrigger, now, inputRegistry);
		UpdateTriggerInput(GamepadAxisMap::TriggerAxis::Right, state.Gamepad.bRightTrigger, currentState.bRightTrigger, now, inputRegistry);
	}

	void GamepadController::UpdateTriggerInput(const GamepadAxisMap::TriggerAxis trigger, const BYTE previousState, const BYTE currentState, 
		const std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const
	{
		if (previousState == currentState || (previousState <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && currentState <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
		{
			return;
		}

		const float value = Math::UnormToNormalized<float>(currentState, Math::Range<BYTE>{.min = XINPUT_GAMEPAD_TRIGGER_THRESHOLD});
		const Axis axis = axisMap->Trigger(trigger);
		inputRegistry.AddInput(RawInputEvent
		{
			.axes = std::span<const Axis>(&axis, 1uz),
			.values = std::span<const float>(&value, 1uz),
			.eventType = InputEventType::State,
			.timePoint = now
		});
	}

	void GamepadController::UpdateStickInput(const XINPUT_GAMEPAD& currentState, const std::chrono::time_point<std::chrono::steady_clock> now, 
		IInputRegistry& inputRegistry) const
	{
		UpdateStickInput(GamepadAxisMap::StickPlacement::Left, Math::Vector2<SHORT>(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY), 
			Math::Vector2<SHORT>(currentState.sThumbLX, currentState.sThumbLY), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, now, inputRegistry);
		UpdateStickInput(GamepadAxisMap::StickPlacement::Right, Math::Vector2<SHORT>(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY), 
			Math::Vector2<SHORT>(currentState.sThumbRX, currentState.sThumbRY), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, now, inputRegistry);
	}

	void GamepadController::UpdateStickInput(const GamepadAxisMap::StickPlacement placement, const Math::Vector2<SHORT>& previousState, const Math::Vector2<SHORT>& currentState,
		const SHORT threshold, const std::chrono::time_point<std::chrono::steady_clock> now, IInputRegistry& inputRegistry) const
	{
		if (previousState == currentState)
		{
			return;
		}

		const auto prevNormalized = static_cast<Math::Vector2<float>>(previousState).Normalized(threshold, std::numeric_limits<SHORT>::max());
		const auto currentNormalized = static_cast<Math::Vector2<float>>(currentState).Normalized(threshold, std::numeric_limits<SHORT>::max());
		if (prevNormalized == currentNormalized)
		{
			return;
		}

		inputRegistry.AddInput(RawInputEvent
		{
			.axes = axisMap->Stick(placement),
			.values = currentNormalized.Span(),
			.eventType = InputEventType::State,
			.timePoint = now
		});
	}
}
