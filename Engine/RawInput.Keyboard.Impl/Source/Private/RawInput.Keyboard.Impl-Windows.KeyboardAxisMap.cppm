/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Input.h"

export module PonyEngine.RawInput.Keyboard.Impl:Windows.KeyboardAxisMap;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::Input::Windows
{
	/// @brief Windows keyboard axis map.
	class KeyboardAxisMap final
	{
	public:
		/// @brief Creates a keyboard axis map.
		/// @param input Raw input context.
		[[nodiscard("Pure constructor")]]
		explicit KeyboardAxisMap(IRawInputContext& input);
		KeyboardAxisMap(const KeyboardAxisMap&) = delete;
		KeyboardAxisMap(KeyboardAxisMap&&) = delete;

		~KeyboardAxisMap() noexcept = default;

		/// @brief Gets a bound axis.
		/// @param key Key.
		/// @return Axis.
		[[nodiscard("Pure function")]]
		AxisId Axis(const RAWKEYBOARD& key);

		KeyboardAxisMap& operator =(const KeyboardAxisMap&) = delete;
		KeyboardAxisMap& operator =(KeyboardAxisMap&&) = delete;

	private:
		/// @brief Gets a scan code from the key input.
		/// @param key Key input.
		/// @return Scan code.
		[[nodiscard("Pure function")]]
		static WORD ScanCode(const RAWKEYBOARD& key) noexcept;
		/// @brief Gets a bound axis.
		/// @param scanCode Scan code.
		/// @return Axis.
		AxisId Axis(WORD scanCode);
		/// @brief Binds an axis.
		/// @param scanCode Scan code.
		/// @param axisPath Axis path.
		/// @return Axis.
		AxisId Bind(WORD scanCode, std::string_view axisPath);

		IRawInputContext* input; ///< Raw input context.

		std::unordered_map<WORD, AxisId> axisMap; ///< Axis map.
	};
}

