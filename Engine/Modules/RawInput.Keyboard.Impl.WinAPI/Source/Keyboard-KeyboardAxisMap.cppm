/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.RawInput.Keyboard.Impl.WinAPI:KeyboardAxisMap;

import std;

import PonyEngine.RawInput.Ext;

export namespace PonyEngine::RawInput::Keyboard
{
	/// @brief Windows keyboard axis map.
	class KeyboardAxisMap final
	{
	public:
		/// @brief Creates a keyboard axis map.
		/// @param hub Device hub.
		[[nodiscard("Pure constructor")]]
		explicit KeyboardAxisMap(IDeviceHub& hub);
		KeyboardAxisMap(const KeyboardAxisMap&) = delete;
		KeyboardAxisMap(KeyboardAxisMap&&) = delete;

		~KeyboardAxisMap() noexcept = default;

		/// @brief Gets a bound axis.
		/// @param hub Device hub.
		/// @param key Key input.
		/// @return Axis.
		Axis EngineAxis(IDeviceHub& hub, const RAWKEYBOARD& key);

		KeyboardAxisMap& operator =(const KeyboardAxisMap&) = delete;
		KeyboardAxisMap& operator =(KeyboardAxisMap&&) = delete;

	private:
		/// @brief Binds an axis.
		/// @param scanCode Scan code.
		/// @param axisPath Axis path.
		/// @param hub Device hub.
		/// @return Axis.
		Axis Bind(WORD scanCode, std::string_view axisPath, IDeviceHub& hub);

		std::unordered_map<WORD, Axis> axisMap; ///< Axis map.
	};
}

