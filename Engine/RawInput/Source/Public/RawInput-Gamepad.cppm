/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Input/Gamepad.h"
#include "PonyEngine/Object/Body.h"

export module PonyEngine.RawInput:Gamepad;

import std;

export namespace PonyEngine::Input
{
	/// @brief Gamepad device.
	struct GamepadDevice final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(GamepadDevice)

		static constexpr std::string_view GenericType = PONY_INPUT_GAMEPAD; ///< Generic gamepad type. A gamepad device supports the @p GamepadLayout.

		static constexpr std::string_view Xbox = PONY_INPUT_XBOX; ///< Xbox name.
		static constexpr std::string_view XboxType = PONY_INPUT_GAMEPAD_XBOX; ///< Xbox gamepad type. An Xbox gamepad device supports the @p GamepadLayout.

		static constexpr std::string_view PlayStation = PONY_INPUT_PLAYSTATION; ///< PlayStation name.
		static constexpr std::string_view PlayStationType = PONY_INPUT_GAMEPAD_PLAYSTATION; ///< PlayStation gamepad type. A PlayStation gamepad device supports the @p GamepadLayout.
	};

	/// @brief Gamepad layout.
	struct GamepadLayout final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(GamepadLayout)

		static constexpr std::string_view Layout = PONY_INPUT_GAMEPAD; ///< Gamepad layout name.

		static constexpr std::string_view DPad = PONY_INPUT_GAMEPAD_DPAD; ///< D-pad name.
		static constexpr std::string_view DPadPath = PONY_INPUT_GAMEPAD_DPAD_PATH; ///< D-pad path.
		static constexpr std::string_view DPadLeftPath = PONY_INPUT_GAMEPAD_DPAD_LEFT_PATH; ///< Left d-pad button.
		static constexpr std::string_view DPadRightPath = PONY_INPUT_GAMEPAD_DPAD_RIGHT_PATH; ///< Right d-pad button.
		static constexpr std::string_view DPadDownPath = PONY_INPUT_GAMEPAD_DPAD_DOWN_PATH; ///< Down d-pad button.
		static constexpr std::string_view DPadUpPath = PONY_INPUT_GAMEPAD_DPAD_UP_PATH; ///< Up d-pad button.

		static constexpr std::string_view FaceButton = PONY_INPUT_GAMEPAD_FACE_BUTTON; ///< Face button group name.
		static constexpr std::string_view FaceButtonPath = PONY_INPUT_GAMEPAD_FACE_BUTTON_PATH; ///< Face button group path.
		static constexpr std::string_view FaceButtonLeftPath = PONY_INPUT_GAMEPAD_FACE_BUTTON_LEFT_PATH; ///< Left face button. X - on Xbox, □ - on PlayStation.
		static constexpr std::string_view FaceButtonRightPath = PONY_INPUT_GAMEPAD_FACE_BUTTON_RIGHT_PATH; ///< Right face button. B - on Xbox, ○ - on PlayStation.
		static constexpr std::string_view FaceButtonDownPath = PONY_INPUT_GAMEPAD_FACE_BUTTON_DOWN_PATH; ///< Down face button. A - on Xbox, ⨯ - on PlayStation.
		static constexpr std::string_view FaceButtonUpPath = PONY_INPUT_GAMEPAD_FACE_BUTTON_UP_PATH; ///< Up face button. Y - on Xbox, △ - on PlayStation.

		static constexpr std::string_view BackButton = PONY_INPUT_GAMEPAD_BACK_BUTTON; ///< Back button group name.
		static constexpr std::string_view BackButtonPath = PONY_INPUT_GAMEPAD_BACK_BUTTON_PATH; ///< Back button group path.
		static constexpr std::string_view BackButtonLeftPath = PONY_INPUT_GAMEPAD_BACK_BUTTON_LEFT_PATH; ///< Left back button. LB - on Xbox, L1 - on PlayStation.
		static constexpr std::string_view BackButtonRightPath = PONY_INPUT_GAMEPAD_BACK_BUTTON_RIGHT_PATH; ///< Right back button. RB - on Xbox, R1 - on PlayStation.

		static constexpr std::string_view Trigger = PONY_INPUT_GAMEPAD_TRIGGER; ///< Trigger group name.
		static constexpr std::string_view TriggerPath = PONY_INPUT_GAMEPAD_TRIGGER_PATH; ///< Trigger path.
		static constexpr std::string_view TriggerLeftPath = PONY_INPUT_GAMEPAD_TRIGGER_LEFT_PATH; ///< Left trigger. LT - on Xbox, L2 - on PlayStation.
		static constexpr std::string_view TriggerRightPath = PONY_INPUT_GAMEPAD_TRIGGER_RIGHT_PATH; ///< Right trigger. RT - on Xbox, R2 - on PlayStation.

		static constexpr std::string_view LeftStick = PONY_INPUT_GAMEPAD_LEFT_STICK; ///< Left stick group name.
		static constexpr std::string_view LeftStickPath = PONY_INPUT_GAMEPAD_LEFT_STICK_PATH; ///< Left stick group path.
		static constexpr std::string_view LeftStickHorizontalPath = PONY_INPUT_GAMEPAD_LEFT_STICK_HORIZONTAL_PATH; ///< Left stick horizontal axis.
		static constexpr std::string_view LeftStickVerticalPath = PONY_INPUT_GAMEPAD_LEFT_STICK_VERTICAL_PATH; ///< Left stick vertical axis.
		static constexpr std::string_view LeftStickButtonPath = PONY_INPUT_GAMEPAD_LEFT_STICK_BUTTON_PATH; ///< Left stick button. LS - on Xbox, L3 - on PlayStation.

		static constexpr std::string_view RightStick = PONY_INPUT_GAMEPAD_RIGHT_STICK; ///< Right stick group name.
		static constexpr std::string_view RightStickPath = PONY_INPUT_GAMEPAD_RIGHT_STICK_PATH; ///< Right strick group path.
		static constexpr std::string_view RightStickHorizontalPath = PONY_INPUT_GAMEPAD_RIGHT_STICK_HORIZONTAL_PATH; ///< Right stick horizontal axis.
		static constexpr std::string_view RightStickVerticalPath = PONY_INPUT_GAMEPAD_RIGHT_STICK_VERTICAL_PATH; ///< Right stick vertical axis.
		static constexpr std::string_view RightStickButtonPath = PONY_INPUT_GAMEPAD_RIGHT_STICK_BUTTON_PATH; ///< Right stick button. RS - on Xbox, R3 - on PlayStation.

		static constexpr std::string_view System = PONY_INPUT_GAMEPAD_SYSTEM; ///< System group name.
		static constexpr std::string_view SystemPath = PONY_INPUT_GAMEPAD_SYSTEM_PATH; ///< System group path.
		static constexpr std::string_view SystemMenuPath = PONY_INPUT_GAMEPAD_SYSTEM_MENU_PATH; ///< System menu path. Menu - on Xbox, Options - on PlayStation.
		static constexpr std::string_view SystemSelectPath = PONY_INPUT_GAMEPAD_SYSTEM_SELECT_PATH; ///< System select path. View - on Xbox, Share - on PlayStation.
		static constexpr std::string_view SystemGuidePath = PONY_INPUT_GAMEPAD_SYSTEM_GUIDE_PATH; ///< Guide button path. Usually, a button with a logo.
	};
}
