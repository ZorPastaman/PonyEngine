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

import :GamepadAxis;
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
		/// @param axes Axes.
		/// @param values Values
		/// @return Input axis count.
		[[nodiscard("Must be used")]]
		std::size_t GetButtonInput(const XINPUT_GAMEPAD& currentState, std::span<Axis, ButtonCount> axes, std::span<float, ButtonCount> values) const;
		/// @brief Updates a trigger input.
		/// @param currentState Current gamepad state.
		/// @param axes Axes.
		/// @param values Values
		/// @return Input axis count.
		[[nodiscard("Must be used")]]
		std::size_t GetTriggerInput(const XINPUT_GAMEPAD& currentState, std::span<Axis, TriggerAxisCount> axes, std::span<float, TriggerAxisCount> values) const;
		/// @brief Get stick input.
		/// @param currentState Current gamepad state.
		/// @param axes Axes.
		/// @param values Values
		/// @return Input axis count.
		[[nodiscard("Must be used")]]
		std::size_t GetStickInput(const XINPUT_GAMEPAD& currentState, 
			std::span<Axis, StickPlacementCount * StickDirectionCount> axes, std::span<float, StickPlacementCount * StickDirectionCount> values) const noexcept;
		/// @brief Gets stick input.
		/// @param placement Stick placement.
		/// @param previousState Previous state.
		/// @param currentState Current state.
		/// @param threshold Dead zone threshold.
		/// @param axes Axes.
		/// @param values Values
		/// @return Input axis count.
		[[nodiscard("Must be used")]]
		std::size_t GetStickInput(StickPlacement placement, const Math::Vector2<SHORT>& previousState, const Math::Vector2<SHORT>& currentState, SHORT threshold,
			std::span<Axis, StickDirectionCount> axes, std::span<float, StickDirectionCount> values) const noexcept;

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
				"Failed to get XInput gamepad state. XInput user index: '{}'; Error code: '0x{:X}'.", gamepadIndex, stateResult);
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

		static constexpr std::size_t AxisCount = ButtonCount + TriggerAxisCount + StickPlacementCount * StickDirectionCount;
		std::array<Axis, AxisCount> axes;
		std::array<float, AxisCount> values;
		static constexpr std::array<InputType, AxisCount> Types = []() noexcept
		{
			std::array<InputType, AxisCount> array;
			std::ranges::fill(array, InputType::State);
			return array;
		}();
		std::size_t count = 0uz;

		count += GetStickInput(currentState.Gamepad, std::span<Axis, StickPlacementCount * StickDirectionCount>(&axes[count], StickPlacementCount * StickDirectionCount),
			std::span<float, StickPlacementCount * StickDirectionCount>(&values[count], StickPlacementCount * StickDirectionCount));
		count += GetTriggerInput(currentState.Gamepad, std::span<Axis, TriggerAxisCount>(&axes[count], TriggerAxisCount), 
			std::span<float, TriggerAxisCount>(&values[count], TriggerAxisCount));
		count += GetButtonInput(currentState.Gamepad, std::span<Axis, ButtonCount>(&axes[count], ButtonCount),
			std::span<float, ButtonCount>(&values[count], ButtonCount));

		if (count > 0uz)
		{
			inputRegistry.AddInput(RawInputEvent
			{
				.axes = std::span<const Axis>(axes.data(), count),
				.values = std::span<const float>(values.data(), count),
				.inputTypes = std::span<const InputType>(Types.data(), count),
				.timePoint = now
			});
		}

		state = currentState;
	}

	std::size_t GamepadController::GetButtonInput(const XINPUT_GAMEPAD& currentState, const std::span<Axis, ButtonCount> axes, const std::span<float, ButtonCount> values) const
	{
		static constexpr std::array<std::pair<WORD, Button>, ButtonCount> ButtonMap
		{
			std::pair<WORD, Button>(XINPUT_GAMEPAD_DPAD_UP, Button::DpadUp),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_DPAD_DOWN, Button::DpadDown),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_DPAD_LEFT, Button::DpadLeft),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_DPAD_RIGHT, Button::DpadRight),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_START, Button::Start),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_BACK, Button::Back),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_LEFT_THUMB, Button::LeftThumb),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_RIGHT_THUMB, Button::RightThumb),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_LEFT_SHOULDER, Button::LeftShoulder),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_RIGHT_SHOULDER, Button::RightShoulder),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_A, Button::A),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_B, Button::B),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_X, Button::X),
			std::pair<WORD, Button>(XINPUT_GAMEPAD_Y, Button::Y)
		};

		std::size_t count = 0uz;
		for (const auto [nativeButton, button] : ButtonMap)
		{
			const bool prevPressed = state.Gamepad.wButtons & nativeButton;
			const bool currentPressed = currentState.wButtons & nativeButton;
			axes[count] = axisMap->Button(button);
			values[count] = currentPressed;
			count += currentPressed != prevPressed;
		}

		return count;
	}

	std::size_t GamepadController::GetTriggerInput(const XINPUT_GAMEPAD& currentState, 
		const std::span<Axis, TriggerAxisCount> axes, const std::span<float, TriggerAxisCount> values) const
	{
		const auto prevTriggers = Math::Vector2<BYTE>(state.Gamepad.bLeftTrigger, state.Gamepad.bRightTrigger);
		const auto currentTriggers = Math::Vector2<BYTE>(currentState.bLeftTrigger, currentState.bRightTrigger);

		std::size_t count = 0uz;
		for (std::size_t i = 0uz; i < TriggerAxisCount; ++i)
		{
			const float prev = Math::UnormToNormalized<float>(prevTriggers[i], Math::Range<BYTE>{.min = XINPUT_GAMEPAD_TRIGGER_THRESHOLD});
			const float current = Math::UnormToNormalized<float>(currentTriggers[i], Math::Range<BYTE>{.min = XINPUT_GAMEPAD_TRIGGER_THRESHOLD});
			axes[count] = axisMap->Trigger(static_cast<TriggerAxis>(i));
			values[count] = current;
			count += current != prev;
		}

		return count;
	}

	std::size_t GamepadController::GetStickInput(const XINPUT_GAMEPAD& currentState, 
		const std::span<Axis, StickPlacementCount * StickDirectionCount> axes, const std::span<float, StickPlacementCount * StickDirectionCount> values) const noexcept
	{
		static constexpr auto Thresholds = std::array<SHORT, StickPlacementCount> { XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE };
		const auto prevSticks = std::array<Math::Vector2<SHORT>, StickPlacementCount>
		{
			Math::Vector2<SHORT>(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY),
			Math::Vector2<SHORT>(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY)
		};
		const auto currentSticks = std::array<Math::Vector2<SHORT>, StickPlacementCount>
		{
			Math::Vector2<SHORT>(currentState.sThumbLX, currentState.sThumbLY),
			Math::Vector2<SHORT>(currentState.sThumbRX, currentState.sThumbRY)
		};

		std::size_t count = 0uz;
		for (std::size_t i = 0uz; i < StickPlacementCount; ++i)
		{
			count += GetStickInput(static_cast<StickPlacement>(i), prevSticks[i], currentSticks[i], Thresholds[i],
				std::span<Axis, StickDirectionCount>(&axes[count], StickDirectionCount), std::span<float, StickDirectionCount>(&values[count], StickDirectionCount));
		}

		return count;
	}

	std::size_t GamepadController::GetStickInput(const StickPlacement placement, const Math::Vector2<SHORT>& previousState, const Math::Vector2<SHORT>& currentState, 
		const SHORT threshold, const std::span<Axis, StickDirectionCount> axes, const std::span<float, StickDirectionCount> values) const noexcept
	{
		const auto prevNormalized = static_cast<Math::Vector2<float>>(previousState).Normalized(threshold, std::numeric_limits<SHORT>::max(), Math::Vector2<float>::Zero());
		const auto currentNormalized = static_cast<Math::Vector2<float>>(currentState).Normalized(threshold, std::numeric_limits<SHORT>::max(), Math::Vector2<float>::Zero());
		
		std::size_t count = 0uz;
		for (std::size_t i = 0uz; i < StickDirectionCount; ++i)
		{
			const float prev = prevNormalized[i];
			const float current = currentNormalized[i];
			axes[count] = axisMap->Stick(placement, static_cast<StickDirection>(i));
			values[count] = current;
			count += current != prev;
		}

		return count;
	}
}
