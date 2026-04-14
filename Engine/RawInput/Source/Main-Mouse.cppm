/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"
#include "PonyEngine/RawInput/Mouse.h"

export module PonyEngine.RawInput:Mouse;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Mouse device.
	struct MouseDevice final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(MouseDevice)

		static constexpr std::string_view GenericType = PONY_INPUT_MOUSE; ///< Generic mouse type. A mouse device supports the @p MouseLayout.
	};

	/// @brief Mouse layout.
	struct MouseLayout final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(MouseLayout)

		static constexpr std::string_view Layout = PONY_INPUT_MOUSE; ///< Mouse layout name.

		static constexpr std::string_view Button = PONY_INPUT_MOUSE_BUTTON; ///< Button group name.
		static constexpr std::string_view ButtonPath = PONY_INPUT_MOUSE_BUTTON_PATH; ///< Button group path.
		static constexpr std::string_view Button1Path = PONY_INPUT_MOUSE_BUTTON_1_PATH; ///< Button '1'.
		static constexpr std::string_view Button2Path = PONY_INPUT_MOUSE_BUTTON_2_PATH; ///< Button '2'.
		static constexpr std::string_view Button3Path = PONY_INPUT_MOUSE_BUTTON_3_PATH; ///< Button '3'.
		static constexpr std::string_view Button4Path = PONY_INPUT_MOUSE_BUTTON_4_PATH; ///< Button '4'.
		static constexpr std::string_view Button5Path = PONY_INPUT_MOUSE_BUTTON_5_PATH; ///< Button '5'.
		static constexpr std::string_view ButtonLeftPath = Button1Path; ///< Left mouse button.
		static constexpr std::string_view ButtonRightPath = Button2Path; ///< Right mouse button.
		static constexpr std::string_view ButtonMiddlePath = Button3Path; ///< Middle mouse button.
		static constexpr std::string_view ButtonX1Path = Button4Path; ///< X1 button.
		static constexpr std::string_view ButtonX2Path = Button5Path; ///< X2 button.

		static constexpr std::string_view Wheel = PONY_INPUT_MOUSE_WHEEL; ///< Wheel group name.
		static constexpr std::string_view WheelPath = PONY_INPUT_MOUSE_WHEEL_PATH; ///< Wheel group path.
		static constexpr std::string_view WheelHorizontalPath = PONY_INPUT_MOUSE_WHEEL_HORIZONTAL_PATH; ///< Horizontal wheel axis.
		static constexpr std::string_view WheelVerticalPath = PONY_INPUT_MOUSE_WHEEL_VERTICAL_PATH; ///< Vertical wheel axis.

		static constexpr std::string_view Axis = PONY_INPUT_MOUSE_AXIS; ///< Mouse pointer group name.
		static constexpr std::string_view AxisPath = PONY_INPUT_MOUSE_AXIS_PATH; ///< Mouse pointer group path.
		static constexpr std::string_view AxisXPath = PONY_INPUT_MOUSE_AXIS_X_PATH; ///< Mouse X axis.
		static constexpr std::string_view AxisYPath = PONY_INPUT_MOUSE_AXIS_Y_PATH; ///< Mouse Y axis.
	};
}
