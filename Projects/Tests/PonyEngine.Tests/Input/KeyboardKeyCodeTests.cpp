/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <cstdint>;

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(KeyboardKeyCodeTests)
	{
		static void AssertString(const PonyEngine::Input::KeyboardKeyCode keyCode, const char* stringValue)
		{
			Assert::AreEqual(stringValue, PonyEngine::Input::ToString(keyCode));
			std::ostringstream ss;
			ss << keyCode;
			Assert::AreEqual(stringValue, ss.str().c_str());
		}

		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(0), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(1), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::A));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(2), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::B));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(3), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::C));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(4), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::D));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(5), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::E));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(6), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(7), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::G));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(8), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::H));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(9), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::I));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(10), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::J));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(11), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::K));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(12), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::L));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(13), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::M));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(14), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::N));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(15), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::O));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(16), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::P));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(17), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Q));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(18), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::R));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(19), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::S));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(20), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::T));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(21), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::U));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(22), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::V));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(23), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::W));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(24), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::X));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(25), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Y));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(26), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Z));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(27), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Period));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(28), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Comma));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(29), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Slash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(30), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Backslash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(31), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Semicolon));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(32), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Apostrophe));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(33), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::LeftBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(34), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::RightBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(35), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(36), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(37), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(38), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(39), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(40), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(41), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(42), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(43), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(44), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Number0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(45), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Minus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(46), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Equal));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(47), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Tilde));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(48), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::ArrowUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(49), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::ArrowDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(50), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::ArrowRight));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(51), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::ArrowLeft));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(52), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Space));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(53), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Backspace));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(54), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(55), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(56), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(57), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(58), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(59), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(60), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(61), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(62), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(63), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F10));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(64), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F11));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(65), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::F12));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(66), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Escape));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(67), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Tab));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(68), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::CapsLock));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(69), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::LeftShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(70), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::RightShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(71), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::LeftCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(72), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::RightCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(73), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::LeftAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(74), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::RightAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(75), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Enter));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(76), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Insert));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(77), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Delete));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(78), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Home));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(79), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::End));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(80), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::PageUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(81), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::PageDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(82), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(83), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(84), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(85), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(86), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(87), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(88), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(89), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(90), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(91), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::Numpad9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(92), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadPlus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(93), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadMinus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(94), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadStar));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(95), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadSlash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(96), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadComma));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(97), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadPeriod));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(98), static_cast<std::underlying_type_t<PonyEngine::Input::KeyboardKeyCode>>(PonyEngine::Input::KeyboardKeyCode::NumpadEnter));
		}

		TEST_METHOD(ToStringTest)
		{
			AssertString(PonyEngine::Input::KeyboardKeyCode::None, "None");
			AssertString(PonyEngine::Input::KeyboardKeyCode::A, "A");
			AssertString(PonyEngine::Input::KeyboardKeyCode::B, "B");
			AssertString(PonyEngine::Input::KeyboardKeyCode::C, "C");
			AssertString(PonyEngine::Input::KeyboardKeyCode::D, "D");
			AssertString(PonyEngine::Input::KeyboardKeyCode::E, "E");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F, "F");
			AssertString(PonyEngine::Input::KeyboardKeyCode::G, "G");
			AssertString(PonyEngine::Input::KeyboardKeyCode::H, "H");
			AssertString(PonyEngine::Input::KeyboardKeyCode::I, "I");
			AssertString(PonyEngine::Input::KeyboardKeyCode::J, "J");
			AssertString(PonyEngine::Input::KeyboardKeyCode::K, "K");
			AssertString(PonyEngine::Input::KeyboardKeyCode::L, "L");
			AssertString(PonyEngine::Input::KeyboardKeyCode::M, "M");
			AssertString(PonyEngine::Input::KeyboardKeyCode::N, "N");
			AssertString(PonyEngine::Input::KeyboardKeyCode::O, "O");
			AssertString(PonyEngine::Input::KeyboardKeyCode::P, "P");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Q, "Q");
			AssertString(PonyEngine::Input::KeyboardKeyCode::R, "R");
			AssertString(PonyEngine::Input::KeyboardKeyCode::S, "S");
			AssertString(PonyEngine::Input::KeyboardKeyCode::T, "T");
			AssertString(PonyEngine::Input::KeyboardKeyCode::U, "U");
			AssertString(PonyEngine::Input::KeyboardKeyCode::V, "V");
			AssertString(PonyEngine::Input::KeyboardKeyCode::W, "W");
			AssertString(PonyEngine::Input::KeyboardKeyCode::X, "X");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Y, "Y");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Z, "Z");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Period, "Period");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Comma, "Comma");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Slash, "Slash");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Backslash, "Backslash");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Semicolon, "Semicolon");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Apostrophe, "Apostrophe");
			AssertString(PonyEngine::Input::KeyboardKeyCode::LeftBracket, "Left bracket");
			AssertString(PonyEngine::Input::KeyboardKeyCode::RightBracket, "Right bracket");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number1, "1");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number2, "2");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number3, "3");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number4, "4");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number5, "5");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number6, "6");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number7, "7");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number8, "8");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number9, "9");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Number0, "0");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Minus, "Minus");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Equal, "Equal");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Tilde, "Tilde");
			AssertString(PonyEngine::Input::KeyboardKeyCode::ArrowUp, "Up");
			AssertString(PonyEngine::Input::KeyboardKeyCode::ArrowDown, "Down");
			AssertString(PonyEngine::Input::KeyboardKeyCode::ArrowRight, "Right");
			AssertString(PonyEngine::Input::KeyboardKeyCode::ArrowLeft, "Left");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Space, "Space");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Backspace, "Backspace");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F1, "F1");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F2, "F2");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F3, "F3");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F4, "F4");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F5, "F5");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F6, "F6");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F7, "F7");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F8, "F8");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F9, "F9");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F10, "F10");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F11, "F11");
			AssertString(PonyEngine::Input::KeyboardKeyCode::F12, "F12");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Escape, "Escape");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Tab, "Tab");
			AssertString(PonyEngine::Input::KeyboardKeyCode::CapsLock, "Caps lock");
			AssertString(PonyEngine::Input::KeyboardKeyCode::LeftShift, "Left shift");
			AssertString(PonyEngine::Input::KeyboardKeyCode::RightShift, "Right shift");
			AssertString(PonyEngine::Input::KeyboardKeyCode::LeftCtrl, "Left ctrl");
			AssertString(PonyEngine::Input::KeyboardKeyCode::RightCtrl, "Right ctrl");
			AssertString(PonyEngine::Input::KeyboardKeyCode::LeftAlt, "Left alt");
			AssertString(PonyEngine::Input::KeyboardKeyCode::RightAlt, "Right alt");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Enter, "Enter");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Insert, "Insert");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Delete, "Delete");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Home, "Home");
			AssertString(PonyEngine::Input::KeyboardKeyCode::End, "End");
			AssertString(PonyEngine::Input::KeyboardKeyCode::PageUp, "Page up");
			AssertString(PonyEngine::Input::KeyboardKeyCode::PageDown, "Page down");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad0, "Numpad 0");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad1, "Numpad 1");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad2, "Numpad 2");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad3, "Numpad 3");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad4, "Numpad 4");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad5, "Numpad 5");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad6, "Numpad 6");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad7, "Numpad 7");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad8, "Numpad 8");
			AssertString(PonyEngine::Input::KeyboardKeyCode::Numpad9, "Numpad 9");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadPlus, "Numpad +");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadMinus, "Numpad -");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadStar, "Numpad *");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadSlash, "Numpad /");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadComma, "Numpad ,");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadPeriod, "Numpad .");
			AssertString(PonyEngine::Input::KeyboardKeyCode::NumpadEnter, "Numpad Enter");
			AssertString(PonyEngine::Input::KeyboardKeyCode{99}, "Unknown");
		}
	};
}
