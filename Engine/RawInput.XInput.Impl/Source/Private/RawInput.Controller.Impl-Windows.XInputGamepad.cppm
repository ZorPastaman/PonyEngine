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

export module PonyEngine.RawInput.XInput.Impl:Windows.XInputGamepad;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad.
	class Gamepad final : public IDevice, private IVibrating
	{
	public:
		/// @brief Creates an XInput gamepad.
		/// @param name Gamepad name.
		/// @param deviceType Device type.
		/// @param isConnected Is the gamepad connected?
		[[nodiscard("Pure constructor")]]
		Gamepad(std::string_view name, DeviceTypeId deviceType, bool isConnected);
		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&&) = delete;

		~Gamepad() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::string_view Name() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual DeviceTypeId DeviceType() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::span<const std::type_index> FeatureTypes() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual void* FindFeature(std::type_index type) noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const void* FindFeature(std::type_index type) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual VibrationState State() const noexcept override;
		virtual void State(const VibrationState& state) noexcept override;

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
		static inline const std::array<std::type_index, 1> Features = { typeid(IVibrating) }; ///< Gamepad features.

		std::string name; ///< Gamepad name.
		DeviceTypeId deviceType; ///< Gamepad device type.

		XINPUT_GAMEPAD gamepadState; ///< Gamepad state.
		VibrationState vibrationState; ///< Gamepad vibration state.
		bool isConnected; ///< Is the gamepad connected?
	};
}

namespace PonyEngine::Input::Windows
{
	Gamepad::Gamepad(const std::string_view name, const DeviceTypeId deviceType, const bool isConnected) :
		name(name),
		deviceType(deviceType),
		gamepadState{},
		vibrationState{},
		isConnected{isConnected}
	{
	}

	std::string_view Gamepad::Name() const noexcept
	{
		return name;
	}

	DeviceTypeId Gamepad::DeviceType() const noexcept
	{
		return deviceType;
	}

	std::span<const std::type_index> Gamepad::FeatureTypes() const noexcept
	{
		return Features;
	}

	void* Gamepad::FindFeature(const std::type_index type) noexcept
	{
		if (type == typeid(IVibrating))
		{
			return static_cast<IVibrating*>(this);
		}

		return nullptr;
	}

	const void* Gamepad::FindFeature(const std::type_index type) const noexcept
	{
		if (type == typeid(IVibrating))
		{
			return static_cast<const IVibrating*>(this);
		}

		return nullptr;
	}

	VibrationState Gamepad::State() const noexcept
	{
		return vibrationState;
	}

	void Gamepad::State(const VibrationState& state) noexcept
	{
		vibrationState = VibrationState
		{
			.lowFrequency = std::clamp(state.lowFrequency, 0.f, 1.f),
			.highFrequency = std::clamp(state.highFrequency, 0.f, 1.f)
		};
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
