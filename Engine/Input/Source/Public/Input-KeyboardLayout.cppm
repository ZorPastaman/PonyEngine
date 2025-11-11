/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Input:KeyboardLayout;

import std;

import :Axis;

namespace PonyEngine::Input
{
	/// @brief Keyboard layout names.
	constexpr std::array<std::string_view, 101> KeyboardLayoutNames
	{
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
		"Left Bracket",
		"Right Bracket",
		// Numbers
		"Number 1",
		"Number 2",
		"Number 3",
		"Number 4",
		"Number 5",
		"Number 6",
		"Number 7",
		"Number 8",
		"Number 9",
		"Number 0",
		// Math signs
		"Minus",
		"Equal",
		"Tilde",
		// Arrows
		"Arrow Up",
		"Arrow Down",
		"Arrow Right",
		"Arrow Left",
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
		"Caps Lock",
		"Left Shift",
		"Right Shift",
		"Left Ctrl",
		"Right Ctrl",
		"Left Alt",
		"Right Alt",
		"Enter",
		"Insert",
		"Delete",
		"Home",
		"End",
		"Page Up",
		"Page Down",
		"Scroll Lock",
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
		"Numpad Plus",
		"Numpad Minus",
		"Numpad Star",
		"Numpad Slash",
		"Numpad Period",
		// Numpad system keys
		"Numpad Enter"
	};
}

export namespace PonyEngine::Input
{
	/// @brief Keyboard layout.
	enum class KeyboardLayout : AxisIdType
	{
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
		ScrollLock,
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
		NumpadPeriod,
		// Numpad system keys
		NumpadEnter
	};

	ENUM_VALUE_FEATURES(KeyboardLayout, KeyboardLayoutNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Input, KeyboardLayout)
}
