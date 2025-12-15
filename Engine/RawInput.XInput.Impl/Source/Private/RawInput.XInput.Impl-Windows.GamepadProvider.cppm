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
#include "PonyEngine/Platform/Windows/Input.h"

export module PonyEngine.RawInput.XInput.Impl:Windows.GamepadProvider;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.RawInput.Ext;
import PonyEngine.Surface;

import :Windows.GamepadAxisMap;
import :Windows.GamepadContainer;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad provider.
	class GamepadProvider final : public IInputProvider
	{
	public:
		/// @brief Creates an XInput gamepad provider.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit GamepadProvider(IRawInputContext& input) noexcept;
		GamepadProvider(const GamepadProvider&) = delete;
		GamepadProvider(GamepadProvider&&) = delete;

		~GamepadProvider() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;
		virtual void Tick() override;

		GamepadProvider& operator =(const GamepadProvider&) = delete;
		GamepadProvider& operator =(GamepadProvider&&) = delete;

	private:
		/// @brief Vibrator feature.
		class Vibrator final : public IVibrating
		{
		public:
			[[nodiscard("Pure constructor")]]
			Vibrator() noexcept = default;
			/// @brief Creates a vibrator.
			/// @param provider Gamepad provider.
			/// @param gamepadIndex Gamepad index.
			[[nodiscard("Pure constructor")]]
			Vibrator(GamepadProvider& provider, DWORD gamepadIndex) noexcept;
			[[nodiscard("Pure constructor")]]
			Vibrator(const Vibrator& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			Vibrator(Vibrator&& other) noexcept = default;

			~Vibrator() noexcept = default;

			[[nodiscard("Pure function")]] 
			virtual VibrationState State() const override;
			virtual void State(const VibrationState& state) override;

			Vibrator& operator =(const Vibrator& other) noexcept = default;
			Vibrator& operator =(Vibrator&& other) noexcept = default;

		private:
			GamepadProvider* provider; ///< Gamepad provider.
			DWORD gamepadIndex; ///< Gamepad index.
		};

		/// @brief Creates devices.
		/// @param count How many devices were created.
		void CreateDevices(DWORD& count);
		/// @brief Destroys devices.
		/// @param count How many devices were created.
		void DestroyDevices(DWORD count);

		/// @brief Connects a gamepad or does nothing if it's already connected.
		/// @param index Gamepad index.
		/// @param now Event time.
		void ConnectGamepad(DWORD index, std::chrono::time_point<std::chrono::steady_clock> now);
		/// @brief Disconnects a gamepad or does nothing if it's already disconnected.
		/// @param index Gamepad index.
		/// @param now Event time.
		void DisconnectGamepad(DWORD index, std::chrono::time_point<std::chrono::steady_clock> now);

		/// @brief Updates a gamepad input.
		/// @param index Gamepad index.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		void UpdateInput(DWORD index, const XINPUT_GAMEPAD& currentState, std::chrono::time_point<std::chrono::steady_clock> now);
		/// @brief Updates a button input.
		/// @param handle Device handle.
		/// @param prevState Previous gamepad state.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		void UpdateButtonInput(DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState,
			std::chrono::time_point<std::chrono::steady_clock> now);
		/// @brief Updates a trigger input.
		/// @param handle Device handle.
		/// @param prevState Previous gamepad state.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		void UpdateTriggerInput(DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState,
			std::chrono::time_point<std::chrono::steady_clock> now);
		/// @brief Updates a stick input.
		/// @param handle Device handle.
		/// @param prevState Previous gamepad state.
		/// @param currentState Current gamepad state.
		/// @param now Event time.
		void UpdateStickInput(DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState,
			std::chrono::time_point<std::chrono::steady_clock> now);
		/// @brief Updates a vibration state.
		/// @param index Gamepad index.
		void UpdateVibration(DWORD index);
		/// @brief Updates a vibration state.
		/// @param index Gamepad index.
		/// @param state Vibration state.
		void UpdateVibration(DWORD index, const VibrationState& state);

		/// @brief Gets a gamepad vibration state.
		/// @param gamepadIndex Gamepad index.
		/// @return Vibration state.
		[[nodiscard("Pure function")]]
		const VibrationState& Vibration(DWORD gamepadIndex) const noexcept;
		/// @brief Sets a gamepad vibration state.
		/// @param gamepadIndex Gamepad index.
		/// @param state Vibration state.
		void Vibration(DWORD gamepadIndex, const VibrationState& state) noexcept;

		IRawInputContext* input; ///< Raw input context.
		Surface::ISurfaceService* surface; ///< Surface service.

		GamepadAxisMap axisMap; ///< Gamepad axis map.
		GamepadContainer gamepadContainer; ///< Gamepad containers.
		std::array<Vibrator, XUSER_MAX_COUNT> vibrators; ///< Gamepad 
	};
}

