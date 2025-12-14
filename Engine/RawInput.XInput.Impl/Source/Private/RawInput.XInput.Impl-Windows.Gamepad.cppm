/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/GamepadInput.h"

export module PonyEngine.RawInput.XInput.Impl:Windows.Gamepad;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad.
	class Gamepad final
	{
	public:
		/// @brief Creates an XInput gamepad.
		/// @param isConnected Is the gamepad connected?
		[[nodiscard("Pure constructor")]]
		explicit Gamepad(bool isConnected);
		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&&) = delete;

		~Gamepad() noexcept = default;

		/// @brief Gets the gamepad state.
		/// @return Gamepad state.
		[[nodiscard("Pure function")]]
		const XINPUT_GAMEPAD& GamepadState() const noexcept;
		/// @brief Sets the gamepad state.
		/// @param state Gamepad state.
		void GamepadState(const XINPUT_GAMEPAD& state) noexcept;

		/// @brief Gets the connection status.
		/// @return Is the gamepad connected?
		[[nodiscard("Pure function")]]
		bool IsConnected() const noexcept;
		/// @brief Sets the connection status.
		/// @param isConnected Is the gamepad connected?
		void Connect(bool isConnected) noexcept;

		Gamepad& operator =(const Gamepad&) = delete;
		Gamepad& operator =(Gamepad&&) = delete;

	private:
		XINPUT_GAMEPAD gamepadState; ///< Gamepad state.
		bool isConnected; ///< Is the gamepad connected?
	};
}

namespace PonyEngine::Input::Windows
{
	Gamepad::Gamepad(const bool isConnected) :
		gamepadState{},
		isConnected{isConnected}
	{
	}

	const XINPUT_GAMEPAD& Gamepad::GamepadState() const noexcept
	{
		return gamepadState;
	}

	void Gamepad::GamepadState(const XINPUT_GAMEPAD& state) noexcept
	{
		gamepadState = state;
	}

	bool Gamepad::IsConnected() const noexcept
	{
		return isConnected;
	}

	void Gamepad::Connect(const bool isConnected) noexcept
	{
		this->isConnected = isConnected;
	}
}
