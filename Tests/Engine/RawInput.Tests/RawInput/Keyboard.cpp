/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import std;

import PonyEngine.RawInput;

TEST_CASE("KeyboardDevice static data", "[RawInput][Keyboard]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardDevice::GenericType == "Keyboard");
}

TEST_CASE("KeyboardLayout static data", "[RawInput][Keyboard]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Layout == "Keyboard");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main == "Main");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPath == "Keyboard/Main");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainAPath == "Keyboard/Main/A");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainBPath == "Keyboard/Main/B");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainCPath == "Keyboard/Main/C");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainDPath == "Keyboard/Main/D");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainEPath == "Keyboard/Main/E");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainFPath == "Keyboard/Main/F");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainGPath == "Keyboard/Main/G");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainHPath == "Keyboard/Main/H");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainIPath == "Keyboard/Main/I");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainJPath == "Keyboard/Main/J");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainKPath == "Keyboard/Main/K");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainLPath == "Keyboard/Main/L");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainMPath == "Keyboard/Main/M");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainNPath == "Keyboard/Main/N");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainOPath == "Keyboard/Main/O");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPPath == "Keyboard/Main/P");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainQPath == "Keyboard/Main/Q");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainRPath == "Keyboard/Main/R");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainSPath == "Keyboard/Main/S");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainTPath == "Keyboard/Main/T");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainUPath == "Keyboard/Main/U");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainVPath == "Keyboard/Main/V");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainWPath == "Keyboard/Main/W");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainXPath == "Keyboard/Main/X");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainYPath == "Keyboard/Main/Y");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainZPath == "Keyboard/Main/Z");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main1Path == "Keyboard/Main/1");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main2Path == "Keyboard/Main/2");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main3Path == "Keyboard/Main/3");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main4Path == "Keyboard/Main/4");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main5Path == "Keyboard/Main/5");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main6Path == "Keyboard/Main/6");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main7Path == "Keyboard/Main/7");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main8Path == "Keyboard/Main/8");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main9Path == "Keyboard/Main/9");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Main0Path == "Keyboard/Main/0");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainEnterPath == "Keyboard/Main/Enter");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainEscapePath == "Keyboard/Main/Escape");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainBackspacePath == "Keyboard/Main/Backspace");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainTabPath == "Keyboard/Main/Tab");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainSpacePath == "Keyboard/Main/Space");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainDashPath == "Keyboard/Main/Dash");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainEqualsPath == "Keyboard/Main/Equals");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainLeftBracePath == "Keyboard/Main/LeftBrace");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainRightBracePath == "Keyboard/Main/RightBrace");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainBackslashPath == "Keyboard/Main/Backslash");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainColonPath == "Keyboard/Main/Colon");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainApostrophePath == "Keyboard/Main/Apostrophe");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainTildePath == "Keyboard/Main/Tilde");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainCommaPath == "Keyboard/Main/Comma");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPeriodPath == "Keyboard/Main/Period");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainSlashPath == "Keyboard/Main/Slash");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPipePath == "Keyboard/Main/Pipe");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF1Path == "Keyboard/Main/F1");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF2Path == "Keyboard/Main/F2");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF3Path == "Keyboard/Main/F3");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF4Path == "Keyboard/Main/F4");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF5Path == "Keyboard/Main/F5");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF6Path == "Keyboard/Main/F6");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF7Path == "Keyboard/Main/F7");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF8Path == "Keyboard/Main/F8");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF9Path == "Keyboard/Main/F9");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF10Path == "Keyboard/Main/F10");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF11Path == "Keyboard/Main/F11");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF12Path == "Keyboard/Main/F12");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF13Path == "Keyboard/Main/F13");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF14Path == "Keyboard/Main/F14");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF15Path == "Keyboard/Main/F15");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF16Path == "Keyboard/Main/F16");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF17Path == "Keyboard/Main/F17");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF18Path == "Keyboard/Main/F18");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF19Path == "Keyboard/Main/F19");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF20Path == "Keyboard/Main/F20");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF21Path == "Keyboard/Main/F21");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF22Path == "Keyboard/Main/F22");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF23Path == "Keyboard/Main/F23");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainF24Path == "Keyboard/Main/F24");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainInsertPath == "Keyboard/Main/Insert");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainDeletePath == "Keyboard/Main/Delete");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainHomePath == "Keyboard/Main/Home");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainEndPath == "Keyboard/Main/End");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPageUpPath == "Keyboard/Main/PageUp");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainPageDownPath == "Keyboard/Main/PageDown");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainLeftCtrlPath == "Keyboard/Main/LeftCtrl");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainRightCtrlPath == "Keyboard/Main/RightCtrl");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainLeftAltPath == "Keyboard/Main/LeftAlt");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainRightAltPath == "Keyboard/Main/RightAlt");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainLeftShiftPath == "Keyboard/Main/LeftShift");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::MainRightShiftPath == "Keyboard/Main/RightShift");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Lock == "Lock");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::LockPath == "Keyboard/Lock");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::LockCapsPath == "Keyboard/Lock/Caps");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::LockScrollPath == "Keyboard/Lock/Scroll");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::LockNumPath == "Keyboard/Lock/Num");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Arrow == "Arrow");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::ArrowPath == "Keyboard/Arrow");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::ArrowLeftPath == "Keyboard/Arrow/Left");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::ArrowRightPath == "Keyboard/Arrow/Right");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::ArrowDownPath == "Keyboard/Arrow/Down");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::ArrowUpPath == "Keyboard/Arrow/Up");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad == "Numpad");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadPath == "Keyboard/Numpad");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadSlashPath == "Keyboard/Numpad/Slash");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadStarPath == "Keyboard/Numpad/Star");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadDashPath == "Keyboard/Numpad/Dash");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadPlusPath == "Keyboard/Numpad/Plus");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadEnterPath == "Keyboard/Numpad/Enter");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad1Path == "Keyboard/Numpad/1");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad2Path == "Keyboard/Numpad/2");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad3Path == "Keyboard/Numpad/3");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad4Path == "Keyboard/Numpad/4");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad5Path == "Keyboard/Numpad/5");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad6Path == "Keyboard/Numpad/6");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad7Path == "Keyboard/Numpad/7");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad8Path == "Keyboard/Numpad/8");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad9Path == "Keyboard/Numpad/9");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::Numpad0Path == "Keyboard/Numpad/0");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadPeriodPath == "Keyboard/Numpad/Period");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadEqualsPath == "Keyboard/Numpad/Equals");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::NumpadCommaPath == "Keyboard/Numpad/Comma");

	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::System == "System");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemPath == "Keyboard/System");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemMenuPath == "Keyboard/System/Menu");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemLeftGuidePath == "Keyboard/System/LeftGuide");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemRightGuidePath == "Keyboard/System/RightGuide");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemPrintScreenPath == "Keyboard/System/PrintScreen");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemRequestPath == "Keyboard/System/Request");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemPausePath == "Keyboard/System/Pause");
	STATIC_REQUIRE(PonyEngine::RawInput::KeyboardLayout::SystemBreakPath == "Keyboard/System/Break");
}