namespace PonyEngine::Input::Windows
{
	GamepadProvider::GamepadProvider(IRawInputContext& input) noexcept :
		input{&input},
		surface{&this->input->Application().GetService<Surface::ISurfaceService>()},
		axisMap(*this->input)
	{
		for (DWORD i = 0uz; i < XUSER_MAX_COUNT; ++i)
		{
			vibrators[i] = Vibrator(*this, i);
		}
	}

	void GamepadProvider::Begin()
	{
		DWORD count = 0uz;

		try
		{
			CreateDevices(count);
		}
		catch (...)
		{
			DestroyDevices(count);
			throw;
		}
	}

	void GamepadProvider::End()
	{
		DestroyDevices(XUSER_MAX_COUNT);
	}

	void GamepadProvider::Tick()
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			const std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();

			XINPUT_CAPABILITIES caps = {};
			if (const DWORD capsResult = XInputGetCapabilities(i, 0, &caps); capsResult == ERROR_SUCCESS)
			{
				if (caps.Type == XINPUT_DEVTYPE_GAMEPAD)
				{
					XINPUT_STATE state = {};
					if (const DWORD stateResult = XInputGetState(i, &state); stateResult == ERROR_SUCCESS)
					{
						ConnectGamepad(i, now);

						if (surface->IsInFocus()) [[likely]]
						{
							UpdateInput(i, state.Gamepad, now);
							UpdateVibration(i);
						}
						else [[unlikely]]
						{
							UpdateInput(i, XINPUT_GAMEPAD{}, now);
							UpdateVibration(i, VibrationState{});
						}

						continue;
					}
					else
					{
						PONY_LOG_IF(stateResult != ERROR_DEVICE_NOT_CONNECTED, input->Logger(), Log::LogType::Error,
							"Failed to get XInput gamepad state. Error code: '0x{:X}'.", stateResult);
					}
				}
			}
			else
			{
				PONY_LOG_IF(capsResult != ERROR_DEVICE_NOT_CONNECTED, input->Logger(), Log::LogType::Error,
					"Failed to get XInput device capabilities. Error code: '0x{:X}'.", capsResult);
			}

