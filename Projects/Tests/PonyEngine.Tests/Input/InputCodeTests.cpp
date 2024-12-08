/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "CppUnitTest.h"

#include <cstdint>
#include <ostream>
#include <string>
#include <string_view>

import PonyEngine.Input;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(InputCodeTests)
	{
		static void AssertString(const PonyEngine::Input::InputCode inputCode, const std::string_view stringValue)
		{
			Assert::AreEqual(stringValue, PonyEngine::Input::ToString(inputCode));
			std::ostringstream ss;
			ss << inputCode;
			Assert::AreEqual(stringValue.data(), ss.str().c_str());
		}

		TEST_METHOD(ValueTest)
		{
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(0), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::None));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(1), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::A));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(2), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::B));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(3), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::C));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(4), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::D));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(5), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::E));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(6), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(7), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::G));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(8), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::H));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(9), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::I));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(10), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::J));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(11), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::K));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(12), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::L));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(13), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::M));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(14), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::N));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(15), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::O));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(16), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::P));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(17), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Q));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(18), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::R));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(19), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::S));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(20), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::T));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(21), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::U));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(22), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::V));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(23), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::W));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(24), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::X));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(25), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Y));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(26), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Z));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(27), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Period));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(28), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Comma));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(29), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Slash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(30), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Backslash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(31), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Semicolon));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(32), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Apostrophe));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(33), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::LeftBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(34), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::RightBracket));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(35), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(36), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(37), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(38), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(39), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(40), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(41), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(42), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(43), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(44), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Number0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(45), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Minus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(46), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Equal));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(47), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Tilde));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(48), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::ArrowUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(49), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::ArrowDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(50), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::ArrowRight));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(51), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::ArrowLeft));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(52), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Space));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(53), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Backspace));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(54), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(55), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(56), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(57), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(58), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(59), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(60), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(61), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(62), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(63), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F10));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(64), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F11));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(65), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::F12));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(66), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Escape));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(67), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Tab));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(68), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::CapsLock));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(69), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::LeftShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(70), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::RightShift));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(71), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::LeftCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(72), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::RightCtrl));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(73), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::LeftAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(74), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::RightAlt));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(75), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Enter));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(76), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Insert));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(77), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Delete));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(78), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Home));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(79), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::End));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(80), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::PageUp));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(81), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::PageDown));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(82), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad0));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(83), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad1));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(84), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad2));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(85), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad3));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(86), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(87), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(88), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad6));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(89), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad7));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(90), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad8));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(91), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::Numpad9));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(92), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadPlus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(93), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadMinus));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(94), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadStar));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(95), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadSlash));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(96), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadComma));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(97), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadPeriod));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(98), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::NumpadEnter));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(99), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseX));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(100), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseY));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(101), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseLeftButton));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(102), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseRightButton));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(103), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseMiddleButton));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(104), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseButton4));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(105), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseButton5));
			Assert::AreEqual(static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(106), static_cast<std::underlying_type_t<PonyEngine::Input::InputCode>>(PonyEngine::Input::InputCode::MouseWheel));
		}

		TEST_METHOD(ToStringTest)
		{
			AssertString(PonyEngine::Input::InputCode::None, "None");
			AssertString(PonyEngine::Input::InputCode::A, "A");
			AssertString(PonyEngine::Input::InputCode::B, "B");
			AssertString(PonyEngine::Input::InputCode::C, "C");
			AssertString(PonyEngine::Input::InputCode::D, "D");
			AssertString(PonyEngine::Input::InputCode::E, "E");
			AssertString(PonyEngine::Input::InputCode::F, "F");
			AssertString(PonyEngine::Input::InputCode::G, "G");
			AssertString(PonyEngine::Input::InputCode::H, "H");
			AssertString(PonyEngine::Input::InputCode::I, "I");
			AssertString(PonyEngine::Input::InputCode::J, "J");
			AssertString(PonyEngine::Input::InputCode::K, "K");
			AssertString(PonyEngine::Input::InputCode::L, "L");
			AssertString(PonyEngine::Input::InputCode::M, "M");
			AssertString(PonyEngine::Input::InputCode::N, "N");
			AssertString(PonyEngine::Input::InputCode::O, "O");
			AssertString(PonyEngine::Input::InputCode::P, "P");
			AssertString(PonyEngine::Input::InputCode::Q, "Q");
			AssertString(PonyEngine::Input::InputCode::R, "R");
			AssertString(PonyEngine::Input::InputCode::S, "S");
			AssertString(PonyEngine::Input::InputCode::T, "T");
			AssertString(PonyEngine::Input::InputCode::U, "U");
			AssertString(PonyEngine::Input::InputCode::V, "V");
			AssertString(PonyEngine::Input::InputCode::W, "W");
			AssertString(PonyEngine::Input::InputCode::X, "X");
			AssertString(PonyEngine::Input::InputCode::Y, "Y");
			AssertString(PonyEngine::Input::InputCode::Z, "Z");
			AssertString(PonyEngine::Input::InputCode::Period, "Period");
			AssertString(PonyEngine::Input::InputCode::Comma, "Comma");
			AssertString(PonyEngine::Input::InputCode::Slash, "Slash");
			AssertString(PonyEngine::Input::InputCode::Backslash, "Backslash");
			AssertString(PonyEngine::Input::InputCode::Semicolon, "Semicolon");
			AssertString(PonyEngine::Input::InputCode::Apostrophe, "Apostrophe");
			AssertString(PonyEngine::Input::InputCode::LeftBracket, "Left bracket");
			AssertString(PonyEngine::Input::InputCode::RightBracket, "Right bracket");
			AssertString(PonyEngine::Input::InputCode::Number1, "1");
			AssertString(PonyEngine::Input::InputCode::Number2, "2");
			AssertString(PonyEngine::Input::InputCode::Number3, "3");
			AssertString(PonyEngine::Input::InputCode::Number4, "4");
			AssertString(PonyEngine::Input::InputCode::Number5, "5");
			AssertString(PonyEngine::Input::InputCode::Number6, "6");
			AssertString(PonyEngine::Input::InputCode::Number7, "7");
			AssertString(PonyEngine::Input::InputCode::Number8, "8");
			AssertString(PonyEngine::Input::InputCode::Number9, "9");
			AssertString(PonyEngine::Input::InputCode::Number0, "0");
			AssertString(PonyEngine::Input::InputCode::Minus, "Minus");
			AssertString(PonyEngine::Input::InputCode::Equal, "Equal");
			AssertString(PonyEngine::Input::InputCode::Tilde, "Tilde");
			AssertString(PonyEngine::Input::InputCode::ArrowUp, "Up");
			AssertString(PonyEngine::Input::InputCode::ArrowDown, "Down");
			AssertString(PonyEngine::Input::InputCode::ArrowRight, "Right");
			AssertString(PonyEngine::Input::InputCode::ArrowLeft, "Left");
			AssertString(PonyEngine::Input::InputCode::Space, "Space");
			AssertString(PonyEngine::Input::InputCode::Backspace, "Backspace");
			AssertString(PonyEngine::Input::InputCode::F1, "F1");
			AssertString(PonyEngine::Input::InputCode::F2, "F2");
			AssertString(PonyEngine::Input::InputCode::F3, "F3");
			AssertString(PonyEngine::Input::InputCode::F4, "F4");
			AssertString(PonyEngine::Input::InputCode::F5, "F5");
			AssertString(PonyEngine::Input::InputCode::F6, "F6");
			AssertString(PonyEngine::Input::InputCode::F7, "F7");
			AssertString(PonyEngine::Input::InputCode::F8, "F8");
			AssertString(PonyEngine::Input::InputCode::F9, "F9");
			AssertString(PonyEngine::Input::InputCode::F10, "F10");
			AssertString(PonyEngine::Input::InputCode::F11, "F11");
			AssertString(PonyEngine::Input::InputCode::F12, "F12");
			AssertString(PonyEngine::Input::InputCode::Escape, "Escape");
			AssertString(PonyEngine::Input::InputCode::Tab, "Tab");
			AssertString(PonyEngine::Input::InputCode::CapsLock, "Caps lock");
			AssertString(PonyEngine::Input::InputCode::LeftShift, "Left shift");
			AssertString(PonyEngine::Input::InputCode::RightShift, "Right shift");
			AssertString(PonyEngine::Input::InputCode::LeftCtrl, "Left ctrl");
			AssertString(PonyEngine::Input::InputCode::RightCtrl, "Right ctrl");
			AssertString(PonyEngine::Input::InputCode::LeftAlt, "Left alt");
			AssertString(PonyEngine::Input::InputCode::RightAlt, "Right alt");
			AssertString(PonyEngine::Input::InputCode::Enter, "Enter");
			AssertString(PonyEngine::Input::InputCode::Insert, "Insert");
			AssertString(PonyEngine::Input::InputCode::Delete, "Delete");
			AssertString(PonyEngine::Input::InputCode::Home, "Home");
			AssertString(PonyEngine::Input::InputCode::End, "End");
			AssertString(PonyEngine::Input::InputCode::PageUp, "Page up");
			AssertString(PonyEngine::Input::InputCode::PageDown, "Page down");
			AssertString(PonyEngine::Input::InputCode::Numpad0, "Numpad 0");
			AssertString(PonyEngine::Input::InputCode::Numpad1, "Numpad 1");
			AssertString(PonyEngine::Input::InputCode::Numpad2, "Numpad 2");
			AssertString(PonyEngine::Input::InputCode::Numpad3, "Numpad 3");
			AssertString(PonyEngine::Input::InputCode::Numpad4, "Numpad 4");
			AssertString(PonyEngine::Input::InputCode::Numpad5, "Numpad 5");
			AssertString(PonyEngine::Input::InputCode::Numpad6, "Numpad 6");
			AssertString(PonyEngine::Input::InputCode::Numpad7, "Numpad 7");
			AssertString(PonyEngine::Input::InputCode::Numpad8, "Numpad 8");
			AssertString(PonyEngine::Input::InputCode::Numpad9, "Numpad 9");
			AssertString(PonyEngine::Input::InputCode::NumpadPlus, "Numpad +");
			AssertString(PonyEngine::Input::InputCode::NumpadMinus, "Numpad -");
			AssertString(PonyEngine::Input::InputCode::NumpadStar, "Numpad *");
			AssertString(PonyEngine::Input::InputCode::NumpadSlash, "Numpad /");
			AssertString(PonyEngine::Input::InputCode::NumpadComma, "Numpad ,");
			AssertString(PonyEngine::Input::InputCode::NumpadPeriod, "Numpad .");
			AssertString(PonyEngine::Input::InputCode::NumpadEnter, "Numpad Enter");
			AssertString(PonyEngine::Input::InputCode::MouseX, "Mouse X Axis");
			AssertString(PonyEngine::Input::InputCode::MouseY, "Mouse Y Axis");
			AssertString(PonyEngine::Input::InputCode::MouseLeftButton, "Mouse Left Button");
			AssertString(PonyEngine::Input::InputCode::MouseRightButton, "Mouse Right Button");
			AssertString(PonyEngine::Input::InputCode::MouseMiddleButton, "Mouse Middle Button");
			AssertString(PonyEngine::Input::InputCode::MouseButton4, "Mouse Button 4");
			AssertString(PonyEngine::Input::InputCode::MouseButton5, "Mouse Button 5");
			AssertString(PonyEngine::Input::InputCode::MouseWheel, "Mouse Wheel");
			AssertString(PonyEngine::Input::InputCode{107}, "Unknown");
		}
	};
}
