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
#include "PonyEngine/RawInput/Layout.h"

export module PonyEngine.RawInput:Layout;

import std;

export namespace PonyEngine::RawInput
{
	/// @brief Layout values.
	struct Layout final
	{
		PONY_NON_CONSTRUCTIBLE_BODY(Layout)

		static constexpr char PathSeparator = PONY_INPUT_PATH_SEPARATOR; ///< Layout path separator.

		static constexpr std::string_view Middle = PONY_INPUT_PATH_MIDDLE; ///< Layout middle name.
		static constexpr std::string_view Left = PONY_INPUT_PATH_LEFT; ///< Layout left name.
		static constexpr std::string_view Right = PONY_INPUT_PATH_RIGHT; ///< Layout right name.
		static constexpr std::string_view Down = PONY_INPUT_PATH_DOWN; ///< Layout down name.
		static constexpr std::string_view Up = PONY_INPUT_PATH_UP; ///< Layout up name.
		static constexpr std::string_view Horizontal = PONY_INPUT_PATH_HORIZONTAL; ///< Layout horizontal name.
		static constexpr std::string_view Vertical = PONY_INPUT_PATH_VERTICAL; ///< Layout vertical name.

		static constexpr std::string_view Axis = PONY_INPUT_PATH_AXIS; ///< Layout axis name.
		static constexpr std::string_view Arrow = PONY_INPUT_PATH_ARROW; ///< Layout arrow name.
		static constexpr std::string_view Button = PONY_INPUT_PATH_BUTTON;  ///< Layout button name.

		static constexpr std::string_view System = PONY_INPUT_PATH_SYSTEM; ///< Layout system name.
		static constexpr std::string_view Main = PONY_INPUT_PATH_MAIN; ///< Layout main name.
		static constexpr std::string_view Menu = PONY_INPUT_PATH_MENU; ///< Layout menu name.
		static constexpr std::string_view Select = PONY_INPUT_PATH_SELECT; ///< Layout select name.
		static constexpr std::string_view Guide = PONY_INPUT_PATH_GUIDE; ///< Layout guide name.
	};
}
