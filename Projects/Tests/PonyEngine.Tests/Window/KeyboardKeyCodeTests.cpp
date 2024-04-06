/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

import <string>;
import <type_traits>;

import PonyEngine.Window;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Window
{
	TEST_CLASS(KeyboardKeyCodeTests)
	{
		void AssertString(const PonyEngine::Window::KeyboardKeyCode keyCode, const std::string stringValue)
		{
			Assert::AreEqual(stringValue, PonyEngine::Window::ToString(keyCode));
			std::ostringstream ss;
			ss << keyCode;
			Assert::AreEqual(stringValue, ss.str());
		}

		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(0), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(1), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::A));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(2), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::B));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(3), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::C));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(4), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::D));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(5), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::E));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(6), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(7), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::G));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(8), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::H));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(9), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::I));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(10), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::J));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(11), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::K));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(12), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::L));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(13), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::M));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(14), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::N));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(15), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::O));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(16), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::P));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(17), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Q));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(18), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::R));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(19), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::S));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(20), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::T));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(21), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::U));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(22), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::V));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(23), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::W));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(24), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::X));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(25), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Y));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(26), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Z));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(27), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Period));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(28), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Comma));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(29), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Slash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(30), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Backslash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(31), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Semicolon));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(32), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Apostrophe));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(33), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::LeftBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(34), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::RightBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(35), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(36), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(37), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(38), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(39), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(40), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(41), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(42), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(43), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(44), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Number0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(45), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Minus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(46), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Equal));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(47), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Tilde));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(48), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::ArrowUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(49), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::ArrowDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(50), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::ArrowRight));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(51), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::ArrowLeft));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(52), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Space));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(53), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Backspace));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(54), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(55), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(56), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(57), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(58), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(59), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(60), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(61), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(62), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(63), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F10));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(64), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F11));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(65), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::F12));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(66), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Escape));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(67), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Tab));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(68), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::CapsLock));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(69), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::LeftShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(70), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::RightShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(71), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::LeftCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(72), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::RightCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(73), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::LeftAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(74), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::RightAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(75), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Enter));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(76), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Insert));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(77), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Delete));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(78), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Home));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(79), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::End));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(80), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::PageUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(81), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::PageDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(82), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(83), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(84), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(85), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(86), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(87), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(88), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(89), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(90), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(91), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::Numpad9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(92), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadPlus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(93), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadMinus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(94), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadStar));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(95), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadSlash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(96), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadPeriod));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(97), static_cast<std::underlying_type_t<PonyEngine::Window::KeyboardKeyCode>>(PonyEngine::Window::KeyboardKeyCode::NumpadEnter));
		}

		TEST_METHOD(ToStringTest)
		{
			AssertString(PonyEngine::Window::KeyboardKeyCode::None, "None");
			AssertString(PonyEngine::Window::KeyboardKeyCode::A, "A");
			AssertString(PonyEngine::Window::KeyboardKeyCode::B, "B");
			AssertString(PonyEngine::Window::KeyboardKeyCode::C, "C");
			AssertString(PonyEngine::Window::KeyboardKeyCode::D, "D");
			AssertString(PonyEngine::Window::KeyboardKeyCode::E, "E");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F, "F");
			AssertString(PonyEngine::Window::KeyboardKeyCode::G, "G");
			AssertString(PonyEngine::Window::KeyboardKeyCode::H, "H");
			AssertString(PonyEngine::Window::KeyboardKeyCode::I, "I");
			AssertString(PonyEngine::Window::KeyboardKeyCode::J, "J");
			AssertString(PonyEngine::Window::KeyboardKeyCode::K, "K");
			AssertString(PonyEngine::Window::KeyboardKeyCode::L, "L");
			AssertString(PonyEngine::Window::KeyboardKeyCode::M, "M");
			AssertString(PonyEngine::Window::KeyboardKeyCode::N, "N");
			AssertString(PonyEngine::Window::KeyboardKeyCode::O, "O");
			AssertString(PonyEngine::Window::KeyboardKeyCode::P, "P");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Q, "Q");
			AssertString(PonyEngine::Window::KeyboardKeyCode::R, "R");
			AssertString(PonyEngine::Window::KeyboardKeyCode::S, "S");
			AssertString(PonyEngine::Window::KeyboardKeyCode::T, "T");
			AssertString(PonyEngine::Window::KeyboardKeyCode::U, "U");
			AssertString(PonyEngine::Window::KeyboardKeyCode::V, "V");
			AssertString(PonyEngine::Window::KeyboardKeyCode::W, "W");
			AssertString(PonyEngine::Window::KeyboardKeyCode::X, "X");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Y, "Y");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Z, "Z");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Period, "Period");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Comma, "Comma");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Slash, "Slash");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Backslash, "Backslash");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Semicolon, "Semicolon");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Apostrophe, "Apostrophe");
			AssertString(PonyEngine::Window::KeyboardKeyCode::LeftBracket, "Left bracket");
			AssertString(PonyEngine::Window::KeyboardKeyCode::RightBracket, "Right bracket");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number1, "1");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number2, "2");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number3, "3");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number4, "4");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number5, "5");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number6, "6");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number7, "7");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number8, "8");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number9, "9");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Number0, "0");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Minus, "Minus");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Equal, "Equal");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Tilde, "Tilde");
			AssertString(PonyEngine::Window::KeyboardKeyCode::ArrowUp, "Up");
			AssertString(PonyEngine::Window::KeyboardKeyCode::ArrowDown, "Down");
			AssertString(PonyEngine::Window::KeyboardKeyCode::ArrowRight, "Right");
			AssertString(PonyEngine::Window::KeyboardKeyCode::ArrowLeft, "Left");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Space, "Space");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Backspace, "Backspace");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F1, "F1");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F2, "F2");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F3, "F3");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F4, "F4");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F5, "F5");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F6, "F6");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F7, "F7");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F8, "F8");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F9, "F9");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F10, "F10");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F11, "F11");
			AssertString(PonyEngine::Window::KeyboardKeyCode::F12, "F12");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Escape, "Escape");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Tab, "Tab");
			AssertString(PonyEngine::Window::KeyboardKeyCode::CapsLock, "Caps lock");
			AssertString(PonyEngine::Window::KeyboardKeyCode::LeftShift, "Left shift");
			AssertString(PonyEngine::Window::KeyboardKeyCode::RightShift, "Right shift");
			AssertString(PonyEngine::Window::KeyboardKeyCode::LeftCtrl, "Left ctrl");
			AssertString(PonyEngine::Window::KeyboardKeyCode::RightCtrl, "Right ctrl");
			AssertString(PonyEngine::Window::KeyboardKeyCode::LeftAlt, "Left alt");
			AssertString(PonyEngine::Window::KeyboardKeyCode::RightAlt, "Right alt");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Enter, "Enter");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Insert, "Insert");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Delete, "Delete");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Home, "Home");
			AssertString(PonyEngine::Window::KeyboardKeyCode::End, "End");
			AssertString(PonyEngine::Window::KeyboardKeyCode::PageUp, "Page up");
			AssertString(PonyEngine::Window::KeyboardKeyCode::PageDown, "Page down");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad0, "Numpad 0");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad1, "Numpad 1");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad2, "Numpad 2");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad3, "Numpad 3");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad4, "Numpad 4");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad5, "Numpad 5");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad6, "Numpad 6");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad7, "Numpad 7");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad8, "Numpad 8");
			AssertString(PonyEngine::Window::KeyboardKeyCode::Numpad9, "Numpad 9");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadPlus, "Numpad +");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadMinus, "Numpad -");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadStar, "Numpad *");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadSlash, "Numpad /");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadPeriod, "Numpad .");
			AssertString(PonyEngine::Window::KeyboardKeyCode::NumpadEnter, "Numpad Enter");
			AssertString(PonyEngine::Window::KeyboardKeyCode{98}, "98");
		}
	};
}
