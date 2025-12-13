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

export module PonyEngine.RawInput.Controller.Impl:Windows.XInputGamepadContainer;

import std;

import PonyEngine.RawInput.Ext;

import :Windows.XInputGamepad;

export namespace PonyEngine::Input::Windows
{
	/// @brief XInput gamepad container.
	class XInputGamepadContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		XInputGamepadContainer() noexcept = default;
		XInputGamepadContainer(const XInputGamepadContainer&) = delete;
		XInputGamepadContainer(XInputGamepadContainer&&) = delete;

		~XInputGamepadContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds a gamepad index by the @p deviceHandle.
		/// @param deviceHandle Device handle.
		/// @return Gamepad index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(struct DeviceHandle deviceHandle) const noexcept;
		/// @brief Finds a gamepad index.
		/// @param gamepad Gamepad.
		/// @return Gamepad index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(const XInputGamepad& gamepad) const noexcept;

		/// @brief Gets a device handle.
		/// @param index Gamepad index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		struct DeviceHandle& DeviceHandle(std::size_t index) noexcept;
		/// @brief Gets a device handle.
		/// @param index Gamepad index.
		/// @return Device handle.
		[[nodiscard("Pure function")]]
		const struct DeviceHandle& DeviceHandle(std::size_t index) const noexcept;
		/// @brief Gets a gamepad.
		/// @param index Gamepad index.
		/// @return Gamepad.
		[[nodiscard("Pure function")]]
		XInputGamepad* Gamepad(std::size_t index) noexcept;
		/// @brief Gets a gamepad.
		/// @param index Gamepad index.
		/// @return Gamepad.
		[[nodiscard("Pure function")]]
		const XInputGamepad* Gamepad(std::size_t index) const noexcept;

		void Set(std::size_t index, struct DeviceHandle handle, const std::shared_ptr<XInputGamepad>& gamepad) noexcept;
		void Unset(std::size_t index) noexcept;

		XInputGamepadContainer& operator =(const XInputGamepadContainer&) = delete;
		XInputGamepadContainer& operator =(XInputGamepadContainer&&) = delete;

	private:
		std::array<struct DeviceHandle, XUSER_MAX_COUNT> deviceHandles; ///< Device handles.
		std::array<std::shared_ptr<XInputGamepad>, XUSER_MAX_COUNT> gamepads; ///< Gamepads.
	};
}

namespace PonyEngine::Input::Windows
{
	std::size_t XInputGamepadContainer::Size() const noexcept
	{
		return deviceHandles.size();
	}

	std::size_t XInputGamepadContainer::IndexOf(const struct DeviceHandle deviceHandle) const noexcept
	{
		return std::ranges::find(deviceHandles, deviceHandle) - deviceHandles.cbegin();
	}

	std::size_t XInputGamepadContainer::IndexOf(const XInputGamepad& gamepad) const noexcept
	{
		return std::ranges::find_if(gamepads, [&](const std::shared_ptr<XInputGamepad>& g) { return g.get() == &gamepad; }) - gamepads.cbegin();
	}

	struct DeviceHandle& XInputGamepadContainer::DeviceHandle(const std::size_t index) noexcept
	{
		return deviceHandles[index];
	}

	const struct DeviceHandle& XInputGamepadContainer::DeviceHandle(const std::size_t index) const noexcept
	{
		return deviceHandles[index];
	}

	XInputGamepad* XInputGamepadContainer::Gamepad(const std::size_t index) noexcept
	{
		return gamepads[index].get();
	}

	const XInputGamepad* XInputGamepadContainer::Gamepad(const std::size_t index) const noexcept
	{
		return gamepads[index].get();
	}

	void XInputGamepadContainer::Set(const std::size_t index, const struct DeviceHandle handle, const std::shared_ptr<XInputGamepad>& gamepad) noexcept
	{
		deviceHandles[index] = handle;
		gamepads[index] = gamepad;
	}

	void XInputGamepadContainer::Unset(const std::size_t index) noexcept
	{
		deviceHandles[index] = Input::DeviceHandle{};
		gamepads[index].reset();
	}
}
