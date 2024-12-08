/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputCode;

import <cstdint>;
import <ostream>;
import <string>;
import <string_view>;
import <unordered_map>;

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
		MouseX,
		MouseY,
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
	const std::unordered_map<InputCode, std::string_view> KeyCodeStrings
	{
		// Special
		{ InputCode::None, "None" },

		// Keyboard
		// Letters
		{ InputCode::A, "A" },
		{ InputCode::B, "B" },
		{ InputCode::C, "C" },
		{ InputCode::D, "D" },
		{ InputCode::E, "E" },
		{ InputCode::F, "F" },
		{ InputCode::G, "G" },
		{ InputCode::H, "H" },
		{ InputCode::I, "I" },
		{ InputCode::J, "J" },
		{ InputCode::K, "K" },
		{ InputCode::L, "L" },
		{ InputCode::M, "M" },
		{ InputCode::N, "N" },
		{ InputCode::O, "O" },
		{ InputCode::P, "P" },
		{ InputCode::Q, "Q" },
		{ InputCode::R, "R" },
		{ InputCode::S, "S" },
		{ InputCode::T, "T" },
		{ InputCode::U, "U" },
		{ InputCode::V, "V" },
		{ InputCode::W, "W" },
		{ InputCode::X, "X" },
		{ InputCode::Y, "Y" },
		{ InputCode::Z, "Z" },
		// Letter signs
		{ InputCode::Period, "Period" },
		{ InputCode::Comma, "Comma" },
		{ InputCode::Slash, "Slash" },
		{ InputCode::Backslash, "Backslash" },
		{ InputCode::Semicolon, "Semicolon" },
		{ InputCode::Apostrophe, "Apostrophe" },
		{ InputCode::LeftBracket, "Left bracket" },
		{ InputCode::RightBracket, "Right bracket" },
		// Numbers
		{ InputCode::Number1, "1" },
		{ InputCode::Number2, "2" },
		{ InputCode::Number3, "3" },
		{ InputCode::Number4, "4" },
		{ InputCode::Number5, "5" },
		{ InputCode::Number6, "6" },
		{ InputCode::Number7, "7" },
		{ InputCode::Number8, "8" },
		{ InputCode::Number9, "9" },
		{ InputCode::Number0, "0" },
		// Math signs
		{ InputCode::Minus, "Minus" },
		{ InputCode::Equal, "Equal" },
		{ InputCode::Tilde, "Tilde" },
		// Arrows
		{ InputCode::ArrowUp, "Up" },
		{ InputCode::ArrowDown, "Down" },
		{ InputCode::ArrowRight, "Right" },
		{ InputCode::ArrowLeft, "Left" },
		// Space
		{ InputCode::Space, "Space" },
		{ InputCode::Backspace, "Backspace" },
		// F Keys
		{ InputCode::F1, "F1" },
		{ InputCode::F2, "F2" },
		{ InputCode::F3, "F3" },
		{ InputCode::F4, "F4" },
		{ InputCode::F5, "F5" },
		{ InputCode::F6, "F6" },
		{ InputCode::F7, "F7" },
		{ InputCode::F8, "F8" },
		{ InputCode::F9, "F9" },
		{ InputCode::F10, "F10" },
		{ InputCode::F11, "F11" },
		{ InputCode::F12, "F12" },
		// System keys
		{ InputCode::Escape, "Escape" },
		{ InputCode::Tab, "Tab" },
		{ InputCode::CapsLock, "Caps lock" },
		{ InputCode::LeftShift, "Left shift" },
		{ InputCode::RightShift, "Right shift" },
		{ InputCode::LeftCtrl, "Left ctrl" },
		{ InputCode::RightCtrl, "Right ctrl" },
		{ InputCode::LeftAlt, "Left alt" },
		{ InputCode::RightAlt, "Right alt" },
		{ InputCode::Enter, "Enter" },
		{ InputCode::Insert, "Insert" },
		{ InputCode::Delete, "Delete" },
		{ InputCode::Home, "Home" },
		{ InputCode::End, "End" },
		{ InputCode::PageUp, "Page up" },
		{ InputCode::PageDown, "Page down" },
		// Numpad numbers
		{ InputCode::Numpad0, "Numpad 0", },
		{ InputCode::Numpad1, "Numpad 1", },
		{ InputCode::Numpad2, "Numpad 2", },
		{ InputCode::Numpad3, "Numpad 3", },
		{ InputCode::Numpad4, "Numpad 4", },
		{ InputCode::Numpad5, "Numpad 5", },
		{ InputCode::Numpad6, "Numpad 6", },
		{ InputCode::Numpad7, "Numpad 7", },
		{ InputCode::Numpad8, "Numpad 8", },
		{ InputCode::Numpad9, "Numpad 9", },
		// Numpad signs
		{ InputCode::NumpadPlus, "Numpad +" },
		{ InputCode::NumpadMinus, "Numpad -" },
		{ InputCode::NumpadStar, "Numpad *" },
		{ InputCode::NumpadSlash, "Numpad /" },
		{ InputCode::NumpadComma, "Numpad ," },
		{ InputCode::NumpadPeriod, "Numpad ." },
		// Numpad system keys
		{ InputCode::NumpadEnter, "Numpad Enter" },

		// Mouse
		// Axis
		{ InputCode::MouseX, "Mouse X Axis" },
		{ InputCode::MouseY, "Mouse Y Axis" },
		{ InputCode::MouseXDelta, "Mouse X Delta" },
		{ InputCode::MouseYDelta, "Mouse Y Delta" },
		// Buttons
		{ InputCode::MouseLeftButton, "Mouse Left Button" },
		{ InputCode::MouseRightButton, "Mouse Right Button" },
		{ InputCode::MouseMiddleButton, "Mouse Middle Button" },
		{ InputCode::MouseButton4, "Mouse Button 4" },
		{ InputCode::MouseButton5, "Mouse Button 5" },
		// Wheel
		{ InputCode::MouseWheel, "Mouse Wheel" }
	};

	std::string_view ToString(const InputCode inputCode) noexcept
	{
		if (const auto position = KeyCodeStrings.find(inputCode); position != KeyCodeStrings.end()) [[likely]]
		{
			return position->second;
		}

		return "Unknown";
	}

	std::ostream& operator <<(std::ostream& stream, const InputCode inputCode)
	{
		return stream << ToString(inputCode);
	}
}
