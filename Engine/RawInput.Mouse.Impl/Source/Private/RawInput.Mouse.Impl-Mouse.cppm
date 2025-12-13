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
	class Mouse final : public IDevice
	{
	public:
		/// @brief Creates a mouse device.
		/// @param name Device name.
		/// @param deviceType Device type.
		/// @param isConnected Is the mouse connected?
		[[nodiscard("Pure constructor")]]
		Mouse(std::string_view name, DeviceTypeId deviceType, bool isConnected);
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;

		~Mouse() noexcept = default;

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

		Mouse& operator =(const Mouse&) = delete;
		Mouse& operator =(Mouse&&) = delete;

	private:
		std::string name; ///< Mouse device name.
		DeviceTypeId deviceType; ///< Mouse device type.

		std::array<bool, static_cast<std::size_t>(MouseButton::Count)> buttonState; ///< Button states. They are placed in the order they are declared in the enum.
		bool isConnected;
	};
}

namespace PonyEngine::Input
{
	Mouse::Mouse(const std::string_view name, const DeviceTypeId deviceType, const bool isConnected) :
		name(name),
		deviceType(deviceType),
		isConnected{isConnected}
	{
		ResetButtons();
	}

	std::string_view Mouse::Name() const noexcept
	{
		return name;
	}

	DeviceTypeId Mouse::DeviceType() const noexcept
	{
		return deviceType;
	}

	std::span<const std::type_index> Mouse::FeatureTypes() const noexcept
	{
		return std::span<const std::type_index>();
	}

	void* Mouse::FindFeature(const std::type_index type) noexcept
	{
		return nullptr;
	}

	const void* Mouse::FindFeature(const std::type_index type) const noexcept
	{
		return nullptr;
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