namespace PonyEngine::RawInput::Keyboard
{
	KeyboardAxisMap::KeyboardAxisMap(IDeviceHub& hub)
	{
		Bind(0x001E, KeyboardLayout::MainAPath, hub);
		Bind(0x0030, KeyboardLayout::MainBPath, hub);
		Bind(0x002E, KeyboardLayout::MainCPath, hub);
		Bind(0x0020, KeyboardLayout::MainDPath, hub);
		Bind(0x0012, KeyboardLayout::MainEPath, hub);
		Bind(0x0021, KeyboardLayout::MainFPath, hub);
		Bind(0x0022, KeyboardLayout::MainGPath, hub);
		Bind(0x0023, KeyboardLayout::MainHPath, hub);
		Bind(0x0017, KeyboardLayout::MainIPath, hub);
		Bind(0x0024, KeyboardLayout::MainJPath, hub);
		Bind(0x0025, KeyboardLayout::MainKPath, hub);
		Bind(0x0026, KeyboardLayout::MainLPath, hub);
		Bind(0x0032, KeyboardLayout::MainMPath, hub);
		Bind(0x0031, KeyboardLayout::MainNPath, hub);
		Bind(0x0018, KeyboardLayout::MainOPath, hub);
		Bind(0x0019, KeyboardLayout::MainPPath, hub);
		Bind(0x0010, KeyboardLayout::MainQPath, hub);
		Bind(0x0013, KeyboardLayout::MainRPath, hub);
		Bind(0x001F, KeyboardLayout::MainSPath, hub);
		Bind(0x0014, KeyboardLayout::MainTPath, hub);
		Bind(0x0016, KeyboardLayout::MainUPath, hub);
		Bind(0x002F, KeyboardLayout::MainVPath, hub);
		Bind(0x0011, KeyboardLayout::MainWPath, hub);
		Bind(0x002D, KeyboardLayout::MainXPath, hub);
		Bind(0x0015, KeyboardLayout::MainYPath, hub);
		Bind(0x002C, KeyboardLayout::MainZPath, hub);

		Bind(0x0002, KeyboardLayout::Main1Path, hub);
		Bind(0x0003, KeyboardLayout::Main2Path, hub);
		Bind(0x0004, KeyboardLayout::Main3Path, hub);
		Bind(0x0005, KeyboardLayout::Main4Path, hub);
		Bind(0x0006, KeyboardLayout::Main5Path, hub);
		Bind(0x0007, KeyboardLayout::Main6Path, hub);
		Bind(0x0008, KeyboardLayout::Main7Path, hub);
		Bind(0x0009, KeyboardLayout::Main8Path, hub);
		Bind(0x000A, KeyboardLayout::Main9Path, hub);
		Bind(0x000B, KeyboardLayout::Main0Path, hub);

		Bind(0x001C, KeyboardLayout::MainEnterPath, hub);
		Bind(0x0001, KeyboardLayout::MainEscapePath, hub);
		Bind(0x000E, KeyboardLayout::MainBackspacePath, hub);
		Bind(0x000F, KeyboardLayout::MainTabPath, hub);
		Bind(0x0039, KeyboardLayout::MainSpacePath, hub);

		Bind(0x000C, KeyboardLayout::MainDashPath, hub);
		Bind(0x000D, KeyboardLayout::MainEqualsPath, hub);
		Bind(0x001A, KeyboardLayout::MainLeftBracePath, hub);
		Bind(0x001B, KeyboardLayout::MainRightBracePath, hub);
		Bind(0x002B, KeyboardLayout::MainBackslashPath, hub);
		Bind(0x0027, KeyboardLayout::MainColonPath, hub);
		Bind(0x0028, KeyboardLayout::MainApostrophePath, hub);
		Bind(0x0029, KeyboardLayout::MainTildePath, hub);
		Bind(0x0033, KeyboardLayout::MainCommaPath, hub);
		Bind(0x0034, KeyboardLayout::MainPeriodPath, hub);
		Bind(0x0035, KeyboardLayout::MainSlashPath, hub);
		Bind(0x0056, KeyboardLayout::MainPipePath, hub);

		Bind(0x003B, KeyboardLayout::MainF1Path, hub);
		Bind(0x003C, KeyboardLayout::MainF2Path, hub);
		Bind(0x003D, KeyboardLayout::MainF3Path, hub);
		Bind(0x003E, KeyboardLayout::MainF4Path, hub);
		Bind(0x003F, KeyboardLayout::MainF5Path, hub);
		Bind(0x0040, KeyboardLayout::MainF6Path, hub);
		Bind(0x0041, KeyboardLayout::MainF7Path, hub);
		Bind(0x0042, KeyboardLayout::MainF8Path, hub);
		Bind(0x0043, KeyboardLayout::MainF9Path, hub);
		Bind(0x0044, KeyboardLayout::MainF10Path, hub);
		Bind(0x0057, KeyboardLayout::MainF11Path, hub);
		Bind(0x0058, KeyboardLayout::MainF12Path, hub);
		Bind(0x0064, KeyboardLayout::MainF13Path, hub);
		Bind(0x0065, KeyboardLayout::MainF14Path, hub);
		Bind(0x0066, KeyboardLayout::MainF15Path, hub);
		Bind(0x0067, KeyboardLayout::MainF16Path, hub);
		Bind(0x0068, KeyboardLayout::MainF17Path, hub);
		Bind(0x0069, KeyboardLayout::MainF18Path, hub);
		Bind(0x006A, KeyboardLayout::MainF19Path, hub);
		Bind(0x006B, KeyboardLayout::MainF20Path, hub);
		Bind(0x006C, KeyboardLayout::MainF21Path, hub);
		Bind(0x006D, KeyboardLayout::MainF22Path, hub);
		Bind(0x006E, KeyboardLayout::MainF23Path, hub);
		Bind(0x0076, KeyboardLayout::MainF24Path, hub);

		Bind(0xE052, KeyboardLayout::MainInsertPath, hub);
		Bind(0xE053, KeyboardLayout::MainDeletePath, hub);
		Bind(0xE047, KeyboardLayout::MainHomePath, hub);
		Bind(0xE04F, KeyboardLayout::MainEndPath, hub);
		Bind(0xE049, KeyboardLayout::MainPageUpPath, hub);
		Bind(0xE051, KeyboardLayout::MainPageDownPath, hub);

		Bind(0x001D, KeyboardLayout::MainLeftCtrlPath, hub);
		Bind(0xE01D, KeyboardLayout::MainRightCtrlPath, hub);
		Bind(0x0038, KeyboardLayout::MainLeftAltPath, hub);
		Bind(0xE038, KeyboardLayout::MainRightAltPath, hub);
		Bind(0x002A, KeyboardLayout::MainLeftShiftPath, hub);
		Bind(0x0036, KeyboardLayout::MainRightShiftPath, hub);

		Bind(0x003A, KeyboardLayout::LockCapsPath, hub);
		Bind(0x0046, KeyboardLayout::LockScrollPath, hub);
		Bind(0x0045, KeyboardLayout::LockNumPath, hub);

		Bind(0xE04B, KeyboardLayout::ArrowLeftPath, hub);
		Bind(0xE04D, KeyboardLayout::ArrowRightPath, hub);
		Bind(0xE050, KeyboardLayout::ArrowDownPath, hub);
		Bind(0xE048, KeyboardLayout::ArrowUpPath, hub);

		Bind(0xE035, KeyboardLayout::NumpadSlashPath, hub);
		Bind(0x0037, KeyboardLayout::NumpadStarPath, hub);
		Bind(0x004A, KeyboardLayout::NumpadDashPath, hub);
		Bind(0x004E, KeyboardLayout::NumpadPlusPath, hub);
		Bind(0xE01C, KeyboardLayout::NumpadEnterPath, hub);
		Bind(0x004F, KeyboardLayout::Numpad1Path, hub);
		Bind(0x0050, KeyboardLayout::Numpad2Path, hub);
		Bind(0x0051, KeyboardLayout::Numpad3Path, hub);
		Bind(0x004B, KeyboardLayout::Numpad4Path, hub);
		Bind(0x004C, KeyboardLayout::Numpad5Path, hub);
		Bind(0x004D, KeyboardLayout::Numpad6Path, hub);
		Bind(0x0047, KeyboardLayout::Numpad7Path, hub);
		Bind(0x0048, KeyboardLayout::Numpad8Path, hub);
		Bind(0x0049, KeyboardLayout::Numpad9Path, hub);
		Bind(0x0052, KeyboardLayout::Numpad0Path, hub);
		Bind(0x0053, KeyboardLayout::NumpadPeriodPath, hub);
		Bind(0x0059, KeyboardLayout::NumpadEqualsPath, hub);
		Bind(0x007E, KeyboardLayout::NumpadCommaPath, hub);

		Bind(0xE05D, KeyboardLayout::SystemMenuPath, hub);
		Bind(0xE05B, KeyboardLayout::SystemLeftGuidePath, hub);
		Bind(0xE05C, KeyboardLayout::SystemRightGuidePath, hub);
		Bind(0xE037, KeyboardLayout::SystemPrintScreenPath, hub);
		Bind(0x0054, KeyboardLayout::SystemRequestPath, hub);
		Bind(0xE11D, KeyboardLayout::SystemPausePath, hub);
		Bind(0xE046, KeyboardLayout::SystemBreakPath, hub);
	}

	Axis KeyboardAxisMap::EngineAxis(IDeviceHub& hub, const RAWKEYBOARD& key)
	{
		const USHORT makeCode = key.MakeCode;
		const USHORT flags = key.Flags;
		const USHORT base = makeCode & 0x7F;
		const USHORT extension = flags & RI_KEY_E0 ? 0xE0 : flags & RI_KEY_E1 ? 0xE1 : 0x00;
		const WORD scanCode =  MAKEWORD(base, extension);

		if (const auto position = axisMap.find(scanCode); position != axisMap.cend()) [[likely]]
		{
			return position->second;
		}

		return Bind(scanCode, std::format("{}/scanCode/0x{:04X}", KeyboardLayout::Layout, scanCode), hub);
	}

	Axis KeyboardAxisMap::Bind(const WORD scanCode, const std::string_view axisPath, IDeviceHub& hub)
	{
		return axisMap[scanCode] = hub.MakeAxis(axisPath);
	}
}