			DisconnectGamepad(i, now);
		}
	}

	GamepadProvider::Vibrator::Vibrator(GamepadProvider& provider, const DWORD gamepadIndex) noexcept :
		provider{&provider},
		gamepadIndex{gamepadIndex}
	{
	}

	VibrationState GamepadProvider::Vibrator::State() const
	{
		return provider->Vibration(gamepadIndex);
	}

	void GamepadProvider::Vibrator::State(const VibrationState& state)
	{
		provider->Vibration(gamepadIndex, state);
	}

	void GamepadProvider::CreateDevices(DWORD& count)
	{
		const DeviceTypeId type = input->Hash(DeviceType(GamepadDevice::XboxType));

		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			IVibrating& vibrator = vibrators[i] = Vibrator(*this, i);

			auto data = DeviceData{};
			data.SetDevice(std::format("XInputGamepad_{}", i), type, false);
			data.AddFeature(vibrator);
			const DeviceHandle handle = input->RegisterDevice(data);

			gamepadContainer.DeviceHandle(i) = handle;
			gamepadContainer.Connect(i, false);
			++count;
		}
	}

	void GamepadProvider::DestroyDevices(const DWORD count)
	{
		for (DWORD i = count; i-- > 0; )
		{
			input->UnregisterDevice(gamepadContainer.DeviceHandle(i));
			gamepadContainer.DeviceHandle(i) = DeviceHandle{};
		}
	}

	void GamepadProvider::ConnectGamepad(const DWORD index, const std::chrono::time_point<std::chrono::steady_clock> now)
	{
		if (gamepadContainer.IsConnected(index))
		{
			return;
		}

		input->Connect(gamepadContainer.DeviceHandle(index), ConnectionEvent{.isConnected = true, .timePoint = now});
		gamepadContainer.Connect(index, true);
	}

	void GamepadProvider::DisconnectGamepad(const DWORD index, const std::chrono::time_point<std::chrono::steady_clock> now)
	{
		if (!gamepadContainer.IsConnected(index))
		{
			return;
		}

		UpdateInput(index, XINPUT_GAMEPAD{}, now);
		input->Connect(gamepadContainer.DeviceHandle(index), ConnectionEvent{.isConnected = false, .timePoint = now});
		gamepadContainer.Connect(index, false);
		gamepadContainer.VibrationState(index, VibrationState{});
	}

	void GamepadProvider::UpdateInput(const DWORD index, const XINPUT_GAMEPAD& currentState, const std::chrono::time_point<std::chrono::steady_clock> now)
	{
		const XINPUT_GAMEPAD& prevState = gamepadContainer.GamepadState(index);
		if (std::memcmp(&currentState, &prevState, sizeof(XINPUT_GAMEPAD)) == 0)
		{
			return;
		}

		const DeviceHandle handle = gamepadContainer.DeviceHandle(index);
		UpdateButtonInput(handle, prevState, currentState, now);
		UpdateTriggerInput(handle, prevState, currentState, now);
		UpdateStickInput(handle, prevState, currentState, now);
		gamepadContainer.GamepadState(index, currentState);
	}

	void GamepadProvider::UpdateButtonInput(const DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState, 
		const std::chrono::time_point<std::chrono::steady_clock> now)
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
			const WORD prev = prevState.wButtons & button;
			const WORD current = currentState.wButtons & button;
			if (prev == current)
			{
				continue;
			}

			const bool pressed = current;
			const float value = pressed;
			const AxisId axis = axisMap.Button(button);
			input->AddInput(handle, RawInputEvent
			{
				.axes = std::span<const AxisId>(&axis, 1uz),
				.values = std::span<const float>(&value, 1uz),
				.eventType = InputEventType::State,
				.timePoint = now
			});
		}
	}

	void GamepadProvider::UpdateTriggerInput(const DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState, 
		const std::chrono::time_point<std::chrono::steady_clock> now)
	{
		const auto updateTriggerInput = [&](const BYTE prev, const BYTE current, const GamepadAxisMap::TriggerAxis trigger)
		{
			if (prev == current || (prev <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && current <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD))
			{
				return;
			}

			const float value = current > XINPUT_GAMEPAD_TRIGGER_THRESHOLD
				? static_cast<float>(current - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (std::numeric_limits<BYTE>::max() - XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				: 0.f;
			const AxisId axis = axisMap.Trigger(trigger);
			input->AddInput(handle, RawInputEvent
			{
				.axes = std::span<const AxisId>(&axis, 1uz),
				.values = std::span<const float>(&value, 1uz),
				.eventType = InputEventType::State,
				.timePoint = now
			});
		};

		updateTriggerInput(prevState.bLeftTrigger, currentState.bLeftTrigger, GamepadAxisMap::TriggerAxis::Left);
		updateTriggerInput(prevState.bRightTrigger, currentState.bRightTrigger, GamepadAxisMap::TriggerAxis::Right);
	}

	void GamepadProvider::UpdateStickInput(const DeviceHandle handle, const XINPUT_GAMEPAD& prevState, const XINPUT_GAMEPAD& currentState, 
		const std::chrono::time_point<std::chrono::steady_clock> now)
	{
		const auto calculateValue = [](const Math::Vector2<float> current, const float threshold) noexcept
		{
			const auto denominator = Math::Vector2<float>(std::numeric_limits<SHORT>::max()) - Math::Vector2<float>(threshold);
			const auto numerator = current - Math::ClampMagnitude(current, threshold);

			return Math::ClampMagnitude(Math::Divide(numerator, denominator), 1.f);
		};

		const auto updateStickInput = [&](const Math::Vector2<SHORT> prev, const Math::Vector2<SHORT> current, const SHORT threshold, 
			const GamepadAxisMap::StickPlacement placement)
		{
			if (prev == current)
			{
				return;
			}

			const auto prevFloat = static_cast<Math::Vector2<float>>(prev);
			const auto currentFloat = static_cast<Math::Vector2<float>>(current);
			const float thresholdFloat = threshold;
			const float prevMagnitude = prevFloat.Magnitude();
			const float currentMagnitude = currentFloat.Magnitude();

			if (prevMagnitude <= threshold && currentMagnitude <= threshold)
			{
				return;
			}

			const auto value = currentMagnitude > threshold
				? calculateValue(currentFloat, thresholdFloat)
				: Math::Vector2<float>::Zero();
			input->AddInput(handle, RawInputEvent
			{
				.axes = axisMap.Stick(placement),
				.values = value.Span(),
				.eventType = InputEventType::State,
				.timePoint = now
			});
		};

		updateStickInput(Math::Vector2<SHORT>(prevState.sThumbLX, prevState.sThumbLY), Math::Vector2<SHORT>(currentState.sThumbLX, currentState.sThumbLY),
			XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, GamepadAxisMap::StickPlacement::Left);
		updateStickInput(Math::Vector2<SHORT>(prevState.sThumbRX, prevState.sThumbRY), Math::Vector2<SHORT>(currentState.sThumbRX, currentState.sThumbRY),
			XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, GamepadAxisMap::StickPlacement::Right);
	}

	void GamepadProvider::UpdateVibration(const DWORD index)
	{
		UpdateVibration(index, gamepadContainer.VibrationState(index));
	}

	void GamepadProvider::UpdateVibration(const DWORD index, const VibrationState& state)
	{
		auto vibration = XINPUT_VIBRATION
		{
			.wLeftMotorSpeed = Math::RoundToIntegral<WORD>(state.lowFrequency * std::numeric_limits<WORD>::max()),
			.wRightMotorSpeed = Math::RoundToIntegral<WORD>(state.highFrequency * std::numeric_limits<WORD>::max())
		};

		const DWORD result = XInputSetState(index, &vibration);
		PONY_LOG_IF(result != ERROR_SUCCESS && result != ERROR_DEVICE_NOT_CONNECTED, input->Logger(), Log::LogType::Error,
			"Failed to set XInput device vibration. Error code: '0x{:X}'.", result);
	}

	const VibrationState& GamepadProvider::Vibration(const DWORD gamepadIndex) const noexcept
	{
		return gamepadContainer.VibrationState(gamepadIndex);
	}

	void GamepadProvider::Vibration(const DWORD gamepadIndex, const VibrationState& state) noexcept
	{
		if (!gamepadContainer.IsConnected(gamepadIndex))
		{
			return;
		}

		gamepadContainer.VibrationState(gamepadIndex, state);
		UpdateVibration(gamepadIndex);
	}
}
