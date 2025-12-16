/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Input.h"

export module PonyEngine.RawInput.XInput.Impl:Windows.GamepadContainer;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad container.
	class GamepadContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		GamepadContainer() noexcept;
		GamepadContainer(const GamepadContainer&) = delete;
		GamepadContainer(GamepadContainer&&) = delete;

		~GamepadContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		DWORD Size() const noexcept;

		/// @brief Finds a gamepad index by the @p deviceHandle.
		/// @param deviceHandle Device handle.
		/// @return Gamepad index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		DWORD IndexOf(struct DeviceHandle deviceHandle) const noexcept;

		/// @brief Gets a device handle.
		/// @param index Gamepad index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		struct DeviceHandle& DeviceHandle(DWORD index) noexcept;
		/// @brief Gets a device handle.
		/// @param index Gamepad index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		const struct DeviceHandle& DeviceHandle(DWORD index) const noexcept;

		/// @brief Gets a gamepad state.
		/// @param index Gamepad index.
		/// @return Gamepad state.
		[[nodiscard("Pure function")]]
		const XINPUT_GAMEPAD& GamepadState(DWORD index) const noexcept;
		/// @brief Sets a gamepad state.
		/// @param index Gamepad index.
		/// @param state Gamepad state.
		void GamepadState(DWORD index, const XINPUT_GAMEPAD& state) noexcept;

		/// @brief Gets a device connection status.
		/// @param index Gamepad index.
		/// @return Connection status.
		[[nodiscard("Pure function")]]
		bool IsConnected(DWORD index) const noexcept;
		/// @brief Sets a device connection status.
		/// @param index Gamepad index.
		/// @param isConnected Connection status.
		void Connect(DWORD index, bool isConnected) noexcept;

		/// @brief Gets a vibration state.
		/// @param index Gamepad index.
		/// @return Vibration state.
		[[nodiscard("Pure function")]]
		const struct VibrationState& VibrationState(DWORD index) const noexcept;
		/// @brief Sets a vibration state.
		/// @param index Gamepad index.
		/// @param state Vibration state.
		void VibrationState(DWORD index, const struct VibrationState& state) noexcept;

		GamepadContainer& operator =(const GamepadContainer&) = delete;
		GamepadContainer& operator =(GamepadContainer&&) = delete;

	private:
		std::array<struct DeviceHandle, XUSER_MAX_COUNT> deviceHandles; ///< Device handles.
		std::array<XINPUT_GAMEPAD, XUSER_MAX_COUNT> gamepadStates; ///< Gamepad states.
		std::array<bool, XUSER_MAX_COUNT> connections; ///< Gamepad connection statuses.
		std::array<struct VibrationState, XUSER_MAX_COUNT> vibrationStates; ///< Gamepad vibration states.
	};
}

namespace PonyEngine::Input::Windows
{
	GamepadContainer::GamepadContainer() noexcept
	{
		std::ranges::fill(deviceHandles, Input::DeviceHandle{});
		std::ranges::fill(gamepadStates, XINPUT_GAMEPAD{});
		std::ranges::fill(connections, false);
		std::ranges::fill(vibrationStates, Input::VibrationState{});
	}

	DWORD GamepadContainer::Size() const noexcept
	{
		return static_cast<DWORD>(deviceHandles.size());
	}

	DWORD GamepadContainer::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return static_cast<DWORD>(std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin());
	}

	struct DeviceHandle& GamepadContainer::DeviceHandle(const DWORD index) noexcept
	{
		return deviceHandles[index];
	}

	const struct DeviceHandle& GamepadContainer::DeviceHandle(const DWORD index) const noexcept
	{
		return deviceHandles[index];
	}

	const XINPUT_GAMEPAD& GamepadContainer::GamepadState(const DWORD index) const noexcept
	{
		return gamepadStates[index];
	}

	void GamepadContainer::GamepadState(const DWORD index, const XINPUT_GAMEPAD& state) noexcept
	{
		gamepadStates[index] = state;
	}

	bool GamepadContainer::IsConnected(const DWORD index) const noexcept
	{
		return connections[index];
	}

	void GamepadContainer::Connect(const DWORD index, const bool isConnected) noexcept
	{
		connections[index] = isConnected;
	}

	const struct VibrationState& GamepadContainer::VibrationState(const DWORD index) const noexcept
	{
		return vibrationStates[index];
	}

	void GamepadContainer::VibrationState(const DWORD index, const struct VibrationState& state) noexcept
	{
		vibrationStates[index] = state;
	}
}
