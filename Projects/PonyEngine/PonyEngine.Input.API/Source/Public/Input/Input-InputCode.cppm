/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputCode;

import <array>;
import <cmath>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

export namespace PonyEngine::Input
{
	/// @brief Input codes.
	enum class InputCode : std::uint32_t
	{
		// Special
		None,

		// Keyboard
		// Letters
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		// Letter signs
		Period,
		Comma,
		Slash,
		Backslash,
		Semicolon,
		Apostrophe,
		LeftBracket,
		RightBracket,
		// Numbers
		Number1,
		Number2,
		Number3,
		Number4,
		Number5,
		Number6,
		Number7,
		Number8,
		Number9,
		Number0,
		// Math signs
		Minus,
		Equal,
		Tilde,
		// Arrows
		ArrowUp,
		ArrowDown,
		ArrowRight,
		ArrowLeft,
		// Space
		Space,
		Backspace,
		// F Keys
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		// System keys
		Escape,
		Tab,
		CapsLock,
		LeftShift,
		RightShift,
		LeftCtrl,
		RightCtrl,
		LeftAlt,
		RightAlt,
		Enter,
		Insert,
		Delete,
		Home,
		End,
		PageUp,
		PageDown,
		// Numpad numbers
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		// Numpad signs
		NumpadPlus,
		NumpadMinus,
		NumpadStar,
		NumpadSlash,
		NumpadComma,
		NumpadPeriod,
		// Numpad system keys
		NumpadEnter,

		// Mouse
		// Axis
		MouseXPosition,
		MouseYPosition,
		MouseXDelta,
		MouseYDelta,
		// Buttons
		MouseLeftButton,
		MouseRightButton,
		MouseMiddleButton,
		MouseButton4,
		MouseButton5,
		// Wheel
		MouseWheel
	};

	/// @brief Gets a string representing the @p inputCode.
	/// @param inputCode Input code.
	/// @return Input code string.
	[[nodiscard("Pure function")]]
	std::string_view ToString(InputCode inputCode) noexcept;

	/// @brief Puts a string representing the @p inputCode into the @p stream.
	/// @param stream Target.
	/// @param inputCode Input code.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, InputCode inputCode);
}

namespace PonyEngine::Input
{
	/// @brief Input code to its name map.
	constexpr std::array<std::string_view, 110> InputCodeNames
	{
		// Special
		"None",

		// Keyboard
		// Letters
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		// Letter signs
		"Period",
		"Comma",
		"Slash",
		"Backslash",
		"Semicolon",
		"Apostrophe",
		"Left bracket",
		"Right bracket",
		// Numbers
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		// Math signs
		"Minus",
		"Equal",
		"Tilde",
		// Arrows
		"Up",
		"Down",
		"Right",
		"Left",
		// Space
		"Space",
		"Backspace",
		// F Keys
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		// System keys
		"Escape",
		"Tab",
		"Caps lock",
		"Left shift",
		"Right shift",
		"Left ctrl",
		"Right ctrl",
		"Left alt",
		"Right alt",
		"Enter",
		"Insert",
		"Delete",
		"Home",
		"End",
		"Page up",
		"Page down",
		// Numpad numbers
		"Numpad 0",
		"Numpad 1",
		"Numpad 2",
		"Numpad 3",
		"Numpad 4",
		"Numpad 5",
		"Numpad 6",
		"Numpad 7",
		"Numpad 8",
		"Numpad 9",
		// Numpad signs
		"Numpad +",
		"Numpad -",
		"Numpad *",
		"Numpad /",
		"Numpad ,",
		"Numpad .",
		// Numpad system keys
		"Numpad Enter",

		// Mouse
		// Axis
		"Mouse X Position",
		"Mouse Y Position",
		"Mouse X Delta",
		"Mouse Y Delta",
		// Buttons
		"Mouse Left Button",
		"Mouse Right Button",
		"Mouse Middle Button",
		"Mouse Button 4",
		"Mouse Button 5",
		// Wheel
		"Mouse Wheel",

		// Invalid
		"Unknown"
	};

	std::string_view ToString(const InputCode inputCode) noexcept
	{
		return InputCodeNames[std::min(static_cast<std::size_t>(inputCode), InputCodeNames.size() - 1)];
	}

	std::ostream& operator <<(std::ostream& stream, const InputCode inputCode)
	{
		return stream << ToString(inputCode);
	}
}
