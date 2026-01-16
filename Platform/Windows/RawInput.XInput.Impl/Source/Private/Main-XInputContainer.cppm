/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

#include <xinput.h>

export module PonyEngine.RawInput.XInput.Impl.Windows:XInputContainer;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::RawInput::Windows
{
	/// @brief XInput gamepad container.
	class XInputContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		XInputContainer() noexcept;
		XInputContainer(const XInputContainer&) = delete;
		XInputContainer(XInputContainer&&) = delete;

		~XInputContainer() noexcept = default;

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

		XInputContainer& operator =(const XInputContainer&) = delete;
		XInputContainer& operator =(XInputContainer&&) = delete;

	private:
		std::array<struct DeviceHandle, XUSER_MAX_COUNT> deviceHandles; ///< Device handles.
		std::array<XINPUT_GAMEPAD, XUSER_MAX_COUNT> gamepadStates; ///< Gamepad states.
		std::array<bool, XUSER_MAX_COUNT> connections; ///< Gamepad connection statuses.
	};
}

namespace PonyEngine::RawInput::Windows
{
	XInputContainer::XInputContainer() noexcept
	{
		std::ranges::fill(deviceHandles, RawInput::DeviceHandle{});
		std::ranges::fill(gamepadStates, XINPUT_GAMEPAD{});
		std::ranges::fill(connections, false);
	}

	DWORD XInputContainer::Size() const noexcept
	{
		return static_cast<DWORD>(deviceHandles.size());
	}

	DWORD XInputContainer::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return static_cast<DWORD>(std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin());
	}

	struct DeviceHandle& XInputContainer::DeviceHandle(const DWORD index) noexcept
	{
		return deviceHandles[index];
	}

	const struct DeviceHandle& XInputContainer::DeviceHandle(const DWORD index) const noexcept
	{
		return deviceHandles[index];
	}

	const XINPUT_GAMEPAD& XInputContainer::GamepadState(const DWORD index) const noexcept
	{
		return gamepadStates[index];
	}

	void XInputContainer::GamepadState(const DWORD index, const XINPUT_GAMEPAD& state) noexcept
	{
		gamepadStates[index] = state;
	}

	bool XInputContainer::IsConnected(const DWORD index) const noexcept
	{
		return connections[index];
	}

	void XInputContainer::Connect(const DWORD index, const bool isConnected) noexcept
	{
		connections[index] = isConnected;
	}
}
