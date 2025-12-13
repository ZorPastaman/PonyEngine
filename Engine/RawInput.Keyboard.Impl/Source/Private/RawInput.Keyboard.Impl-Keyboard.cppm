/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl:Keyboard;

import std;

import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
	/// @brief Keyboard device.
	class Keyboard final : public IDevice
	{
	public:
		/// @brief Creates a keyboard.
		/// @param name Keyboard name.
		/// @param deviceType Device type.
		/// @param isConnected Is the keyboard connected?
		[[nodiscard("Pure constuctor")]]
		Keyboard(std::string_view name, DeviceTypeId deviceType, bool isConnected);
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;

		~Keyboard() noexcept = default;

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

		/// @brief Checks if the key is pressed.
		/// @param axis Key axis.
		/// @return @a True if it's pressed; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsPressed(AxisId axis) const noexcept;
		/// @brief Gets pressed keys.
		/// @return Pressed keys.
		[[nodiscard("Pure function")]]
		std::span<const AxisId> PressedKeys() const noexcept;
		/// @brief Sets if the key is pressed.
		/// @param axis Key axis.
		/// @param value Is it pressed?
		void Press(AxisId axis, bool value);
		/// @brief Resets all the keys to unpressed.
		void ResetKeys() noexcept;

		/// @brief Gets the connection status.
		/// @return Connection status.
		[[nodiscard("Pure function")]]
		bool IsConnected() const noexcept;
		/// @brief Sets the connection status.
		/// @param isConnected Connection status.
		void Connect(bool isConnected) noexcept;

		Keyboard& operator =(const Keyboard&) = delete;
		Keyboard& operator =(Keyboard&&) = delete;

	private:
		std::string name; ///< Keyboard device name.
		DeviceTypeId deviceType; ///< Keyboard device type.

		std::vector<AxisId> pressedKeys; ///< Pressed keys.
		bool isConnected; ///< Is the keyboard connected?
	};
}

namespace PonyEngine::Input
{
	Keyboard::Keyboard(const std::string_view name, const DeviceTypeId deviceType, const bool isConnected) :
		name(name),
		deviceType(deviceType),
		isConnected{isConnected}
	{
	}

	std::string_view Keyboard::Name() const noexcept
	{
		return name;
	}

	DeviceTypeId Keyboard::DeviceType() const noexcept
	{
		return deviceType;
	}

	std::span<const std::type_index> Keyboard::FeatureTypes() const noexcept
	{
		return std::span<const std::type_index>();
	}

	void* Keyboard::FindFeature(const std::type_index type) noexcept
	{
		return nullptr;
	}

	const void* Keyboard::FindFeature(const std::type_index type) const noexcept
	{
		return nullptr;
	}

	bool Keyboard::IsPressed(const AxisId axis) const noexcept
	{
		return std::ranges::find(pressedKeys, axis) != pressedKeys.cend();
	}

	std::span<const AxisId> Keyboard::PressedKeys() const noexcept
	{
		return pressedKeys;
	}

	void Keyboard::Press(const AxisId axis, const bool value)
	{
		const auto position = std::ranges::find(pressedKeys, axis);

		if (value)
		{
			if (position == pressedKeys.cend()) [[likely]]
			{
				pressedKeys.push_back(axis);
			}
		}
		else
		{
			if (position != pressedKeys.cend()) [[likely]]
			{
				pressedKeys.erase(position);
			}
		}
	}

	void Keyboard::ResetKeys() noexcept
	{
		pressedKeys.clear();
	}

	bool Keyboard::IsConnected() const noexcept
	{
		return isConnected;
	}

	void Keyboard::Connect(const bool isConnected) noexcept
	{
		this->isConnected = isConnected;
	}
}
