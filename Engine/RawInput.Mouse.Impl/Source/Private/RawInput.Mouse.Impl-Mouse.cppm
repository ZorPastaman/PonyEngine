/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:Mouse;

import std;

import PonyEngine.RawInput;

import :MouseAxis;

export namespace PonyEngine::Input
{
	/// @brief Mouse device.
	class Mouse final
	{
	public:
		/// @brief Creates a mouse device.
		/// @param name Device name.
		/// @param isConnected Is the mouse connected?
		[[nodiscard("Pure constructor")]]
		Mouse(std::string_view name, bool isConnected);
		[[nodiscard("Pure constructor")]]
		Mouse(const Mouse& other) = default;
		[[nodiscard("Pure constructor")]]
		Mouse(Mouse&&) noexcept = default;

		~Mouse() noexcept = default;

		/// @brief Gets the mouse name.
		/// @return Mouse name.
		[[nodiscard("Pure function")]]
		std::string_view Name() const noexcept;

		/// @brief Checks if the button pressed.
		/// @param button Button ID.
		/// @return @a True if it's pressed; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsPressed(MouseButton button) const noexcept;
		/// @brief Gets all the button states.
		/// @return Button states.
		/// @remark They are placed in the order they are declared in the enum.
		[[nodiscard("Pure function")]]
		std::span<const bool, static_cast<std::size_t>(MouseButton::Count)> ButtonStates() const noexcept;
		/// @brief Sets a button state.
		/// @param button Button ID.
		/// @param value Button state.
		void Press(MouseButton button, bool value) noexcept;
		/// @brief Resets all the buttons to the false state.
		void ResetButtons() noexcept;

		/// @brief Gets the connection status.
		/// @return Connection status.
		[[nodiscard("Pure function")]]
		bool IsConnected() const noexcept;
		/// @brief Sets the connection status.
		/// @param isConnected Connection status.
		void Connect(bool isConnected) noexcept;

		Mouse& operator =(const Mouse& other) = default;
		Mouse& operator =(Mouse&& other) noexcept = default;

	private:
		std::string name; ///< Mouse device name.

		std::array<bool, static_cast<std::size_t>(MouseButton::Count)> buttonState; ///< Button states. They are placed in the order they are declared in the enum.
		bool isConnected;
	};
}

namespace PonyEngine::Input
{
	Mouse::Mouse(const std::string_view name, const bool isConnected) :
		name(name),
		isConnected{isConnected}
	{
		ResetButtons();
	}

	std::string_view Mouse::Name() const noexcept
	{
		return name;
	}

	bool Mouse::IsPressed(const MouseButton button) const noexcept
	{
		return buttonState[static_cast<std::size_t>(button)];
	}

	std::span<const bool, static_cast<std::size_t>(MouseButton::Count)> Mouse::ButtonStates() const noexcept
	{
		return buttonState;
	}

	void Mouse::Press(const MouseButton button, const bool value) noexcept
	{
		buttonState[static_cast<std::size_t>(button)] = value;
	}

	void Mouse::ResetButtons() noexcept
	{
		std::ranges::fill(buttonState, false);
	}

	bool Mouse::IsConnected() const noexcept
	{
		return isConnected;
	}

	void Mouse::Connect(const bool isConnected) noexcept
	{
		this->isConnected = isConnected;
	}
}
