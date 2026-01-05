/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Input/Keyboard.h"
#include "PonyEngine/Object/Body.h"

export module PonyEngine.RawInput:Keyboard;

import std;

export namespace PonyEngine::Input
{
	/// @brief Keyboard device.
	struct KeyboardDevice final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(KeyboardDevice)

		static constexpr std::string_view GenericType = PONY_INPUT_KEYBOARD; ///< Generic keyboard type. A keyboard device supports the @p KeyboardLayout.
	};

	/// @brief Keyboard layout.
	struct KeyboardLayout final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(KeyboardLayout)

		static constexpr std::string_view Layout = PONY_INPUT_KEYBOARD; ///< Keyboard layout name.

		static constexpr std::string_view Main = PONY_INPUT_KEYBOARD_MAIN; ///< Main group name.
		static constexpr std::string_view MainPath = PONY_INPUT_KEYBOARD_MAIN_PATH; ///< Main group path.

		static constexpr std::string_view MainAPath = PONY_INPUT_KEYBOARD_MAIN_A_PATH; ///< Button with 'A' on US layout.
		static constexpr std::string_view MainBPath = PONY_INPUT_KEYBOARD_MAIN_B_PATH; ///< Button with 'B' on US layout.
		static constexpr std::string_view MainCPath = PONY_INPUT_KEYBOARD_MAIN_C_PATH; ///< Button with 'C' on US layout.
		static constexpr std::string_view MainDPath = PONY_INPUT_KEYBOARD_MAIN_D_PATH; ///< Button with 'D' on US layout.
		static constexpr std::string_view MainEPath = PONY_INPUT_KEYBOARD_MAIN_E_PATH; ///< Button with 'E' on US layout.
		static constexpr std::string_view MainFPath = PONY_INPUT_KEYBOARD_MAIN_F_PATH; ///< Button with 'F' on US layout.
		static constexpr std::string_view MainGPath = PONY_INPUT_KEYBOARD_MAIN_G_PATH; ///< Button with 'G' on US layout.
		static constexpr std::string_view MainHPath = PONY_INPUT_KEYBOARD_MAIN_H_PATH; ///< Button with 'H' on US layout.
		static constexpr std::string_view MainIPath = PONY_INPUT_KEYBOARD_MAIN_I_PATH; ///< Button with 'I' on US layout.
		static constexpr std::string_view MainJPath = PONY_INPUT_KEYBOARD_MAIN_J_PATH; ///< Button with 'J' on US layout.
		static constexpr std::string_view MainKPath = PONY_INPUT_KEYBOARD_MAIN_K_PATH; ///< Button with 'K' on US layout.
		static constexpr std::string_view MainLPath = PONY_INPUT_KEYBOARD_MAIN_L_PATH; ///< Button with 'L' on US layout.
		static constexpr std::string_view MainMPath = PONY_INPUT_KEYBOARD_MAIN_M_PATH; ///< Button with 'M' on US layout.
		static constexpr std::string_view MainNPath = PONY_INPUT_KEYBOARD_MAIN_N_PATH; ///< Button with 'N' on US layout.
		static constexpr std::string_view MainOPath = PONY_INPUT_KEYBOARD_MAIN_O_PATH; ///< Button with 'O' on US layout.
		static constexpr std::string_view MainPPath = PONY_INPUT_KEYBOARD_MAIN_P_PATH; ///< Button with 'P' on US layout.
		static constexpr std::string_view MainQPath = PONY_INPUT_KEYBOARD_MAIN_Q_PATH; ///< Button with 'Q' on US layout.
		static constexpr std::string_view MainRPath = PONY_INPUT_KEYBOARD_MAIN_R_PATH; ///< Button with 'R' on US layout.
		static constexpr std::string_view MainSPath = PONY_INPUT_KEYBOARD_MAIN_S_PATH; ///< Button with 'S' on US layout.
		static constexpr std::string_view MainTPath = PONY_INPUT_KEYBOARD_MAIN_T_PATH; ///< Button with 'T' on US layout.
		static constexpr std::string_view MainUPath = PONY_INPUT_KEYBOARD_MAIN_U_PATH; ///< Button with 'U' on US layout.
		static constexpr std::string_view MainVPath = PONY_INPUT_KEYBOARD_MAIN_V_PATH; ///< Button with 'V' on US layout.
		static constexpr std::string_view MainWPath = PONY_INPUT_KEYBOARD_MAIN_W_PATH; ///< Button with 'W' on US layout.
		static constexpr std::string_view MainXPath = PONY_INPUT_KEYBOARD_MAIN_X_PATH; ///< Button with 'X' on US layout.
		static constexpr std::string_view MainYPath = PONY_INPUT_KEYBOARD_MAIN_Y_PATH; ///< Button with 'Y' on US layout.
		static constexpr std::string_view MainZPath = PONY_INPUT_KEYBOARD_MAIN_Z_PATH; ///< Button with 'Z' on US layout.

		static constexpr std::string_view Main1Path = PONY_INPUT_KEYBOARD_MAIN_1_PATH; ///< Button with '1'.
		static constexpr std::string_view Main2Path = PONY_INPUT_KEYBOARD_MAIN_2_PATH; ///< Button with '2'.
		static constexpr std::string_view Main3Path = PONY_INPUT_KEYBOARD_MAIN_3_PATH; ///< Button with '3'.
		static constexpr std::string_view Main4Path = PONY_INPUT_KEYBOARD_MAIN_4_PATH; ///< Button with '4'.
		static constexpr std::string_view Main5Path = PONY_INPUT_KEYBOARD_MAIN_5_PATH; ///< Button with '5'.
		static constexpr std::string_view Main6Path = PONY_INPUT_KEYBOARD_MAIN_6_PATH; ///< Button with '6'.
		static constexpr std::string_view Main7Path = PONY_INPUT_KEYBOARD_MAIN_7_PATH; ///< Button with '7'.
		static constexpr std::string_view Main8Path = PONY_INPUT_KEYBOARD_MAIN_8_PATH; ///< Button with '8'.
		static constexpr std::string_view Main9Path = PONY_INPUT_KEYBOARD_MAIN_9_PATH; ///< Button with '9'.
		static constexpr std::string_view Main0Path = PONY_INPUT_KEYBOARD_MAIN_0_PATH; ///< Button with '0'.

		static constexpr std::string_view MainEnterPath = PONY_INPUT_KEYBOARD_MAIN_ENTER_PATH; ///< Enter button.
		static constexpr std::string_view MainEscapePath = PONY_INPUT_KEYBOARD_MAIN_ESCAPE_PATH; ///< Escape button.
		static constexpr std::string_view MainBackspacePath = PONY_INPUT_KEYBOARD_MAIN_BACKSPACE_PATH;  ///< Backspace button.
		static constexpr std::string_view MainTabPath = PONY_INPUT_KEYBOARD_MAIN_TAB_PATH; ///< Tab button.
		static constexpr std::string_view MainSpacePath = PONY_INPUT_KEYBOARD_MAIN_SPACE_PATH;  ///< Space button.

		static constexpr std::string_view MainDashPath = PONY_INPUT_KEYBOARD_MAIN_DASH_PATH; ///< Button with '-' on US layout.
		static constexpr std::string_view MainEqualsPath = PONY_INPUT_KEYBOARD_MAIN_EQUALS_PATH; ///< Button with '=' on US layout.
		static constexpr std::string_view MainLeftBracePath = PONY_INPUT_KEYBOARD_MAIN_LEFT_BRACE_PATH; ///< Button with '{' on US layout.
		static constexpr std::string_view MainRightBracePath = PONY_INPUT_KEYBOARD_MAIN_RIGHT_BRACE_PATH; ///< Button with '}' on US layout.
		static constexpr std::string_view MainBackslashPath = PONY_INPUT_KEYBOARD_MAIN_BACKSLASH_PATH; ///< Button with '\' on US layout.
		static constexpr std::string_view MainColonPath = PONY_INPUT_KEYBOARD_MAIN_COLON_PATH; ///< Button with ':' on US layout.
		static constexpr std::string_view MainApostrophePath = PONY_INPUT_KEYBOARD_MAIN_APOSTROPHE_PATH; ///< Button with ''' on US layout.
		static constexpr std::string_view MainTildePath = PONY_INPUT_KEYBOARD_MAIN_TILDE_PATH; ///< Button with '~' on US layout.
		static constexpr std::string_view MainCommaPath = PONY_INPUT_KEYBOARD_MAIN_COMMA_PATH; ///< Button with ',' on US layout.
		static constexpr std::string_view MainPeriodPath = PONY_INPUT_KEYBOARD_MAIN_PERIOD_PATH; ///< Button with '.' on US layout.
		static constexpr std::string_view MainSlashPath = PONY_INPUT_KEYBOARD_MAIN_SLASH_PATH; ///< Button with '/' on US layout.
		static constexpr std::string_view MainPipePath = PONY_INPUT_KEYBOARD_MAIN_PIPE_PATH; ///< Button with '|' on non-US layout.

		static constexpr std::string_view MainF1Path = PONY_INPUT_KEYBOARD_MAIN_F1_PATH; ///< 'F1' button.
		static constexpr std::string_view MainF2Path = PONY_INPUT_KEYBOARD_MAIN_F2_PATH; ///< 'F2' button.
		static constexpr std::string_view MainF3Path = PONY_INPUT_KEYBOARD_MAIN_F3_PATH; ///< 'F3' button.
		static constexpr std::string_view MainF4Path = PONY_INPUT_KEYBOARD_MAIN_F4_PATH; ///< 'F4' button.
		static constexpr std::string_view MainF5Path = PONY_INPUT_KEYBOARD_MAIN_F5_PATH; ///< 'F5' button.
		static constexpr std::string_view MainF6Path = PONY_INPUT_KEYBOARD_MAIN_F6_PATH; ///< 'F6' button.
		static constexpr std::string_view MainF7Path = PONY_INPUT_KEYBOARD_MAIN_F7_PATH; ///< 'F7' button.
		static constexpr std::string_view MainF8Path = PONY_INPUT_KEYBOARD_MAIN_F8_PATH; ///< 'F8' button.
		static constexpr std::string_view MainF9Path = PONY_INPUT_KEYBOARD_MAIN_F9_PATH; ///< 'F9' button.
		static constexpr std::string_view MainF10Path = PONY_INPUT_KEYBOARD_MAIN_F10_PATH; ///< 'F10' button.
		static constexpr std::string_view MainF11Path = PONY_INPUT_KEYBOARD_MAIN_F11_PATH; ///< 'F11' button.
		static constexpr std::string_view MainF12Path = PONY_INPUT_KEYBOARD_MAIN_F12_PATH; ///< 'F12' button.
		static constexpr std::string_view MainF13Path = PONY_INPUT_KEYBOARD_MAIN_F13_PATH; ///< 'F13' button.
		static constexpr std::string_view MainF14Path = PONY_INPUT_KEYBOARD_MAIN_F14_PATH; ///< 'F14' button.
		static constexpr std::string_view MainF15Path = PONY_INPUT_KEYBOARD_MAIN_F15_PATH; ///< 'F15' button.
		static constexpr std::string_view MainF16Path = PONY_INPUT_KEYBOARD_MAIN_F16_PATH; ///< 'F16' button.
		static constexpr std::string_view MainF17Path = PONY_INPUT_KEYBOARD_MAIN_F17_PATH; ///< 'F17' button.
		static constexpr std::string_view MainF18Path = PONY_INPUT_KEYBOARD_MAIN_F18_PATH; ///< 'F18' button.
		static constexpr std::string_view MainF19Path = PONY_INPUT_KEYBOARD_MAIN_F19_PATH; ///< 'F19' button.
		static constexpr std::string_view MainF20Path = PONY_INPUT_KEYBOARD_MAIN_F20_PATH; ///< 'F20' button.
		static constexpr std::string_view MainF21Path = PONY_INPUT_KEYBOARD_MAIN_F21_PATH; ///< 'F21' button.
		static constexpr std::string_view MainF22Path = PONY_INPUT_KEYBOARD_MAIN_F22_PATH; ///< 'F22' button.
		static constexpr std::string_view MainF23Path = PONY_INPUT_KEYBOARD_MAIN_F23_PATH; ///< 'F23' button.
		static constexpr std::string_view MainF24Path = PONY_INPUT_KEYBOARD_MAIN_F24_PATH; ///< 'F24' button.

		static constexpr std::string_view MainInsertPath = PONY_INPUT_KEYBOARD_MAIN_INSERT_PATH; ///< Insert button.
		static constexpr std::string_view MainDeletePath = PONY_INPUT_KEYBOARD_MAIN_DELETE_PATH; ///< Delete button.
		static constexpr std::string_view MainHomePath = PONY_INPUT_KEYBOARD_MAIN_HOME_PATH; ///< Home button.
		static constexpr std::string_view MainEndPath = PONY_INPUT_KEYBOARD_MAIN_END_PATH; ///< End button.
		static constexpr std::string_view MainPageUpPath = PONY_INPUT_KEYBOARD_MAIN_PAGE_UP_PATH; ///< Page Up button.
		static constexpr std::string_view MainPageDownPath = PONY_INPUT_KEYBOARD_MAIN_PAGE_DOWN_PATH; ///< Page Down button.

		static constexpr std::string_view MainLeftCtrlPath = PONY_INPUT_KEYBOARD_MAIN_LEFT_CTRL_PATH; ///< Left Ctrl button.
		static constexpr std::string_view MainRightCtrlPath = PONY_INPUT_KEYBOARD_MAIN_RIGHT_CTRL_PATH; ///< Right Ctrl button.
		static constexpr std::string_view MainLeftAltPath = PONY_INPUT_KEYBOARD_MAIN_LEFT_ALT_PATH; ///< Left Alt button.
		static constexpr std::string_view MainRightAltPath = PONY_INPUT_KEYBOARD_MAIN_RIGHT_ALT_PATH; ///< Right Alt button.
		static constexpr std::string_view MainLeftShiftPath = PONY_INPUT_KEYBOARD_MAIN_LEFT_SHIFT_PATH; ///< Left Shift button.
		static constexpr std::string_view MainRightShiftPath = PONY_INPUT_KEYBOARD_MAIN_RIGHT_SHIFT_PATH; ///< Right Shift button.

		static constexpr std::string_view Lock = PONY_INPUT_KEYBOARD_LOCK; ///< Lock group name.
		static constexpr std::string_view LockPath = PONY_INPUT_KEYBOARD_LOCK_PATH; ///< Lock group path.
		static constexpr std::string_view LockCapsPath = PONY_INPUT_KEYBOARD_LOCK_CAPS_PATH; ///< Caps Lock button
		static constexpr std::string_view LockScrollPath = PONY_INPUT_KEYBOARD_LOCK_SCROLL_PATH; ///< Scroll Lock button
		static constexpr std::string_view LockNumPath = PONY_INPUT_KEYBOARD_LOCK_NUM_PATH; ///< Num Lock button

		static constexpr std::string_view Arrow = PONY_INPUT_KEYBOARD_ARROW; ///< Arrow group name.
		static constexpr std::string_view ArrowPath = PONY_INPUT_KEYBOARD_ARROW_PATH; ///< Arrow group path.
		static constexpr std::string_view ArrowLeftPath = PONY_INPUT_KEYBOARD_ARROW_LEFT_PATH; ///< Left arrow button.
		static constexpr std::string_view ArrowRightPath = PONY_INPUT_KEYBOARD_ARROW_RIGHT_PATH; ///< Right arrow button.
		static constexpr std::string_view ArrowDownPath = PONY_INPUT_KEYBOARD_ARROW_DOWN_PATH; ///< Down arrow button.
		static constexpr std::string_view ArrowUpPath = PONY_INPUT_KEYBOARD_ARROW_UP_PATH; ///< Up arrow button.

		static constexpr std::string_view Numpad = PONY_INPUT_KEYBOARD_NUMPAD; ///< Numpad group name.
		static constexpr std::string_view NumpadPath = PONY_INPUT_KEYBOARD_NUMPAD_PATH; ///< Numpad group path.
		static constexpr std::string_view NumpadSlashPath = PONY_INPUT_KEYBOARD_NUMPAD_SLASH_PATH; ///< Numpad '/' button.
		static constexpr std::string_view NumpadStarPath = PONY_INPUT_KEYBOARD_NUMPAD_STAR_PATH; ///< Numpad '*' button.
		static constexpr std::string_view NumpadDashPath = PONY_INPUT_KEYBOARD_NUMPAD_DASH_PATH; ///< Numpad '-' button.
		static constexpr std::string_view NumpadPlusPath = PONY_INPUT_KEYBOARD_NUMPAD_PLUS_PATH; ///< Numpad '+' button.
		static constexpr std::string_view NumpadEnterPath = PONY_INPUT_KEYBOARD_NUMPAD_ENTER_PATH; ///< Numpad Enter button.
		static constexpr std::string_view Numpad1Path = PONY_INPUT_KEYBOARD_NUMPAD_1_PATH; ///< Numpad '1' button.
		static constexpr std::string_view Numpad2Path = PONY_INPUT_KEYBOARD_NUMPAD_2_PATH; ///< Numpad '2' button.
		static constexpr std::string_view Numpad3Path = PONY_INPUT_KEYBOARD_NUMPAD_3_PATH; ///< Numpad '3' button.
		static constexpr std::string_view Numpad4Path = PONY_INPUT_KEYBOARD_NUMPAD_4_PATH; ///< Numpad '4' button.
		static constexpr std::string_view Numpad5Path = PONY_INPUT_KEYBOARD_NUMPAD_5_PATH; ///< Numpad '5' button.
		static constexpr std::string_view Numpad6Path = PONY_INPUT_KEYBOARD_NUMPAD_6_PATH; ///< Numpad '6' button.
		static constexpr std::string_view Numpad7Path = PONY_INPUT_KEYBOARD_NUMPAD_7_PATH; ///< Numpad '7' button.
		static constexpr std::string_view Numpad8Path = PONY_INPUT_KEYBOARD_NUMPAD_8_PATH; ///< Numpad '8' button.
		static constexpr std::string_view Numpad9Path = PONY_INPUT_KEYBOARD_NUMPAD_9_PATH; ///< Numpad '9' button.
		static constexpr std::string_view Numpad0Path = PONY_INPUT_KEYBOARD_NUMPAD_0_PATH; ///< Numpad '0' button.
		static constexpr std::string_view NumpadPeriodPath = PONY_INPUT_KEYBOARD_NUMPAD_PERIOD_PATH; ///< Numpad '.' button.
		static constexpr std::string_view NumpadEqualsPath = PONY_INPUT_KEYBOARD_NUMPAD_EQUALS_PATH; ///< Numpad '=' button.
		static constexpr std::string_view NumpadCommaPath = PONY_INPUT_KEYBOARD_NUMPAD_COMMA_PATH; ///< Numpad ',' button.

		static constexpr std::string_view System = PONY_INPUT_KEYBOARD_SYSTEM; ///< System group name.
		static constexpr std::string_view SystemPath = PONY_INPUT_KEYBOARD_SYSTEM_PATH; ///< System group path.
		static constexpr std::string_view SystemMenuPath = PONY_INPUT_KEYBOARD_SYSTEM_MENU_PATH; ///< Menu button.
		static constexpr std::string_view SystemLeftGuidePath = PONY_INPUT_KEYBOARD_SYSTEM_LEFT_GUIDE_PATH; ///< Left guide button.
		static constexpr std::string_view SystemRightGuidePath = PONY_INPUT_KEYBOARD_SYSTEM_RIGHT_GUIDE_PATH; ///< Right guide button.
		static constexpr std::string_view SystemPrintScreenPath = PONY_INPUT_KEYBOARD_SYSTEM_PRINT_SCREEN_PATH; ///< Print screen button.
		static constexpr std::string_view SystemRequestPath = PONY_INPUT_KEYBOARD_SYSTEM_REQUEST_PATH; ///< Request button.
		static constexpr std::string_view SystemPausePath = PONY_INPUT_KEYBOARD_SYSTEM_PAUSE_PATH; ///< Pause button.
		static constexpr std::string_view SystemBreakPath = PONY_INPUT_KEYBOARD_SYSTEM_BREAK_PATH; ///< Break button.
	};
}
