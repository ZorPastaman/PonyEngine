/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:KeyboardKeyCode;

import <cstdint>;
import <ostream>;
import <string>;
import <type_traits>;
import <unordered_map>;

namespace PonyEngine::Window
{
	/// @brief Keyboard key codes.
	export enum class KeyboardKeyCode : std::uint_fast8_t
	{
		// Special
		None,
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
		NumpadComma
	};

	/// @brief Creates a string representing the @p keyCode.
	/// @param keyCode Key code.
	/// @return Created string.
	export [[nodiscard("Pure function")]]
	std::string ToString(KeyboardKeyCode keyCode);

	/// @brief Puts a string representing the @p keyCode into the @p stream.
	/// @param stream Target.
	/// @param keyCode Key code.
	/// @return @p stream.
	export inline std::ostream& operator <<(std::ostream& stream, KeyboardKeyCode keyCode);

	/// @brief Key code to its name map.
	static const std::unordered_map<KeyboardKeyCode, const char*> s_keyCodeStrings
	{
		// Special
		{ KeyboardKeyCode::None, "None" },
		// Letters
		{ KeyboardKeyCode::A, "A" },
		{ KeyboardKeyCode::B, "B" },
		{ KeyboardKeyCode::C, "C" },
		{ KeyboardKeyCode::D, "D" },
		{ KeyboardKeyCode::E, "E" },
		{ KeyboardKeyCode::F, "F" },
		{ KeyboardKeyCode::G, "G" },
		{ KeyboardKeyCode::H, "H" },
		{ KeyboardKeyCode::I, "I" },
		{ KeyboardKeyCode::J, "J" },
		{ KeyboardKeyCode::K, "K" },
		{ KeyboardKeyCode::L, "L" },
		{ KeyboardKeyCode::M, "M" },
		{ KeyboardKeyCode::N, "N" },
		{ KeyboardKeyCode::O, "O" },
		{ KeyboardKeyCode::P, "P" },
		{ KeyboardKeyCode::Q, "Q" },
		{ KeyboardKeyCode::R, "R" },
		{ KeyboardKeyCode::S, "S" },
		{ KeyboardKeyCode::T, "T" },
		{ KeyboardKeyCode::U, "U" },
		{ KeyboardKeyCode::V, "V" },
		{ KeyboardKeyCode::W, "W" },
		{ KeyboardKeyCode::X, "X" },
		{ KeyboardKeyCode::Y, "Y" },
		{ KeyboardKeyCode::Z, "Z" },
		// Letter signs
		{ KeyboardKeyCode::Period, "Period" },
		{ KeyboardKeyCode::Comma, "Comma" },
		{ KeyboardKeyCode::Slash, "Slash" },
		{ KeyboardKeyCode::Backslash, "Backslash" },
		{ KeyboardKeyCode::Semicolon, "Semicolon" },
		{ KeyboardKeyCode::Apostrophe, "Apostrophe" },
		{ KeyboardKeyCode::LeftBracket, "Left bracket" },
		{ KeyboardKeyCode::RightBracket, "Right bracket" },
		// Numbers
		{ KeyboardKeyCode::Number1, "1" },
		{ KeyboardKeyCode::Number2, "2" },
		{ KeyboardKeyCode::Number3, "3" },
		{ KeyboardKeyCode::Number4, "4" },
		{ KeyboardKeyCode::Number5, "5" },
		{ KeyboardKeyCode::Number6, "6" },
		{ KeyboardKeyCode::Number7, "7" },
		{ KeyboardKeyCode::Number8, "8" },
		{ KeyboardKeyCode::Number9, "9" },
		{ KeyboardKeyCode::Number0, "0" },
		// Math signs
		{ KeyboardKeyCode::Minus, "Minus" },
		{ KeyboardKeyCode::Equal, "Equal" },
		{ KeyboardKeyCode::Tilde, "Tilde" },
		// Arrows
		{ KeyboardKeyCode::ArrowUp, "Up" },
		{ KeyboardKeyCode::ArrowDown, "Down" },
		{ KeyboardKeyCode::ArrowRight, "Right" },
		{ KeyboardKeyCode::ArrowLeft, "Left" },
		// Space
		{ KeyboardKeyCode::Space, "Space" },
		{ KeyboardKeyCode::Backspace, "Backspace" },
		// F Keys
		{ KeyboardKeyCode::F1, "F1" },
		{ KeyboardKeyCode::F2, "F2" },
		{ KeyboardKeyCode::F3, "F3" },
		{ KeyboardKeyCode::F4, "F4" },
		{ KeyboardKeyCode::F5, "F5" },
		{ KeyboardKeyCode::F6, "F6" },
		{ KeyboardKeyCode::F7, "F7" },
		{ KeyboardKeyCode::F8, "F8" },
		{ KeyboardKeyCode::F9, "F9" },
		{ KeyboardKeyCode::F10, "F10" },
		{ KeyboardKeyCode::F11, "F11" },
		{ KeyboardKeyCode::F12, "F12" },
		// System keys
		{ KeyboardKeyCode::Escape, "Escape" },
		{ KeyboardKeyCode::Tab, "Tab" },
		{ KeyboardKeyCode::CapsLock, "Caps lock" },
		{ KeyboardKeyCode::LeftShift, "Left shift" },
		{ KeyboardKeyCode::RightShift, "Right shift" },
		{ KeyboardKeyCode::LeftCtrl, "Left ctrl" },
		{ KeyboardKeyCode::RightCtrl, "Right ctrl" },
		{ KeyboardKeyCode::LeftAlt, "Left alt" },
		{ KeyboardKeyCode::RightAlt, "Right alt" },
		{ KeyboardKeyCode::Enter, "Enter" },
		{ KeyboardKeyCode::Insert, "Insert" },
		{ KeyboardKeyCode::Delete, "Delete" },
		{ KeyboardKeyCode::Home, "Home" },
		{ KeyboardKeyCode::End, "End" },
		{ KeyboardKeyCode::PageUp, "Page up" },
		{ KeyboardKeyCode::PageDown, "Page down" },
		// Numpad numbers
		{ KeyboardKeyCode::Numpad0, "Numpad 0", },
		{ KeyboardKeyCode::Numpad1, "Numpad 1", },
		{ KeyboardKeyCode::Numpad2, "Numpad 2", },
		{ KeyboardKeyCode::Numpad3, "Numpad 3", },
		{ KeyboardKeyCode::Numpad4, "Numpad 4", },
		{ KeyboardKeyCode::Numpad5, "Numpad 5", },
		{ KeyboardKeyCode::Numpad6, "Numpad 6", },
		{ KeyboardKeyCode::Numpad7, "Numpad 7", },
		{ KeyboardKeyCode::Numpad8, "Numpad 8", },
		{ KeyboardKeyCode::Numpad9, "Numpad 9", },
		// Numpad signs
		{ KeyboardKeyCode::NumpadPlus, "Numpad +" },
		{ KeyboardKeyCode::NumpadMinus, "Numpad -" },
		{ KeyboardKeyCode::NumpadStar, "Numpad *" },
		{ KeyboardKeyCode::NumpadSlash, "Numpad /" },
		{ KeyboardKeyCode::NumpadComma, "Numpad ," }
	};

	std::string ToString(const KeyboardKeyCode keyCode)
	{
		const std::unordered_map<KeyboardKeyCode, const char*>::const_iterator position = s_keyCodeStrings.find(keyCode);

		if (position != s_keyCodeStrings.end()) [[likely]]
		{
			return position->second;
		}
		else [[unlikely]]
		{
			return std::to_string(static_cast<std::underlying_type_t<KeyboardKeyCode>>(keyCode));
		}
	}

	inline std::ostream& operator<<(std::ostream& stream, const KeyboardKeyCode keyCode)
	{
		return stream << ToString(keyCode);
	}
}
