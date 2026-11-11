/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.XInput.Impl:GamepadAxisMap;

import std;

import PonyEngine.RawInput.Ext;

import :GamepadAxis;

export namespace PonyEngine::RawInput::XInput
{
	/// @brief XInput gamepad axis map.
	class GamepadAxisMap final
	{
	public:
		/// @brief Creates an XInput gamepad axis map.
		/// @param hub Device hub.
		[[nodiscard("Pure constructor")]]
		explicit GamepadAxisMap(IDeviceHub& hub);
		GamepadAxisMap(const GamepadAxisMap&) = delete;
		GamepadAxisMap(GamepadAxisMap&&) = delete;

		~GamepadAxisMap() noexcept = default;

		/// @brief Gets a buttons axis.
		/// @param button Button.
		/// @return Button axis.
		[[nodiscard("Pure function")]]
		Axis Button(Button button) const noexcept;
		/// @brief Gets a trigger axis.
		/// @param trigger Trigger axis type.
		/// @return Trigger axis.
		[[nodiscard("Pure function")]]
		Axis Trigger(TriggerAxis trigger) const noexcept;
		/// @brief Gets a stick axis.
		/// @param placement Stick placement.
		/// @param direction Stick direction.
		/// @return Stick axis.
		[[nodiscard("Pure function")]]
		Axis Stick(StickPlacement placement, StickDirection direction) const noexcept;

		GamepadAxisMap& operator =(const GamepadAxisMap&) = delete;
		GamepadAxisMap& operator =(GamepadAxisMap&&) = delete;

	private:
		/// @brief Binds a button.
		/// @param button Button
		/// @param axis Button axis.
		/// @param hub Device hub.
		void Bind(enum Button button, std::string_view axis, IDeviceHub& hub);
		/// @brief Binds a trigger.
		/// @param trigger Trigger axis type.
		/// @param axis Trigger axis.
		/// @param hub Device hub.
		void Bind(TriggerAxis trigger, std::string_view axis, IDeviceHub& hub);
		/// @brief Binds a stick.
		/// @param placement Stick placement.
		/// @param direction Stick direction.
		/// @param axis Stick axis.
		/// @param hub Device hub.
		void Bind(StickPlacement placement, StickDirection direction, std::string_view axis, IDeviceHub& hub);

		std::array<Axis, ButtonCount> buttonAxes; ///< Button axes.
		std::array<Axis, TriggerAxisCount> triggerAxes; ///< Trigger axes.
		std::array<std::array<Axis, StickDirectionCount>, StickPlacementCount> stickAxes; ///< Stick axes.
	};
}

namespace PonyEngine::RawInput::XInput
{
	GamepadAxisMap::GamepadAxisMap(IDeviceHub& hub)
	{
		constexpr auto buttonMap = std::array
		{
			std::pair(Button::DpadUp, GamepadLayout::DPadUpPath),
			std::pair(Button::DpadDown, GamepadLayout::DPadDownPath),
			std::pair(Button::DpadLeft, GamepadLayout::DPadLeftPath),
			std::pair(Button::DpadRight, GamepadLayout::DPadRightPath),
			std::pair(Button::Start, GamepadLayout::SystemMenuPath),
			std::pair(Button::Back, GamepadLayout::SystemSelectPath),
			std::pair(Button::LeftThumb, GamepadLayout::LeftStickButtonPath),
			std::pair(Button::RightThumb, GamepadLayout::RightStickButtonPath),
			std::pair(Button::LeftShoulder, GamepadLayout::BackButtonLeftPath),
			std::pair(Button::RightShoulder, GamepadLayout::BackButtonRightPath),
			std::pair(Button::A, GamepadLayout::FaceButtonDownPath),
			std::pair(Button::B, GamepadLayout::FaceButtonRightPath),
			std::pair(Button::X, GamepadLayout::FaceButtonLeftPath),
			std::pair(Button::Y, GamepadLayout::FaceButtonUpPath)
		};
		for (const auto [button, axis] : buttonMap)
		{
			Bind(button, axis, hub);
		}

		Bind(TriggerAxis::Left, GamepadLayout::TriggerLeftPath, hub);
		Bind(TriggerAxis::Right, GamepadLayout::TriggerRightPath, hub);

		Bind(StickPlacement::Left, StickDirection::Horizontal, GamepadLayout::LeftStickHorizontalPath, hub);
		Bind(StickPlacement::Left, StickDirection::Vertical, GamepadLayout::LeftStickVerticalPath, hub);
		Bind(StickPlacement::Right, StickDirection::Horizontal, GamepadLayout::RightStickHorizontalPath, hub);
		Bind(StickPlacement::Right, StickDirection::Vertical, GamepadLayout::RightStickVerticalPath, hub);
	}

	Axis GamepadAxisMap::Button(const enum Button button) const noexcept
	{
		return buttonAxes[static_cast<std::size_t>(button)];
	}

	Axis GamepadAxisMap::Trigger(const TriggerAxis trigger) const noexcept
	{
		return triggerAxes[static_cast<std::size_t>(trigger)];
	}

	Axis GamepadAxisMap::Stick(const StickPlacement placement, const StickDirection direction) const noexcept
	{
		return stickAxes[static_cast<std::size_t>(placement)][static_cast<std::size_t>(direction)];
	}

	void GamepadAxisMap::Bind(const enum Button button, const std::string_view axis, IDeviceHub& hub)
	{
		buttonAxes[static_cast<std::size_t>(button)] = hub.MakeAxis(axis);
	}

	void GamepadAxisMap::Bind(const TriggerAxis trigger, const std::string_view axis, IDeviceHub& hub)
	{
		triggerAxes[static_cast<std::size_t>(trigger)] = hub.MakeAxis(axis);
	}

	void GamepadAxisMap::Bind(const StickPlacement placement, const StickDirection direction, const std::string_view axis, IDeviceHub& hub)
	{
		stickAxes[static_cast<std::size_t>(placement)][static_cast<std::size_t>(direction)] = hub.MakeAxis(axis);
	}
}