namespace PonyEngine::Input::Windows
{
	KeyboardAxisMap::KeyboardAxisMap(IRawInputContext& input) :
		input{&input}
	{
		Bind(0x001E, KeyboardLayout::MainAPath);
		Bind(0x0030, KeyboardLayout::MainBPath);
		Bind(0x002E, KeyboardLayout::MainCPath);
		Bind(0x0020, KeyboardLayout::MainDPath);
		Bind(0x0012, KeyboardLayout::MainEPath);
		Bind(0x0021, KeyboardLayout::MainFPath);
		Bind(0x0022, KeyboardLayout::MainGPath);
		Bind(0x0023, KeyboardLayout::MainHPath);
		Bind(0x0017, KeyboardLayout::MainIPath);
		Bind(0x0024, KeyboardLayout::MainJPath);
		Bind(0x0025, KeyboardLayout::MainKPath);
		Bind(0x0026, KeyboardLayout::MainLPath);
		Bind(0x0032, KeyboardLayout::MainMPath);
		Bind(0x0031, KeyboardLayout::MainNPath);
		Bind(0x0018, KeyboardLayout::MainOPath);
		Bind(0x0019, KeyboardLayout::MainPPath);
		Bind(0x0010, KeyboardLayout::MainQPath);
		Bind(0x0013, KeyboardLayout::MainRPath);
		Bind(0x001F, KeyboardLayout::MainSPath);
		Bind(0x0014, KeyboardLayout::MainTPath);
		Bind(0x0016, KeyboardLayout::MainUPath);
		Bind(0x002F, KeyboardLayout::MainVPath);
		Bind(0x0011, KeyboardLayout::MainWPath);
		Bind(0x002D, KeyboardLayout::MainXPath);
		Bind(0x0015, KeyboardLayout::MainYPath);
		Bind(0x002C, KeyboardLayout::MainZPath);

		Bind(0x0002, KeyboardLayout::Main1Path);
		Bind(0x0003, KeyboardLayout::Main2Path);
		Bind(0x0004, KeyboardLayout::Main3Path);
		Bind(0x0005, KeyboardLayout::Main4Path);
		Bind(0x0006, KeyboardLayout::Main5Path);
		Bind(0x0007, KeyboardLayout::Main6Path);
		Bind(0x0008, KeyboardLayout::Main7Path);
		Bind(0x0009, KeyboardLayout::Main8Path);
		Bind(0x000A, KeyboardLayout::Main9Path);
		Bind(0x000B, KeyboardLayout::Main0Path);

		Bind(0x001C, KeyboardLayout::MainEnterPath);
		Bind(0x0001, KeyboardLayout::MainEscapePath);
		Bind(0x000E, KeyboardLayout::MainBackspacePath);
		Bind(0x000F, KeyboardLayout::MainTabPath);
		Bind(0x0039, KeyboardLayout::MainSpacePath);

		Bind(0x000C, KeyboardLayout::MainDashPath);
		Bind(0x000D, KeyboardLayout::MainEqualsPath);
		Bind(0x001A, KeyboardLayout::MainLeftBracePath);
		Bind(0x001B, KeyboardLayout::MainRightBracePath);
		Bind(0x002B, KeyboardLayout::MainBackslashPath);
		Bind(0x0027, KeyboardLayout::MainColonPath);
		Bind(0x0028, KeyboardLayout::MainApostrophePath);
		Bind(0x0029, KeyboardLayout::MainTildePath);
		Bind(0x0033, KeyboardLayout::MainCommaPath);
		Bind(0x0034, KeyboardLayout::MainPeriodPath);
		Bind(0x0035, KeyboardLayout::MainSlashPath);
		Bind(0x0056, KeyboardLayout::MainPipePath);

		Bind(0x003B, KeyboardLayout::MainF1Path);
		Bind(0x003C, KeyboardLayout::MainF2Path);
		Bind(0x003D, KeyboardLayout::MainF3Path);
		Bind(0x003E, KeyboardLayout::MainF4Path);
		Bind(0x003F, KeyboardLayout::MainF5Path);
		Bind(0x0040, KeyboardLayout::MainF6Path);
		Bind(0x0041, KeyboardLayout::MainF7Path);
		Bind(0x0042, KeyboardLayout::MainF8Path);
		Bind(0x0043, KeyboardLayout::MainF9Path);
		Bind(0x0044, KeyboardLayout::MainF10Path);
		Bind(0x0057, KeyboardLayout::MainF11Path);
		Bind(0x0058, KeyboardLayout::MainF12Path);
		Bind(0x0064, KeyboardLayout::MainF13Path);
		Bind(0x0065, KeyboardLayout::MainF14Path);
		Bind(0x0066, KeyboardLayout::MainF15Path);
		Bind(0x0067, KeyboardLayout::MainF16Path);
		Bind(0x0068, KeyboardLayout::MainF17Path);
		Bind(0x0069, KeyboardLayout::MainF18Path);
		Bind(0x006A, KeyboardLayout::MainF19Path);
		Bind(0x006B, KeyboardLayout::MainF20Path);
		Bind(0x006C, KeyboardLayout::MainF21Path);
		Bind(0x006D, KeyboardLayout::MainF22Path);
		Bind(0x006E, KeyboardLayout::MainF23Path);
		Bind(0x0076, KeyboardLayout::MainF24Path);

		Bind(0xE052, KeyboardLayout::MainInsertPath);
		Bind(0xE053, KeyboardLayout::MainDeletePath);
		Bind(0xE047, KeyboardLayout::MainHomePath);
		Bind(0xE04F, KeyboardLayout::MainEndPath);
		Bind(0xE049, KeyboardLayout::MainPageUpPath);
		Bind(0xE051, KeyboardLayout::MainPageDownPath);

		Bind(0x001D, KeyboardLayout::MainLeftCtrlPath);
		Bind(0xE01D, KeyboardLayout::MainRightCtrlPath);
		Bind(0x0038, KeyboardLayout::MainLeftAltPath);
		Bind(0xE038, KeyboardLayout::MainRightAltPath);
		Bind(0x002A, KeyboardLayout::MainLeftShiftPath);
		Bind(0x0036, KeyboardLayout::MainRightShiftPath);

		Bind(0x003A, KeyboardLayout::LockCapsPath);
		Bind(0x0046, KeyboardLayout::LockScrollPath);
		Bind(0x0045, KeyboardLayout::LockNumPath);

		Bind(0xE04B, KeyboardLayout::ArrowLeftPath);
		Bind(0xE04D, KeyboardLayout::ArrowRightPath);
		Bind(0xE050, KeyboardLayout::ArrowDownPath);
		Bind(0xE048, KeyboardLayout::ArrowUpPath);

		Bind(0xE035, KeyboardLayout::NumpadSlashPath);
		Bind(0x0037, KeyboardLayout::NumpadStarPath);
		Bind(0x004A, KeyboardLayout::NumpadDashPath);
		Bind(0x004E, KeyboardLayout::NumpadPlusPath);
		Bind(0xE01C, KeyboardLayout::NumpadEnterPath);
		Bind(0x004F, KeyboardLayout::Numpad1Path);
		Bind(0x0050, KeyboardLayout::Numpad2Path);
		Bind(0x0051, KeyboardLayout::Numpad3Path);
		Bind(0x004B, KeyboardLayout::Numpad4Path);
		Bind(0x004C, KeyboardLayout::Numpad5Path);
		Bind(0x004D, KeyboardLayout::Numpad6Path);
		Bind(0x0047, KeyboardLayout::Numpad7Path);
		Bind(0x0048, KeyboardLayout::Numpad8Path);
		Bind(0x0049, KeyboardLayout::Numpad9Path);
		Bind(0x0052, KeyboardLayout::Numpad0Path);
		Bind(0x0053, KeyboardLayout::NumpadPeriodPath);
		Bind(0x0059, KeyboardLayout::NumpadEqualsPath);
		Bind(0x007E, KeyboardLayout::NumpadCommaPath);

		Bind(0xE05D, KeyboardLayout::SystemMenuPath);
		Bind(0xE05B, KeyboardLayout::SystemLeftGuidePath);
		Bind(0xE05C, KeyboardLayout::SystemRightGuidePath);
		Bind(0xE037, KeyboardLayout::SystemPrintScreenPath);
		Bind(0x0054, KeyboardLayout::SystemRequestPath);
		Bind(0xE11D, KeyboardLayout::SystemPausePath);
		Bind(0xE046, KeyboardLayout::SystemBreakPath);
	}

	AxisId KeyboardAxisMap::Axis(const RAWKEYBOARD& key)
	{
		return Axis(ScanCode(key));
	}

	WORD KeyboardAxisMap::ScanCode(const RAWKEYBOARD& key) noexcept
	{
		const USHORT makeCode = key.MakeCode;
		const USHORT flags = key.Flags;
		const USHORT base = makeCode & 0x7F;
		const USHORT extension = flags & RI_KEY_E0 ? 0xE0 : flags & RI_KEY_E1 ? 0xE1 : 0x00;

		return MAKEWORD(base, extension);
	}

	AxisId KeyboardAxisMap::Axis(const WORD scanCode)
	{
		if (const auto position = axisMap.find(scanCode); position != axisMap.cend()) [[likely]]
		{
			return position->second;
		}

		return Bind(scanCode, std::format("{}/scanCode/0x{:04X}", KeyboardLayout::Layout, scanCode));
	}

	AxisId KeyboardAxisMap::Bind(const WORD scanCode, const std::string_view axisPath)
	{
		return axisMap[scanCode] = input->Hash(Input::Axis(axisPath));
	}
}
